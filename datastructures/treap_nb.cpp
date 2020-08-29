// the BBST feature will no longer function if using as dynamic array
// supports reversing (an example of lazy propagation)
struct node{
    int key, sz; // key -> bbst, sz -> dynamic array
    int v;
    int pri; // priority
    bool flip;
    node* l; node* r;
    node(int key, int v) : key(key), sz(1), v(v), pri(rand()), flip(0), l(NULL), r(NULL){}
}*head;

inline int getsize(node* now){ return (now) ? now->sz : 0; }
inline void update(node* now){
    if(now){
        now->sz = getsize(now->l) + getsize(now->r) + 1;
    }
}
inline void apply(node* now){
    if(now){
        now->flip ^= 1;
        swap(now->l, now->r);
    }
}
inline void prop(node* now){
    if(now && now->flip){
        now->flip = 0;
        apply(now->l);
        apply(now->r);
    }
}

// current function: dynamic array. See comments for bbst
void split(node* now, int k, node*& a, node*& b){ // <=k, >k
    if(!now){a = b = NULL;return;}
    prop(now);
    if(getsize(now->l) + 1 <= k){ // now->key <= k
        a = now;
        split(now->r, k-getsize(now->l)-1, a->r, b); // (now->r, k, a->r, b)
    }else{
        b = now;
        split(now->l, k, a, b->l);
    }
    update(now);
}

node* join(node* a, node* b){
    if(!a)return b; if(!b)return a;
    prop(a); prop(b);
    if(a->pri < b->pri){
        a->r = join(a->r, b);
        update(a);
        return a;
    }
    b->l = join(a, b->l);
    update(b);
    return b;
}

// quick insert and delete
// the slow variant = just split everything lmao
// current function: dynamic array. see comments for bbst

// insert after node k. so 0<=k<=size
void insert(node*& now, int k, node* ins){ // (now, ins) no need k
    prop(now);
    if(!now)now = ins;
    else if(ins->pri > now->pri){
        split(now, k, ins->l, ins->r), now = ins; // by index => by key
    }else{
        int sl = getsize(now->l); // no need sl
        // (ins->key < now->key ? now->l : now->r, ins)
        insert(k < sl+1 ? now->l : now->r, k < sl+1 ? k : k-sl-1, ins);
    }
    update(now);
}
// if erase key, have to check if key exists; if(!now)
node* erase(node*& now, int k){ // 1<=k<=size
    prop(now);
    int sl = getsize(now->l); // no need sl
    node* erased = NULL;
    if(sl+1 == k){ // now->key == k
        erased = now;
        now = join(now->l, now->r);
    }else{
        // (k < now->key ? now->l : now->r, k)
        erased = erase(k < sl+1 ? now->l : now->r, k < sl+1 ? k : k-sl-1);
    }
    update(now);
    return erased;
}

/*
reversing (l, r)
split so you get the treap in range (l, r)
apply(the head node of (l,r))
join everything back
*/