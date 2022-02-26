/*Greedy Algo Problem 10x1.b. Job Sequencing
Given a set of N jobs where each jobi has a deadline and profit associated with it. Each job takes 1 unit of time to
complete and only one job can be scheduled at a time. We earn the profit if and only if the job is completed by its
deadline. The task is to find the number of jobs done and the maximum profit.
Note: Jobs will be given in the form (Jobid, Deadline, Profit) associated with that Job.
gfg - https://practice.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1#

Example 1:
Input:
1
4
1 4 20 2 1 10 3 1 40 4 1 30
Output:
2 60

Constraints:
1 <= N <= 10^5
1 <= Deadline <= 100
1 <= Profit <= 500
*/

#include<bits/stdc++.h>
using namespace std;

// A structure to represent a job
struct Job
{
    int id;	 // Job Id
    int dead; // Deadline of job
    int profit; // Profit if job is over before or on deadline
};

int findSet(int t, vector<int> &timeSlotSubset) {
	int parent = timeSlotSubset[t];
	if(parent == t || parent == -1) return parent;
	else {
		timeSlotSubset[t] = findSet(parent, timeSlotSubset);
		return timeSlotSubset[t];
	}
}

void unionOfSets(int t1, int t2, vector<int> &timeSlotSubset) {           //  Union of (t-2, t-1) & (t-1, t) is just making (t-2, t-1) the parent of (t-1, t)
	    timeSlotSubset[t2] = t1;
}

class Solution {
public:
    vector<int> JobScheduling(Job jobNodes[], int n) {
        int maxDeadline = 0;
        for(int i=0; i<n; i++) maxDeadline = max(maxDeadline, jobNodes[i].dead);
        sort(jobNodes, jobNodes+n, [](Job a, Job b) -> bool {return (a.profit > b.profit);});
        vector<int> timeSlotSubset(maxDeadline);
		for(int i=0; i<maxDeadline; i++) timeSlotSubset[i] = i;
        int maxProfitSum = 0;
        int count = 0;
        for(int i=0; i<n; i++) {
			int	dlSlot = jobNodes[i].dead-1;
			int t = findSet(dlSlot, timeSlotSubset);
			if(t!=-1 && t<=dlSlot) {
				unionOfSets(t-1, t, timeSlotSubset);
				maxProfitSum += jobNodes[i].profit;
				count++;
			}
		}			
		//cout<<"The max profit is = "<<maxProfitSum<<"\n";
		return {count, maxProfitSum};
    }
};

int main() {
    int t;
    cin >> t;
    while(t--){
        int n;
        //size of array
        cin >> n;
        Job arr[n];
        //adding id, deadline, profit
        for(int i = 0;i<n;i++){
                int x, y, z;
                cin >> x >> y >> z;
                arr[i].id = x;
                arr[i].dead = y;
                arr[i].profit = z;
        }
        Solution ob;
        //function call
        vector<int> ans = ob.JobScheduling(arr, n);
        cout<<ans[0]<<" "<<ans[1]<<endl;
    }
	return 0;
}
