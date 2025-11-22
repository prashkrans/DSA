/* 17. Poisonous Plants
https://www.hackerrank.com/challenges/poisonous-plants/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=stacks-queues
*/

//	Method 1. Basically nseLeft + variable day to count the nth day in which a plant i dies.
//	Running time = O(n)
//	Auxiliary space = O(n) due to the stack

int poisonousPlants(vector<int> p) {
    int day, maxDay = 0;
    stack<pair<int, int>> s;
    for(int i=0; i<p.size(); i++) {
        day = 0;
        while(!s.empty() && s.top().first >= p[i]) {
            day = max(day, s.top().second);
            s.pop();
        }
        if(!s.empty()) day += 1;
        else day = 0;
        maxDay = max(maxDay, day);
        s.push({p[i], day});
    }
    return maxDay;
}

/* Dry run
7
6 5 8 4 7 10 9

+6, 0
-6, 0		+5, 0
5, 0		+8, 1
-5, 0 		-8, 1		+4, 0
4, 0		+7, 1
4, 0		7, 1		+10, 1
- 10, 1 	4, 0		9, 2
*/	