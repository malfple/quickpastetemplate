/*
Add string -> just call addPat(the string)
then call buildAutomaton() and searchStr(the searched string)
to print occurrences -> iterate through patIdx, you get index patIdx[i], etc
 */

const int A = 256; // alphabet size

struct node{
    node* next[A],* fail,* suflink;
    int id;
    node() : fail(NULL), suflink(NULL), id(-1){
        FOR(i,A)next[i] = NULL;
    }
}head;

vector<string>pats; // stores unique strings
vector<int>patIdx; // stores index of string in pats
vector<vector<int> >match;

void addPat(string pat){ // returns string id
    node* now = &head;
    FOR(i,pat.size()){
        if(!now->next[pat[i]]) now->next[pat[i]] = new node();
        now = now->next[pat[i]];
    }
    if(now->id == -1){ // prevents doubles
        now->id = pats.size();
        pats.pb(pat);
        match.pb(vector<int>());
    }
    patIdx.pb(now->id);
}

queue<node*>q;
void buildAutomaton(){
    q.push(&head);
    while(!q.empty()){
        node* now = q.front();
        q.pop();
        FOR(i,A){
            if(!now->next[i])continue;
            node* nt = now->next[i];
            nt->fail = now->fail;
            while(nt->fail && !nt->fail->next[i])nt->fail = nt->fail->fail;
            if(nt->fail)nt->fail = nt->fail->next[i];
            else nt->fail = &head;
            if(nt->fail->id != -1)nt->suflink = nt->fail;
            else nt->suflink = nt->fail->suflink;
            q.push(nt);
        }
    }
}

void searchStr(string str){
    node* now = &head;
    FOR(i,str.size()){
        while(now != &head && !now->next[str[i]])now = now->fail;
        if(now->next[str[i]]){
            now = now->next[str[i]];
            for(node* curr = now; curr; curr = curr->suflink){ // iterate links
                if(curr->id == -1)continue;
                match[curr->id].pb(i - pats[curr->id].size() + 1);
            }
        }
    }
}