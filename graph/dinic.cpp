/*
How to Backtrack: observe the edge.flow
Using Dinic’s for max bipartite matching achieves same speed as hopcroft-karp
 */

const int N = 2505; // nodes numbered 1..N-2
const int SRC = 0; // source
const int SINK = N-1; // sink

struct edge{int to, flow, cap, rev;};
vector<edge> lst[N]; // adjlist

void addEdge(int a, int b, int cap){
    int sa = lst[a].size(), sb = lst[b].size();
    lst[a].pb({b, 0, cap, sb});
    lst[b].pb({a, 0, 0, sa}); // here cap=0 cuz 1 way
}

int level[N]; // level graph
int lastEdge[N]; // to keep used paths from being flowed again

bool bfs(){ // create level graph, returns false if no more flow is possible
    queue<int>q;
    memset(level, -1, sizeof level);

    q.push(SRC);
    level[SRC] = 0;
    while(!q.empty()){
        int now = q.front();
        q.pop();

        FOR(i,lst[now].size()){
            edge& e = lst[now][i];
            if(level[e.to] != -1)continue;
            if(e.flow < e.cap){ // flow still possible
                level[e.to] = level[now]+1;
                q.push(e.to);
            }
        }
    }
    return level[SINK] != -1;
}

int dfs(int now, int flow){ // do the flow
    if(now == SINK)return flow;

    int ret = 0;
    for(int& i = lastEdge[now]; i<lst[now].size(); i++){
        edge& e = lst[now][i];
        if(e.flow == e.cap)continue; // no flow
        if(level[e.to] == level[now]+1){
            int curr = dfs(e.to, min(flow, e.cap - e.flow));
            if(curr > 0){
                e.flow += curr; // forward flow
                lst[e.to][e.rev].flow -= curr; // residual
                flow -= curr;
                ret += curr;
                if(flow == 0)return ret; // if flow to this node is already depleted, i.e. there is a bottleneck far before this node
            }
        }
    }
    return ret;
}

int maxFlow(){
    int ret = 0;
    while(bfs()){
        memset(lastEdge, 0, sizeof lastEdge);
        ret += dfs(SRC, OO);
    }
    return ret;
}