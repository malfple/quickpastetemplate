/*
dp[i][j] = min k<j {dp[i-1][k] + C[k][j]}

Make sure A[i][j] <= A[i][j+1] where A is most optimal k, to enable dnc optimizing mids
 */


int dp[K][N];
void dpdnc(int level, int l, int r, int bl, int br){
    if(l > r)return;
    int m = (l+r)/2, best = OO, bm = -1;
    REP(i,bl,min(m, br)){
        int tmp = dp[level-1][i-1] + C[i][m];
        if(tmp < best){
            best = tmp;
            bm = i;
        }
    }
    dp[level][m] = best;
    dpdnc(level, l, m-1, bl, bm);
    dpdnc(level, m+1, r, bm, br);
}
//call
//set base case
REP(i,1,k)dpdnc(i, 1,n, 1,n);
