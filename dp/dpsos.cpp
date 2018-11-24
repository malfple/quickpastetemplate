/*
Given array A[] of 2^N integers,
    find sum of all F(x), where F(x) = sum of all A[i] where x&i=i (i is a submask of x)
 */


// 3^N  This one can be used for various other problems. flexible.
// iterate over all the masks
for (int mask = 0; mask < (1<<n); mask++){
    F[mask] = A[0];
    // iterate over all the subsets of the mask
    for(int i = mask; i > 0; i = (i-1) & mask){
        F[mask] += A[i];
    }
}
//N * 2^N
for(int i = 0; i<(1<<N); ++i)
    F[i] = A[i];
for(int i = 0;i < N; ++i){
    for(int mask = 0; mask < (1<<N); ++mask){
    if(mask & (1<<i))
            F[mask] += F[mask^(1<<i)];
    }
}
