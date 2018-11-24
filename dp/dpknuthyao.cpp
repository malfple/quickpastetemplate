/*
dp[i][j] = min i<k<j {dp[i][k] + dp[k or k+1][j] + C[i][j]}

Like dp dnc, make sure A[i][j-1] <= A[i][j] <= A[i+1][j] to enable mid optimize
To make sure that, the cost function C[i][j] has to fulfil 2 requirement:
For a,b,c,d, (a <= b <= c <= d)
    1. Quadrangle inequality, C[a][c] + C[b][d] <= C[a][d] + C[b][c]
    2. Monotonicity, C[b][c] <= C[a][d]
 */

REP(s,1,n){ // s size of substring
    REP(l,1,n-s+1){
        int r = l + s - 1;
        if(s == 1){ // base case
            dp[l][r] = some base case value;
            mid[l][r] = l;
            continue;
        }
        dp[l][r] = INF;
        int ml = mid[l][r-1];
        int mr = min(r-1, mid[l+1][r]);
        REP(i,ml,mr){
            ll tmp = dp[l][i] + dp[i+1][r] + C[l][r];
            if(tmp < dp[l][r]){
                dp[l][r] = tmp;
                mid[l][r] = i;
            }
        }
    }
}