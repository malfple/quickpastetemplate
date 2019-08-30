// Z[i] = LCP of string Z[0..N] and Z[i..N]

l = r = 0;
Z[0] = n;
for(int i = 1; i < n; i++) {
    if(i > r) { // over bound -> manual widen
        l = r = i;
        while(r < n && s[r-l] == s[r]) r++;
        Z[i] = r-l; r--;
    }else{
        if(Z[i-l] < r-i+1) Z[i] = Z[i-l];
        else{ // lcp exceeds bound -> manual widen
            l = i;
            while(r < n && s[r-l] == s[r]) r++;
            Z[i] = r-l; r--;
        }
    }
}
