int sz[N], depth[N], dpar[N];

void dfs(int now,int par){
    dpar[now] = par; // direct parent
    sz[now] = 1; // size of subtree
    FOR(i,lst[now].size()){
        int to = lst[now][i].ff;
        if(to == par)continue;
        depth[to] = depth[now]+1;
        dfs(to, now);
        sz[now] += sz[to];
    }
}

int nodeToSeg[N]; // stores the renumbering
int id; // set to 0
int headFamily[N]; // head of a segment

void decompose(int now,int par){
    nodeToSeg[now] = ++id;

    int bigChild = -1;
    FOR(i,lst[now].size()){
        int to = lst[now][i].ff;
        if(to == par)continue;
        if(bigChild == -1 || sz[to] > sz[bigChild]){
            bigChild = to;
        }
    }
    if(bigChild == -1)return;
    headFamily[bigChild] = headFamily[now];
    decompose(bigChild, now); // to bigChild first
    // to the rest
    FOR(i,lst[now].size()){
        int to = lst[now][i].ff;
        if(to == par || to == bigChild)continue;
        headFamily[to] = to; // new head
        decompose(to, now);
    }
}
// currently only queries lca, comments = query on i =
// query on edge between i and dpar[i]
int query(int a,int b){
    while(1){
        int ha = headFamily[a], hb = headFamily[b];
        if(ha == hb)break;
        if(depth[ha] < depth[hb]){
            // query anything in nodeToSeg[hb]..nodeToSeg[b]
            b = dpar[hb];
        }else{
            // query anything in nodeToSeg[ha]..nodeToSeg[a]
            a = dpar[ha];
        }
    }
    if(depth[a] > depth[b])swap(a,b);
    //if(a != b) query anything in nodeToSeg[a]+1..nodeToSeg[b]
    return b; //b is lca
}