// only works for prime modulus

template<int m>
struct modular{
    int64_t r;
    modular() : r(0) {}
    modular(int64_t rr) : r(rr) {if(abs(r) >= m) r %= m; if(r < 0) r += m;}
    modular operator += (const modular &t) {r += t.r; if(r >= m) r -= m; return *this;}
    modular operator -= (const modular &t) {r -= t.r; if(r < 0) r += m; return *this;}
    modular operator + (const modular& t) const {return modular(r) += t;}
    modular operator - (const modular& t) const {return modular(r) -= t;}
    modular operator *= (const modular& t) {r = (r * t.r) % m; return *this;}
    modular operator * (const modular& t) const {return (r * t.r) % m;}
    modular pow(int64_t e) const {
        modular ret(1), mul(r);
        while(e){
            if(e&1)ret *= mul;
            mul *= mul;
            e >>= 1;
        }
        return ret;
    }
    modular inv() const {return this->pow(m-2);} // can change if non-prime modulus
    modular operator / (const modular& t) const {return *this * t.inv();}
    modular operator /= (const modular& t) {return *this = *this / t;}

    bool operator == (const modular& t) const {return r == t.r;}
    bool operator != (const modular& t) const {return r != t.r;}

    operator int64_t() const {return r;}
};

template<int T>
istream& operator >> (istream &in, modular<T> &x) {
    return in >> x.r;
}