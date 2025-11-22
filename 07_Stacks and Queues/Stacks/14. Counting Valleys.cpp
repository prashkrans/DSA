/* Stack problem 13. Counting Valleys 
An avid hiker keeps meticulous records of their hikes. During the last hike that took exactly  steps, for every step it was 
noted if it was an uphill, , or a downhill,  step. Hikes always start and end at sea level, and each step up or down represents
a unit change in altitude. We define the following terms:

A mountain is a sequence of consecutive steps above sea level, starting with a step up from sea level and ending with a step down
to sea level.
A valley is a sequence of consecutive steps below sea level, starting with a step down from sea level and ending with a step up to
sea level.
Given the sequence of up and down steps during a hike, find and print the number of valleys walked through.

hr - https://www.hackerrank.com/challenges/counting-valleys/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=warmup

Example 1:
steps = 8 path = [DDUUUUDD]
The hiker first enters a valley  units deep. Then they climb out and up onto a mountain  units high. Finally, the hiker returns to 
sea level and ends the hike.

Function Description:
Complete the countingValleys function in the editor below.
countingValleys has the following parameter(s):
int steps: the number of steps on the hike
string path: a string describing the path
Returns:
int: the number of valleys traversed
Input Format

The first line contains an integer, the number of steps in the hike.
The second line contains a single string, of  characters that describe the path.

Constraints:
2<=steps<=10^6
path[i] belongs to {'U', 'D'}
*/

/*
 * Complete the 'countingValleys' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER steps
 *  2. STRING path
 */

int countingValleys(int steps, string path) {
    stack<char> s;
    int count = 0;
    for(int i=0; i<path.size(); i++) {
        if(s.empty()||(s.top()==path[i])) s.push(path[i]);
        else if(s.top()=='U' && path[i]=='D') s.pop();
        else if(s.top()=='D' && path[i]=='U') {
            s.pop();
            if(s.empty()) count++;
        }
    }
    return count;
}

