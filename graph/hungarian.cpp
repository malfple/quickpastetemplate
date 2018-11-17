struct Hungarian {
    int n; ll adj[N][N];
    vector<ll> hl,hr,slk;
    vector<int> fl,fr,vl,vr,pre;
    deque<int> q;
    Hungarian() {}
    int check(int i) {
        if (vl[i]=1,fl[i]!=-1) return q.push_back(fl[i]), vr[fl[i]]=1;
        while (i!=-1) swap(i,fr[fl[i]=pre[i]]); return 0;
    }
    void bfs(int s) {
        slk.assign(n,INF); vl.assign(n,0); vr=vl; q.assign(vr[s]=1,s);
        for (ll d;;) {
            for (;!q.empty();q.pop_front()) {
                for (int i=0,j=q.front();i<n;i++) {
                    if (d=hl[i]+hr[j]-adj[i][j],!vl[i]&&d<=slk[i]) {
                        if (pre[i]=j,d) slk[i]=d; else if (!check(i)) return;    
            }}}
            d=INF;
            FOR(i,n) if (!vl[i]&&d>slk[i]) d=slk[i];
            FOR(i,n) {
                if (vl[i]) hl[i]+=d; else slk[i]-=d;
                if (vr[i]) hr[i]-=d;
            }
            FOR(i,n) if (!vl[i]&&!slk[i]&&!check(i)) return;
    }}
    ll solve() {
        fl.assign(n,-1); fr=fl; hl.assign(n,0); hr=hl; pre.assign(n,0);
        FOR(i,n) hl[i]=*max_element(adj[i],adj[i]+n);
        FOR(i,n) bfs(i);
        ll ret=0;
        FOR(i,n) if (adj[i][fl[i]]) ret+=adj[i][fl[i]];
        return ret;
    }
}; //i will be matched with fl[i]