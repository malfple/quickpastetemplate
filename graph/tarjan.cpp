/*
For Strongly Connected Component
For Articulation point, no need to use stack, but need an extra integer parameter par to avoid back edge.
A node is an articulation point if:
    1. it’s root of dfs tree, and have at least 2 children
    2. not root -> there exist a children c where low[c] >= disc[now].
        This means if this node is erased, the graph will split
    3. not root -> disc[c] == low[c]. This node cannot reach anything above.
For Bridge -> find edge that connects 2 articulation points, beware of multiple edges
HELPFUL NOTE: scc[i] stores the id of the scc in a topological order,
    therefore, when using dp(or anything else that needs dfs), just iterate 1..sccid,
    which is already topologically ordered.
 */

vi lst[N];
int disc[N]; // precompute to -1
int low[N];
int scc[N]; // stores the id of scc of node i
stack<int>stk;
bool stkmember[N];

int id, sccid; // set to 0
void tarjan(int now){
    if(disc[now] != -1)return;
    disc[now] = low[now] = ++id;
    stk.push(now);
    stkmember[now] = true;

    FOR(i,lst[now].size()){
        int to = lst[now][i];
        if(disc[to] == -1){
            tarjan(to);
            low[now] = min(low[now], low[to]);
        }else if(stkmember[to]){
            low[now] = min(low[now], disc[to]);
        }
    }

    //if root
    if(disc[now] == low[now]){
        sccid++;
        while(stk.top() != now){
            scc[stk.top()] = sccid;
            stkmember[stk.top()] = false;
            stk.pop();
        }
        scc[now] = sccid;
        stkmember[now] = false;
        stk.pop();
    }
}