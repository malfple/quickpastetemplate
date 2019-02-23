/*
This tree is used for min/max query on polynomials/functions,
    where each pair can only intersect at most once.
    Note that each polynomial only occupies one segment,
    so making a dynamic version is easy (for memory issues).
 */

// getv(i, x) = get value of polynom i at x
int tree[4*N];
void add(int idx, int left, int right, int v){
    int mid = (left+right)/2;
    bool flipleft = getv(v, left) < getv(tree[idx], left);
    bool flipmid = getv(v, mid) < getv(tree[idx], mid);
    if(flipmid)swap(tree[idx], v);
    if(left == right) // do nothing
    else if(flipleft == flipmid) add(idx<<1|1, mid+1, right, v);
    else add(idx<<1, left, mid, v);
}
// for query, use stabbing query



// dynamic version
struct DynamicLiChao{
    struct node{
        int v;
        node* lf,* rg;
        node(int v=0, node* lf=NULL, node* rg=NULL) : v(v), lf(lf), rg(rg){}
    }*head;
    
    DynamicLiChao(){
        head = new node();
    }
    
    void add(int v, node* now, int left, int right){
        if(v == 0)return;
        int mid = (left+right)/2;
        bool flipleft = getv(v, left) < getv(now->v, left);
        bool flipmid = getv(v, mid) < getv(now->v, mid);
        if(flipmid){
            swap(now->v, v);
        }
        if(left == right){
            // do nothing
        }else if(flipleft != flipmid){
            if(!now->lf)now->lf = new node();
            add(v, now->lf, left, mid);
        }else{
            if(!now->rg)now->rg = new node();
            add(v, now->rg, mid+1, right);
        }
    }
    void add(int v){
        add(v, head, 1, M);
    }
    
    ll query(int x, node* now, int left, int right){
        if(!now)return INF;
        if(left == right)return getv(now->v, x);
        int mid = (left+right)/2;
        if(x <= mid)return min(getv(now->v, x), query(x, now->lf, left, mid));
        else return min(getv(now->v, x), query(x, now->rg, mid+1, right));
    }
    ll query(int x){
        return query(x, head, 1, M);
    }
}