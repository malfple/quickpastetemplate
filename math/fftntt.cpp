/*
input a, a vector representation of polynomial, output a as point representation. Put sign=-1 for inverse.
NTT -> integer FFT with modulo
 */

/*
For NTT, let p be modulo prime
p = 2^k * c + 1
need: size of polynom <= 2^k
find r so that r^1 .. r^p-1 distinct <- call prr

change for the following
int theta = expmod(prr, (MOD-1)/n); // expmod->exponent
if(sign == -1)theta = expmod(theta, MOD-2);
    w = expmod(theta, irev) // can be saved to array
don’t forget divmod and other mods
*/
typedef complex<long double> Cld;
void FFT(vector<Cld>& a, int sign = 1) {
    int n = a.size(); // n should be a power of two
    double theta = sign * 2 * M_PI / n;
    for(int i = 0, j = 1; j < n - 1; ++j) {
        for(int k = n >> 1; k > (i ^= k); k >>= 1);
        if(j < i) swap(a[i], a[j]);
    }
    for(int m, mh = 1; (m = mh << 1) <= n; mh = m) {
        int irev = 0;
        for(int i = 0; i < n; i += m) {
            Cld  w = exp(Cld(0, theta*irev));
            for(int k = n >> 2; k > (irev ^= k); k >>= 1);
            for(int j = i; j < mh + i; ++j) {
                int k = j + mh;
                Cld x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
    }
    if(sign == -1) FOR(i,n)a[i] /= n;
}

void vector_multiply(vector<Cld>& res, vector<Cld>& a, vector<Cld>& b){ // multiplies, stores to a
    res.clear();
    int n = a.size() + b.size() - 1;
    for(int i=1; i<n; i<<=1)if(n&i)n += i;
    a.resize(n);
    b.resize(n);

    FFT(a);
    FFT(b);
    FOR(i,n)res.pb(a[i] * b[i]);
    FFT(res, -1);
}