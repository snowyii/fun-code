#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include<algorithm>
#include<numeric>
#include <set>
#include <array>
#include <queue>
#include <unistd.h>


void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input16.txt");
    vector<string> grid;
    string line ;
    while (getline(file , line)) {
        grid.push_back(line);
    }

    int x = 0 , y =0 , endX = 0, endY= 0 ;
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0 ;i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 'S') {
                x = i , y= j ;
            }else if ( grid[i][j] == 'E') {
                endX = i , endY = j ;
            }
        }
    }

    int dx[4] = { - 1, 0 , 1, 0 } ;
    int dy[4] = { 0 , 1, 0 , -1} ;
    vector<vector<int>> best(row , vector<int>(col, INT_MAX));
    using NODE = array<int , 4> ;
    priority_queue<NODE, vector<NODE> , greater<>> pq;
    pq.push({0 , x ,y, 1});
    best[x][y] =0;
    while (!pq.empty() ) {
        auto [sc , X , Y , dir ] = pq.top() ;
        pq.pop();

        for (int d =0 ;d < 4 ;d++) {
            int nx = X +dx[d] ;
            int ny = Y + dy[d] ;

            if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                if (grid[nx][ny] != '#') {
                    int score = sc + 1 + ((dir + 3) %4   == d || (dir + 1) % 4 == d  ? 1000 : 0 ) ;
                    if (score < best[nx][ny]) {
                        best[nx][ny] = score;
                        pq.push({score , nx, ny, d});
                    }
                }
            }
        }
    }

    cout << best[endX][endY] << endl;
}

void PartTwo() {
    ifstream file("input16.txt");
    vector<string> grid;
    string line ;
    while (getline(file , line)) {
        grid.push_back(line);
    }

    int x = 0 , y =0 , endX = 0, endY= 0 ;
    int row = grid.size();
    int col = grid[0].size();
    for (int i = 0 ;i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 'S') {
                x = i , y= j ;
            }else if ( grid[i][j] == 'E') {
                endX = i , endY = j ;
            }
        }
    }

    int dx[4] = { - 1, 0 , 1, 0 } ;
    int dy[4] = { 0 , 1, 0 , -1} ;
    vector best(row , vector(col, vector<int>(4 , INT_MAX)));
    vector prev(row , vector(col, vector<vector<array<int ,3>>>(4)));
    using NODE = array<int , 4> ;
    priority_queue<NODE, vector<NODE> , greater<>> pq;
    pq.push({0 , x ,y, 1});
    best[x][y][1] =0;
    best[x][y][2] = 1000 ;
    best[x][y][3] = 2000;
    best[x][y][0] = 1000;
    for (int i =0 ; i < 4 ; i++) {
        prev[x][y][i] = {{ -1 , -1}};
    }
    while (!pq.empty() ) {
        auto [sc , X , Y , dir ] = pq.top() ;
        pq.pop();

        for (int d =0 ;d < 4 ;d++) {
            int nx = X +dx[d] ;
            int ny = Y + dy[d] ;



            if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                if (grid[nx][ny] != '#') {
                    int score = sc + 1  ;
                    if ((dir + 3) %4   == d || (dir + 1) % 4 == d) score += 1000 ;
                    if ((dir + 2) % 4 == d) score += 2000;
                    if (score < best[nx][ny][d]) {
                        best[nx][ny][d] = score;
                        pq.push({score , nx, ny, d});
                        prev[nx][ny][d] ={{X , Y , dir}} ;
                    }else if (score == best[nx][ny][d]) {
                        prev[nx][ny][d].push_back({X , Y, dir});
                    }
                }
            }
        }
    }

    int lowest = INT_MAX;
    for (int i =0 ; i < 4 ; i++) {
        lowest = min(lowest, best[endX][endY][i]);
    }

    vector<array<int ,3>> cur;
    for (int i =0 ; i < 4 ; i++) {
        if (best[endX][endY][i] == lowest) cur.push_back({endX, endY, i});
    }

    for (int i =0 ; i < cur.size(); i++) {
        auto [x , y, dim] = cur[i];
        grid[x][y] = 'O';
        for (auto [a , b, d ] : prev[x][y][dim]) {
            if (a != -1 && b != -1) cur.push_back({a , b, d});
        }
    }



    cout << lowest << endl;

    int cnt =0 ;
    for (auto x : grid) {
        for (auto y : x ) {
            if (y == 'O') cnt++;
        }
        cout << x << '\n' ;
    }


    cout << cnt << '\n' ;

}
