/* DP-Problem 11 - Rod Cutting Problem I
Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. 
Determine the maximum value obtainable by cutting up the rod and selling the pieces.
Given L, arrays price(i) and lenght(i).
GFG - https://www.geeksforgeeks.org/cutting-a-rod-dp-13/

This problem is exactly the same problem as unbounded knapsack problem with just a change in the name of variables.
RCP I	==	UKP
L 		== 	W
p[i] 	== 	v[i]
l[i]	== 	w[i]
*/

//	1.	DP - Tabulation (Top Down)
//		Running Time = O(Ln)
//		Extra Space = O(Ln)
//		Refer DP-Problem 5b. Unbounded Knapsack Problem