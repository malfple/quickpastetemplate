# 2-SAT

A special case of boolean satisfiability. Can a boolean equation equates to true?

### 1-SAT

to help understand 2-sat

f = x1 ∧ x2 ∧ ...  ∧ xn

If there aren’t both xi and ¬xi in f, then f is satisfiable.

### 2-SAT

f = (x1 ∨ y1) ∧ (x2 ∨ y2) ∧ ...  ∧ (xn ∨ yn)

xi ∨ yi =  xi → yi =  yi → xi

Create a graph with 2n vertices, for each i, make 2 directed edges from ¬xi to yi and from ¬yi to xi.

f is not satisfiable if both xi and ¬xi is in the same SCC(see Tarjan above).

Note that for ⊕, you can convert it into the above equation.
x ⊕ y = (x1 ∨ y1) ∧ (¬x1 ∨ ¬y1)

### Backtracking

if  xi → ¬xi then xi has to be FALSE. This is valid for the opposite. This is also why if they are in the same SCC, a contradiction occurs. To assign values to xi, you can use topological sort. Anything that comes earlier has to be FALSE. In the above implementation, you can use scc[i] (see NOTE).

Sometimes you can just if(scc[i] > scc[-i]) i = false, else i = true

if in doubt:

You need to record the members of each scc as an addition to the tarjan implementation above.
```
iterate i = sccid..1:
if scc[i] doesn’t have value, set to false
set the negation of the members of scc[i] to their respective value. The scc that they’re in, now have a value.
if scc[i] has value true, all of its children has to be true
```