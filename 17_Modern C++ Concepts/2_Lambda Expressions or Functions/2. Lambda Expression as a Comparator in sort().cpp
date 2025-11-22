//  2. Lambda Expression as a Comparator in the inbuilt sort function.

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct node {
    char first;         //  Both first and second take lower case alphabets as a valid input
    string second;
    int third;
};

int main() {
    int n, t;
    char f;
    string s;
    cin>>n;
	vector<node> vectorOfNodes(n);
	node* arr = new node[n];
	auto print = [](int n, auto a) {for(int i=0; i<n; i++) cout<<a[i].first<<" "<<a[i].second<<" "<<a[i].third<<"\n";};
	for(int i=0; i<n; i++) {
        cin>>f>>s>>t;
        vectorOfNodes[i].first = f;     arr[i].first = f;
        vectorOfNodes[i].second = s;    arr[i].second = s;
        vectorOfNodes[i].third = t;     arr[i].third = t;
	}
	sort(vectorOfNodes.begin(), vectorOfNodes.end(), [](node a, node b) -> bool {   //  When the first variables are same, compare the second variables and if they are same too, compare the third variables
	    if(a.first!=b.first) return a.first > b.first;                              //  Descending order in first variable
	    else if(a.second!=b.second) return a.second > b.second;                     //  Descending order in second variable
        else return a.third > b.third;                                              //  Descending order in third variable
        });
    cout<<"Printing the vector after sorting in descending order:\n";
    print(n, vectorOfNodes);
    sort(arr, arr+n, [](node a, node b) -> bool {
	    if(a.first!=b.first) return a.first < b.first;                              //  Ascending order in first variable
        else if(a.second!=b.second) return a.second < b.second;                     //  Ascending order in second variable
        else return a.third < b.third;                                              //  Ascending order in third variable
        });
    cout<<"Printing the array after sorting in ascending order:\n";
    print(n, arr);
	return 0;
}

/* Sample Input:
Input 1:
5
b eaz 4
x hfw 5
r nch 2
a nca 3
i qpl 1

Input 2:
5
a hab 4
a hfw 5
a nch 2
a nca 3
a qpl 1

Input 3:
5
a aaa 4
a aaa 5
a aaa 2
a aaa 3
a aaa 1

*/
