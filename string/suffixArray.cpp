const int N = 1e5 + 5;
const int H = 17;

int n;
string str; // 0 based ofc
int sparse[H+1][N]; // 0 based as well
int pow2[H+1]; // power of 2
int SA[N]; // 1-based HUE

pair<pii,int> buffer[N], copyy[N]; // 0 based, sorting
int cnt[N];

void radix(int sz){ // sorts 0..sz-1 on buffer
    int pclear = 0;
    FOR(i,n)copyy[i] = buffer[i];
    FOR(i,n){
        while(pclear <= buffer[i].F.S)cnt[pclear++] = 0;
        cnt[buffer[i].F.S]++;
    }
    REP(i,1,pclear-1)cnt[i] += cnt[i-1];
    FORD(i,n) buffer[--cnt[copyy[i].F.S]] = copyy[i];

    pclear = 0;
    FOR(i,n)copyy[i] = buffer[i];
    FOR(i,n){
        while(pclear <= buffer[i].F.F)cnt[pclear++] = 0;
        cnt[buffer[i].F.F]++;
    }
    REP(i,1,pclear-1)cnt[i] += cnt[i-1];
    FORD(i,n) buffer[--cnt[copyy[i].F.F]] = copyy[i];
}

void buildSA(){ // from str with length n
    pow2[0] = 1;
    REP(i,1,H)pow2[i] = pow2[i-1]<<1;

    FOR(i,n)sparse[0][i] = str[i];
    REP(i,1,H){
        FOR(j,n){
            buffer[j] = {{sparse[i-1][j], 0}, j};
            if(j+pow2[i-1] < n) // 2nd char inside bounds
                buffer[j].F.S = sparse[i-1][j+pow2[i-1]];
        }
        radix(n);

        pii prev = {-1, -1}; int id = 0;
        FOR(j,n){
            if(buffer[j].F != prev){
                prev = buffer[j].F;
                id++;
            }
            sparse[i][buffer[j].S] = id;
        }
    }

    FOR(i,n) SA[sparse[H][i]] = i;
}

// longest common prefix, index a and b IN the sparse table
int LCP(int a, int b){
    int ret = 0;
    REV(i,H,0){
        if(sparse[i][a] == sparse[i][b]){
            ret += pow2[i];
            a += pow2[i];
            b += pow2[i];
        }
    }
    return ret;
}