/*
Snatched from: spoj LISTREE
Given a tree, find longest LIS from all possible path
 */

int sz[N];
vi lst[N];

void findsz(int idx, int par){ // precompute size for hld
    sz[idx] = 1;
    FOR(i,lst[idx].size()){
        if(lst[idx][i] == par)continue;
        findsz(lst[idx][i], idx);
        sz[idx] += sz[lst[idx][i]];
    }
}

inline void addto(vi* vec, int a){ // add a to lis array vec
    vi::iterator p = lower_bound(vec->begin(), vec->end(), a);
    if(p == vec->end())vec->pb(a);
    else (*p) = a;
}

inline void combine(vi* a,vi *b){ // combine lis array a and b
    int p = 0;
    while(1){
        if(p >= b->size())break;
        else if(p >= a->size())a->pb((*b)[p]);
        else if(p < b->size()) (*a)[p] = min((*a)[p], (*b)[p]);

        p++;
    }
}

int ans = 0;
vi* alis[N]; // lis
vi* alds[N]; // lds
void dfs(int idx, int par, vi* lis, vi* lds){ // dfs for dsu on tree
    int mx = -1, bigChild = -1;
    FOR(i,lst[idx].size()){ // find big child
        int u = lst[idx][i];
        if(u == par)continue;
        if(sz[u] > mx){
            mx = sz[u];
            bigChild = u;
        }
    }
    addto(lis, idx);
    addto(lds, -idx);

    if(bigChild == -1){ // is leaf, create new vector in alis, alds
        ans = max(ans, (int)lis->size());
        ans = max(ans, (int)lds->size());
        alis[idx] = new vi();
        alis[idx]->pb(idx);
        alds[idx] = new vi();
        alds[idx]->pb(-idx);
    }else if(par != -1 && lst[idx].size() == 2){ // only one child, pass array lis, lds directly
        dfs(bigChild, idx, lis, lds);

        alis[idx] = alis[bigChild];
        alds[idx] = alds[bigChild];
        addto(alis[idx], idx);
        addto(alds[idx], -idx);
    }else{ // more than one child, create copy array
        vi a = *lis;
        vi b = *lds;
        dfs(bigChild, idx, &a, &b);

        alis[idx] = alis[bigChild];
        alds[idx] = alds[bigChild];
        addto(alis[idx], idx);
        addto(alds[idx], -idx);

        combine(lis, alis[idx]);
        combine(lds, alds[idx]);

        FOR(i,lst[idx].size()){ // dfs to other childs
            int u = lst[idx][i];
            if(u == par || u == bigChild)continue;
            a = *lis;
            b = *lds;
            dfs(u, idx, &a, &b);

            addto(alis[u], idx);
            addto(alds[u], -idx);

            combine(alis[idx], alis[u]);
            combine(alds[idx], alds[u]);

            if(i+1 < lst[idx].size()){
                combine(lis, alis[u]);
                combine(lds, alds[u]);
            }

            delete alis[u]; // dont forget to delete
            delete alds[u];
        }
    }
}