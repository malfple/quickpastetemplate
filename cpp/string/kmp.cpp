/*
always take advantage of the failure function
 */

//str -> searched string
//pat -> search pattern
kmp[0] = -1;
for(int i=0, j=-1; i < pat.size(); i++, j++){
    while ((j >= 0) && (pat[i] != pat[j])) j = kmp[j];
    kmp[i+1] = j+1;
}
int found = -1;
for(int i=0, j=0; i < str.size(); i++, j++){
    while ((j >= 0) && (str[i] != pat[j])) j = kmp[j];
    if (j+1 == pat.size()){
        found = i-j;
        break;
    }
}