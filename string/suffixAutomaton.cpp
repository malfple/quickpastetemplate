/*
or SAM. Builds online char-by-char, just call sam_extend(c).
This implementation uses dynamic pointer because SAM is often used with DP.
It also use map to achieve O(N) memory, however O(N log K) build time. Change to array to speed up build time but sacrificing memory.
*/

struct node{
    int len, link;
    map<char, int> next;
}st[2 * N];
int pcntr, last;
inline int alloc(int len=0, int link=-1){
    st[pcntr].len = len;
    st[pcntr].link = link;
    return pcntr++;
}
inline void sam_init(){ pcntr = 0; last = alloc(); }
inline void sam_extend(char c){
    int now = alloc(st[last].len + 1);
    int p = last;
    while(p != -1 && !st[p].next.count(c)){
        st[p].next[c] = now;
        p = st[p].link;
    }
    if(p == -1){
        st[now].link = 0;
    }else{
        int q = st[p].next[c];
        if(st[p].len + 1 == st[q].len){
            st[now].link = q;
        }else{
            int clone = alloc(st[p].len + 1, st[q].link);
            st[clone].next = st[q].next;
            while(p != -1 && st[p].next[c] == q){
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = st[now].link = clone;
        }
    }
    last = now;
}
