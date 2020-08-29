/*
for storing size of subtree (cartesian tree),
    just add another variable (sz, remove key) to each node.
    The time to pull up (update) the size provided as comments.
    This enables accessing Kth-key and num of keys less than K.
Other query/update/propagation techniques can be used as well.
 */

// the BBST feature will no longer function if using as dynamic array
struct node{
    int key, sz; // key -> bbst, sz -> dynamic array
    int v;
    int pri; // priority
    node* l; node* r;
    node(int key, int v) : key(key), sz(1), v(v), pri(rand()), l(NULL), r(NULL){}
}*head;

int getsize(node* now){
    if(now)return now->sz;
    return 0;
}
void update(node* now){
    if(now){
        now->sz = getsize(now->l) + getsize(now->r) + 1;
    }
}

// current function: dynamic array. See comments for bbst
void split(node* now, int k, node*& a, node*& b){ // <=k, >k
    if(!now){a = b = NULL;return;}
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
    if(a->pri < b->pri){
        a->r = join(a->r, b);
        update(a);
        return a;
    }
    b->l = join(a, b->l);
    update(b);
    return b;
}

/*
quick insert:
    if now null
        now = new node
    if current node has higher priority than new node
        descent the tree like usual
    else
        split -> assign as children to new node
    update(now)

quick erase:
    if now null
        well, do nothing
    if found
        join the deleted node's children
    else
        descent the tree like usual
    update(now)

the slow variant = just split everything lmao
*/


// class version

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