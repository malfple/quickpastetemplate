/*
Similar to Dinic’s MaxFlow
Special case:
    1. negative edge, do bellman-ford 1x to initialize potentials
    2. negative cycle, things get complicated. Generally, always use negative cycle until depleted.
Often, dfs is not needed, and traditional backtrack is enough.
    remove level[N], lastEdge[N], and use epar[N] that stores the index of the reverse edge
    used to reach node during dijkstra.
Might even be faster. LOL ;-)
 */

struct edge{int to, flow, cap, cost, rev;};
// lst, N,SRC,SINK, same as dinic's

void addEdge(int a, int b, int cap, int cost){
    int sa = lst[a].size(), sb = lst[b].size();
    lst[a].pb({b, 0, cap, cost, sb});
    lst[b].pb({a, 0, 0, -cost, sa}); // here cap=0, cannot make 2 way, have to call this function twice, because of cost
}

int level[N]; // to prevent infinite loop during dfs
int potential[N];
int dist[N];
int lastEdge[N];

int ccost(int now, edge& e){ // compute cost w/ potentials
    return e.cost + potential[now] - potential[e.to];
}

// almost like dinic's bfs, but dijkstra instead
bool dijkstra(){
    FOR(i,N)potential[i] += dist[i]; //update potentials

    priority_queue<pii>pq;
    memset(dist, -1, sizeof dist);
    memset(level, 0, sizeof level);

    level[SRC] = 0;
    pq.push(mp(0, SRC));
    dist[SRC] = 0;
    while(!pq.empty()){
        int d = -pq.top().F;
        int now = pq.top().S;
        pq.pop();

        if(dist[now] != d)continue;

        FOR(i,lst[now].size()){
            edge& e = lst[now][i];
            if(e.flow < e.cap){
                if(dist[e.to] != -1 && dist[e.to] <= d+ccost(now, e))continue;
                dist[e.to] = d+ccost(now, e);
                level[e.to] = max(level[e.to], level[now]+1);
                // epar[e.to] = e.rev;
                pq.push(mp(-d-ccost(now, e), e.to));
            }
        }
    }
    return dist[SINK] != -1;
}

// dfs pretty much the same as dinic's + some lines
int dfs(int now, int flow){
    // add this line inside for loop
        if(level[e.to] < level[now])continue; //going back
    // condition for level changed
        if(dist[e.to] == dist[now] + ccost(now, e))
}

int totalflow, totalcost;
void MCMF(){
    totalflow = totalcost = 0;
    while(dijkstra()){
        memset(lastEdge, 0, sizeof lastEdge);
        int flow = dfs(SRC, OO);
        totalflow += flow;
        totalcost += flow * (dist[SINK] + potential[SINK]);
    }
}
// traditional backtrack, put inside while(dijkstra()) loop
        int flow = OO;
        for(int p = SINK; p != SRC; p = lst[p][epar[p]].to){
            edge& e = lst[lst[p][epar[p]].to][lst[p][epar[p]].rev];
            flow = min(flow, e.cap - e.flow);
        }
        for(int p = SINK; p != SRC; p = lst[p][epar[p]].to){
            edge& e = lst[p][epar[p]];
            lst[e.to][e.rev].flow += flow;
            e.flow -= flow;
        }