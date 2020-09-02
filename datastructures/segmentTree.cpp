const int N = 1e5 + 5;

struct _data{
    ll sum;
}nil{0}; // define nil
_data combine(const _data& a, const _data& b){
    _data c;
    c.sum = a.sum + b.sum;
    return c;
}

_data tree[2*N];
ll pend[2*N];

#define RANGE 1,1,n // change when needed
#define CL idx+1
#define CR idx+2*(mid-left+1)

inline void apply(int idx, ll v, int s){ // change when needed
    tree[idx].sum += v * s;
    pend[idx] += v;
}
inline void prop(int idx, int left, int mid, int right){
    if(pend[idx]){
        apply(CL, pend[idx], mid-left+1);
        apply(CR, pend[idx], right-mid);
        pend[idx] = 0;
    }
}

ll sarr[N]; // source array (can be any type)
void build(int idx, int left, int right){
    pend[idx] = 0;
    if(left == right){
        tree[idx].sum = sarr[left]; // change when need
    }else{
        int mid = (left+right)/2;
        build(CL, left, mid);
        build(CR, mid+1, right);
        tree[idx] = combine(tree[CL], tree[CR]);
    }
}

void update(int idx, int left, int right, int l, int r, ll v){
    if(left >= l && right <= r){
        apply(idx, v, right-left+1);
    }else if(right < l || left > r){
        return;
    }else{
        int mid = (left+right)/2;
        prop(idx, left, mid, right);
        update(CL, left, mid, l, r, v);
        update(CR, mid+1, right, l, r, v);
        tree[idx] = combine(tree[CL], tree[CR]);
    }
}

_data query(int idx, int left, int right, int l, int r){
    if(left >= l && right <= r){
        return tree[idx];
    }else if(right < l || left > r){
        return nil;
    }else{
        int mid = (left+right)/2;
        prop(idx, left, mid, right);
        return combine(query(CL, left, mid, l, r),
            query(CR, mid+1, right, l, r));
    }
}