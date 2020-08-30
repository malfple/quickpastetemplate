// only works for prime modulus

inline ll domod(ll x){
	if(abs(x) >= MOD) x %= MOD;
	if(x < 0)x += MOD;
	return x;
}
inline ll addmod(ll a, ll b){
	a += b; if(a >= MOD) a -= MOD; return a;
}
inline ll submod(ll a, ll b){
	a -= b; if(a < 0) a += MOD; return a;
}
inline ll mulmod(ll a, ll b){return (a*b)%MOD;}
inline ll powmod(ll a, ll e){
	ll ret = 1;
	while(e){
		if(e&1)ret = mulmod(ret, a);
		a = mulmod(a, a);
		e >>= 1;
	}
	return ret;
}
inline ll invmod(ll a){ // change this if non-prime modulus
	return powmod(a, MOD-2);
}
inline ll divmod(ll a, ll b){
	return mulmod(a, invmod(b));
}
