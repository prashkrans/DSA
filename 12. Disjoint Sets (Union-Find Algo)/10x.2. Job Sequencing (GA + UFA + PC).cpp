/* Greedy Algo Problem 10x.2. Job Sequencing (Greedy Algo + Jobs sorted in desc. order of profit + Union-Find Algo)
Given an array of jobs where every job has a deadline and associated profit, if the job is finished before the
deadline. It is also given that every job takes a single unit of time, so the minimum possible deadline for any
job is 1. How to maximize total profit if only one job can be scheduled at a time.

Example 1:
n = 5
a b c d e
2 2 1 2 3
1 3 1 4 2
Ans = 9

This problem could be solved using three methods;
1.  Greedy Algo Naive:  Running time = O(2^n) (exponential thus, inefficient) as total no. of subsets of an array of size == n is 2^n
    Steps:  a.  Generate all the subsets of a given set of jobs.
            b.  Check individual subsets for the feasibility of jobs in that subset.
            c.  Keep track of maximum profit among all feasible subsets.

2.  Greedy Algo Optimized with Sorting:
    Running time = O(sorting + find greatest available time slot for each element) = O(nlog2(n) + O(n*m)) ~ O(n*m) i.e. quadratic thus, inefficient.
    where m = the max number of time slots = maxDeadline
    Steps:  a.  Sort all jobs in decreasing order of profit.
            b.  Iterate on jobs in decreasing order of profit. For each job , do the following :
                i.  For each job find the greatest empty time slot from its deadline to 0. R.T. = O(m)
                ii. If found empty slot put the job in the slot and mark this slot filled.
    Note: timeSlot[i] represents the time slot (i, i+1). So, if a job has deadline d then it could be alloted any one time slot
    from (0, 1) i.e. timeSlot[0] to (d-1, d) i.e. timeSlot[d-1] thus, i iterates from d-1 to 0.

3.  Greedy Algo Optimized with Sorting as well as Union-Find Algo:
    Note: Only path compression is used instead of Union by rank/height + path compression as we only merge a set with slot t with a set with slot t-1
    Running time = O(sorting + find greatest available time slot for each element) = O(nlog2(n) + n*1) ~ O(nlog2(n)) thus efficient.
    Steps: Exactly same as that of method 2 except that now Union-Find algo reduces the time to find the greatest available time slot for each element to
    O(1) instead of O(m).
    Note: In vector timeSlotSubset; ith posn represents the time slot (i, i+1). So, size of timeSlotSubset = maxDeadline thereby giving the maxDeadline no. of time slots
    i   time slot   deadline
    0   (0, 1)      1
    1   (1, 2)      2
    ...
    m-1 (m-1, m)    m
*/

//  Method 3. Greedy Algo Optimized
//  Running time = O(nlog2(n) + n*1) ~ O(nlog2(n))
//  Auxiliary space = O(m) to store the timeSlots i.e. 0 to m-1 where m = maxDeadlineTime

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct node {
	char jobID;
	int deadline, profit;
};

class cmp1 {
public:                     //  make sure to make the operator() public
	bool operator()(node x, node y) const {
		return x.profit > y.profit;
	}
};

bool cmp2(node x, node y) {
    return x.profit > y.profit;
}

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

int jobSequencing(int n, vector<char> job, vector<int> d, vector<int> p) {
	vector<node> jobNodes(n);
	int maxDeadline = 0;
	for(int i=0; i<n; i++) {
		jobNodes[i].jobID = job[i];
		jobNodes[i].deadline = d[i];
		jobNodes[i].profit = p[i];
		maxDeadline = max(maxDeadline, d[i]);
	}
	//cout<<"Sorting the jobs in descending order of profit\n"; //  Three methods to use a comparator in sort() function
    //sort(jobNodes.begin(), jobNodes.end(), cmp1());           //  1.  Comparator as a class
    //sort(jobNodes.begin(), jobNodes.end(), cmp2);             //  2.  Comparator as a function
	sort(jobNodes.begin(), jobNodes.end(), [](node a, node b) -> bool {return a.profit > b.profit;}); //  3.  Comparator as a lambda expression
	//for(auto i : jobNodes) cout<<i.jobID<<" "<<i.deadline<<" "<<i.profit<<"\n";
	//cout<<"Max Deadline = "<<maxDeadline<<"\n";
	//cout<<"So, [#IMP]atmost "<<maxDeadline<<" number of jobs can be completed as each job takes 1 unit of time to complete\n";
	vector<int> timeSlotSubset(maxDeadline);                    //  timeSlots[i] = -1 (vacant) or profit of the job that occupies the ith time slot (occupied)
	for(int i=0; i<maxDeadline; i++) timeSlotSubset[i] = i;
	vector<pair<char, int>> jobsCompleted;                      //  ith time slot means the time slot (i, i+1);
	int maxProfitSum = 0;
	int count = 0;                                              //  Number of jobs completed to give max profit
    for(int i=0; i<n; i++) {                                    //  Greedy algo
		int deadlineSlot = jobNodes[i].deadline-1;
		int t = findSet(deadlineSlot, timeSlotSubset);          //  t is the maximum available slot for a job
        if(t!=-1 && t<=deadlineSlot) {						    //  Checks the feasibility of a job and assigns it a time slot
			unionOfSets(t-1, t, timeSlotSubset);
			maxProfitSum += jobNodes[i].profit;
            jobsCompleted.push_back({jobNodes[i].jobID, jobNodes[i].profit});
            count++;
        }
    }
    //for(int i=0; i<maxDeadline; i++) cout<<i<<"\t"; cout<<"\n";
    //for(int i=0; i<maxDeadline; i++) cout<<timeSlotSubset[i]<<"\t";  cout<<"\n";
    cout<<"The order of completion of jobs:\n";
    for(int i=0; i<count; i++) cout<<jobsCompleted[i].first<<" "; cout<<"\n";
    cout<<"The max profit is = ";
	return maxProfitSum;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n;
        cin>>n;
        vector<char> job(n);
        vector<int> deadline(n), profit(n);
        for(int i=0; i<n; i++) cin>>job[i];
        for(int i=0; i<n; i++) cin>>deadline[i];
        for(int i=0; i<n; i++) cin>>profit[i];
        cout<<jobSequencing(n, job, deadline, profit)<<"\n";
    }
	return 0;
}

/* Sample input:
4
5
a b c d e
2 2 1 2 3
1 3 1 4 2
5
a b c d e
2 2 3 2 1
1 3 1 4 2
5
a b c d e
2 2 1 2 1
1 3 1 4 2
4
a b c d
4 1 1 1
20 10 40 30
*/
