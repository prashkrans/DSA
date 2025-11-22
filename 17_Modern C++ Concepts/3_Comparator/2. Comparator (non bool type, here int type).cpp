/* Comparator Prob. #2 - Sorting: Comparator (Non-bool type and using a class)
https://www.hackerrank.com/challenges/ctci-comparator-sorting/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D%5B%5D=sorting
*/

#include<cmath>
#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

struct Player {
    int score;
    string name;
};

class Checker{
public:
  	// complete this method
    static int comparator(Player a, Player b)  {                //  Non bool type comparator class
            if(a.score==b.score && a.name < b.name) return 1;
            else if(a.score > b.score) return 1;
            else return -1;
    }
};

bool compare(Player a, Player b) {                              //  This just maps -1 to false and 1 to true
    if(Checker::comparator(a,b) == -1)                          //  :: is the scope resolution operator that uses
        return false;                                           //  the public method of checker without creating an object
    return true;
}
int main()
{
    int n;
    cin >> n;
    vector< Player > players;
    string name;
    int score;
    for(int i = 0; i < n; i++){
        cin >> name >> score;
        Player player;
        player.name = name, player.score = score;
        players.push_back(player);
    }
    sort(players.begin(), players.end(), compare);		//	sort() uses compare which then uses Checker::comparator() == -1 or not to compare.
    for(int i = 0; i < players.size(); i++) {
        cout << players[i].name << " " << players[i].score << endl;
    }
    return 0;
}
