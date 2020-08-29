// define N

// 1-indexed
template<typename T>
struct FenwickTree{
    vector<T> a;
    FenwickTree(int s) {
        a.resize(s+1, 0);
    }
    void update(int x, T v){
        for(int i=x; i<a.size(); i+=i&-i) a[i] += v;
    }
    T query(int x){
        T ret = 0;
        for(int i=x; i>=1; i-=i&-i) ret += a[i];
        return ret;
    }
    T query(int l, int r){
        return query(r) - query(l-1);
    }
};