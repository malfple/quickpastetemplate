/*
Range Update Range Query (Sum)
All indexes of update and get are 1-based
 */

const int N = 100005; // size
const int H = 16; // height

ll tree[2*N];
ll pend[N];

void apply(int x, ll v, int s){
    tree[x] += v*s;
    if(x < n)pend[x] += v;
}    

void calc(int x, int s){
    tree[x] = tree[x<<1] + tree[x<<1|1] + pend[x]*s;
}

void build(int x){
    int s = 1;
    while(x > 1){
        x >>= 1;
        s <<= 1;
        calc(x, s);
    }
}

void push(int x){
    for(int h = H, s = 1<<(H-1); h>0; h--, s>>=1){
        int i = x >> h;
        if(pend[i]){
            apply(i<<1, pend[i], s);
            apply(i<<1|1, pend[i], s);
            pend[i] = 0;
        }
    }
}

void update(int l,int r,ll v){
    l += n-1; r += n;
    int lt = l, rt = r;

    for(int s=1; l<r; l>>=1, r>>=1, s<<=1){
        if(l&1) apply(l++, v, s);
        if(r&1) apply(--r, v, s);
    }
    build(lt);
    build(rt-1);
}

ll get(int l,int r){
    l += n-1; r += n;
    push(l);
    push(r-1);

    ll ret = 0;
    for(; l<r; l>>=1, r>>=1){
        if(l&1)ret += tree[l++];
        if(r&1)ret += tree[--r];
    }
    return ret;
}