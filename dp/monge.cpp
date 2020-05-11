/*
Let’s use some 2D dp for example: Given an array of N integers, take K non-adjacent integers so that their sum is minimized.
DP[N][K] = solution for taking K integers from first N integers = min(DP[N-1][K], DP[N-2][K-1] + A[N])

Let F(X) = DP[N][X]

This problem has a property: F(X+1)-F(X) <= F(X+2)-F(X+1), which is called monge-property. The F(X) function creates an envelope (non-decreasing).

Let SlopeF(X) = F(X+1)-F(X)
We can directly compute F(X) by taking the smallest Y where SlopeF(X) = SlopeF(Y), and F(X) = F(Y) + (X-Y)*SlopeF(X)

This is abusable. For a slope C, we can find the smallest Y where SlopeF(Y) = C, by adding C as a penalty for taking integers. Let G(X) = F(X) - X*C. Smallest Y, SlopeF(Y) = C is where G(Y) is minimum. You can draw G to clarify.

Because of this, now the dp becomes:
DP[N] = minimum G(1..K) that uses C as penalty = min(DP[N-1], DP[N-2] + A[N] - C)

Back to the problem. To find F(K), binary search on a slope C so that SlopeF(K) = C. To know if C <= SlopeF(K), use the above method to find the smallest Y, where SlopeF(Y) = C. If Y <= K, then C <= SlopeF(K).

Finally after the last binary search, you know the value of SlopeF(K) = C and you can find DP[N].
F(K) = DP[N] + C*K.

Congratulations, you have reduced a linear state into logarithmic complexity.
*/