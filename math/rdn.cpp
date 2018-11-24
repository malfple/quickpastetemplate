/*
Gregorian -> Rata Die = Go to day 1/1/1 in O(1). Plgrzd. fr. L,M.M.K. M.TI.
 */

int rdn(int y, int m, int d) { // Rata Die day one is 0001-01-01
    if(m < 3) y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m-457)/5 + d - 306;
}