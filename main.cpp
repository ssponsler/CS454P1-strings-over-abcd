/*

* = not sure

1. Sigma: vector of all postibe symbols
2. Queue: Vector of all states
3. Delta: 2-D Vector of all resulting states, EX: D[current state, given input] = resulting state
4. *Final: boolean vector (length k, k = num of states) 1 for accepting state, 0 for reject

For Counting
1. *Prev: 
2. *Next: 

*Functions:
build: using sigma and language rules, generate queue, delta, and final
*Encode: given string in langauge M, using base-4 conversion return a decimal number
*Decode: given a decimal number, using base 4 conversion return a corresponding string
*count: recurively count number of all possible valid string of given length N

*/
