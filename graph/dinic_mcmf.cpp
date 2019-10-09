/*
Similar to Dinic’s MaxFlow
Special case:
    1. negative edge, do bellman-ford 1x to initialize potentials
    2. negative cycle, things get complicated. Generally, always use negative cycle until depleted.
This implementation uses normal iterative backtracking.
    Sometimes, a dfs similar to dinic’s can be used (don’t forget to maintain level[N] and lastEdge[N]).
 */

struct edge{int to, flow, cap, cost, rev;};
// lst, N,SRC,SINK, same as dinic's

void addEdge(int a, int b, int cap, int cost){
    int sa = lst[a].size(), sb = lst[b].size();
    lst[a].pb({b, 0, cap, cost, sb});
    lst[b].pb({a, 0, 0, -cost, sa}); // here cap=0, cannot make 2 way, have to call this function twice, because of cost
}

int potential[N];
int dist[N];
int epar[N];

int ccost(int now, edge& e){ // compute cost w/ potentials
    return e.cost + potential[now] - potential[e.to];
}

// almost like dinic's bfs, but dijkstra instead
bool dijkstra(){
    FOR(i,N)potential[i] += dist[i]; //update potentials

    priority_queue<pii>pq;
    FOR(i,N)dist[i] = OO;

    pq.push({0, SRC});
    dist[SRC] = 0;
    while(!pq.empty()){
        int d = -pq.top().F;
        int now = pq.top().S;
        pq.pop();

        if(dist[now] != d)continue;

        FOR(i,lst[now].size()){
            edge& e = lst[now][i];
            if(e.flow < e.cap){
                if(dist[e.to] != OO && dist[e.to] <= d+ccost(now, e))continue;
                dist[e.to] = d+ccost(now, e);
                epar[e.to] = e.rev;
                pq.push({-d-ccost(now, e), e.to});
            }
        }
    }
    return dist[SINK] != OO;
}

int totalflow, totalcost;
void MCMF(){
    totalflow = totalcost = 0;
    while(dijkstra()){
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
        totalflow += flow;
        totalcost += flow * (dist[SINK] + potential[SINK]);
    }
}