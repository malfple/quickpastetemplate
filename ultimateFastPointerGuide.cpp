node nodes[N];
int pcntr = 0;
node* alloc(/*constructor parameters*/){
    nodes[pcntr] = node(/*constructor parameters*/);
    return &nodes[pcntr++];
}
// change all new node(...) with alloc(...)
// to reset => pcntr = 0