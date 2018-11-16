/*
for storing size of subtree (cartesian tree),
	the time to pull up the size provided as comments.
	This enables accessing Kth-key and num of keys less than K.
 */

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