// Z[i] = LCP of string s[0..N] and s[i..N]

l = r = 0;
Z[0] = n;
for(int i = 1; i < s.size(); i++) {
    if(i > r) { // over bound -> manual widen
        l = r = i;
        while(r < s.size() && s[r-l] == s[r]) r++;
        Z[i] = r-l; r--;
    }else{
        if(Z[i-l] < r-i+1) Z[i] = Z[i-l];
        else{ // lcp exceeds bound -> manual widen
            l = i;
            while(r < s.size() && s[r-l] == s[r]) r++;
            Z[i] = r-l; r--;
        }
    }
}
