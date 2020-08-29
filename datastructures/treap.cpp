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

void split_idx(node* now, int k, node*& a, node*& b){ // <=k, >k
    if(!now){a = b = NULL;return;}
    prop(now);
    if(getsize(now->l) + 1 <= k){
        a = now;
        split_idx(now->r, k-getsize(now->l)-1, a->r, b);
    }else{
        b = now;
        split_idx(now->l, k, a, b->l);
    }
    update(now);
}
void split_key(node* now, int k, node*& a, node*& b){ // <=k, >k
    if(!now){a = b = NULL;return;}
    prop(now);
    if(now->key <= k){
        a = now;
        split_key(now->r, k, a->r, b);
    }else{
        b = now;
        split_key(now->l, k, a, b->l);
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

// insert after node k. so 0<=k<=size
void insert_idx(node*& now, int k, node* ins){
    prop(now);
    if(!now)now = ins;
    else if(ins->pri > now->pri){
        split_idx(now, k, ins->l, ins->r), now = ins;
    }else{
        int sl = getsize(now->l);
        insert_idx(k < sl+1 ? now->l : now->r, k < sl+1 ? k : k-sl-1, ins);
    }
    update(now);
}
void insert_key(node*& now, node* ins){
    prop(now);
    if(!now)now = ins;
    else if(ins->pri > now->pri){
        split_key(now, k, ins->l, ins->r), now = ins;
    }else{
        insert_key(ins->key < now->key ? now->l : now->r, ins);
    }
    update(now);
}
node* erase_idx(node*& now, int k){ // 1<=k<=size
    prop(now);
    int sl = getsize(now->l);
    node* erased = NULL;
    if(sl+1 == k){
        erased = now;
        now = join(now->l, now->r);
    }else{
        erased = erase_idx(k < sl+1 ? now->l : now->r, k < sl+1 ? k : k-sl-1);
    }
    update(now);
    return erased;
}
node* erase_key(node*& now, int k){ // 1<=k<=size
    prop(now);
    node* erased = NULL;
    if(now->key == k){
        erased = now;
        now = join(now->l, now->r);
    }else{
        erased = erase_key(k < now->key ? now->l : now->r, k);
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

// class version (deprecated)

template<typename __key, typename __val>
class Treap{
private:
    struct node{
        __key key; __val v;
        int pri;
        node* l; node* r;
        node(__key key) : key(key), v(0), pri(rand()), l(NULL), r(NULL){}
    }*head;
    int s;
    
    void split(node* now, __key k, node*& a, node*& b){ // <=k, >k
        if(!now){a = b = NULL;return;}
        if(now->key <= k){
            a = now;
            split(now->r, k, a->r, b);
        }else{
            b = now;
            split(now->l, k, a, b->l);
        }
        //pull(now);
    }
    
    node* join(node* a, node* b){
        if(!a)return b; if(!b)return a;
        if(a->pri < b->pri){
            a->r = join(a->r, b);
            //pull(a);
            return a;
        }
        b->l = join(a, b->l);
        //pull(b);
        return b;
    }
    
    node* find(node* now, __key key){
        if(!now)return now;
        if(now->key == key)return now;
        else if(now->key > key)return find(now->l, key);
        else return find(now->r, key);
    }
    
    node* insert(__key key){
        s++;
        node* tmp,* add = new node(key);
        split(head, key, head, tmp);
        head = join(join(head, add), tmp);
        return add;
    }
public:
    Treap() : head(NULL), s(0){}
    
    bool hasKey(__key key){return find(head, key);}
    int size(){return s;}
    
    __val& operator[](__key key){
        node* t = find(head, key);
        if(!t){
            t = insert(key);
        }
        return t->v;
    }

    void erase(__key key){
        s--;
        node* target,* tmp;
        split(head, key, head, tmp);
        split(head, key-1, head, target);
        head = join(head, tmp);
        if(target)delete target;
    }
};