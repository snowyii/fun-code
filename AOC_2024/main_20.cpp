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

int SX , SY, EX, EY;
int row , col;
int dx[4] = { - 1, 0 , 1, 0} ;
int dy[4]   {  0 , 1, 0, -1} ;
bool check = false;
vector<vector<int>> vis;

void initVis(int r, int c) {
    vis.resize(row) ;
    for (int i = 0; i < row; i++) {
        vis[i].resize(c) ;
        vis[i].assign(c, -1) ;
    }
}

int bfs(vector<string> &grid) {
    vis[SX][SY] = 0;
    queue<pair<int, int>> q;
    q.push({SX , SY});
    while (!q.empty()) {
        auto [x , y] = q.front();
        q.pop();
        for (int d=0 ;d < 4 ;d++) {
            int nx= x + dx[d];
            int ny= y + dy[d];
            if (nx>=0 && ny>=0 && nx<row && ny<col && vis[nx][ny] == -1 && grid[nx][ny] != '#') {
                vis[nx][ny] = vis[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    return vis[EX][EY];
}


void PartOne() {
    ifstream file("input20.txt");
    string line;
    vector<string> grid;
    while (getline(file , line)) {
        grid.push_back(line);
    }

    row = grid.size(), col = grid[0].size();
    initVis(row, col);
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == 'S') SX =i , SY =j ;
            if (grid[i][j] == 'E') EX =i , EY =j ;
        }
    }

    int full = bfs(grid);
    check = true;
    map<int ,int> mp;
    for (int i =0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            if (grid[i][j] == '#') {
                int air =0 ;
                for (int d = 0 ;d < 4 ; d++) {
                    int nx = i + dx[d] ;
                    int ny = j + dy[d];
                    if (nx>= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] != '#') air++;
                }

                if (air >= 2) {
                    grid[i][j] = '.';
                    int newScore = bfs(grid);
                    mp[full - newScore]++;
                    grid[i][j] = '#';
                }
            }
        }
    }

    int64_t total = 0;

    for (auto [ x , y] : mp) {
        if (x >= 100) total += y;
    }
    cout << total << '\n' ;
}

bool isValid(int x , int y) {
    return x >= 0 && x < row && y >= 0 && y < col;
}

void PartTwo() {
    ifstream file("input20.txt");
    string line;
    vector<string> grid;
    while (getline(file , line)) {
        grid.push_back(line);
    }

    row = grid.size(), col = grid[0].size();

    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == 'S') SX =i , SY =j ;
            if (grid[i][j] == 'E') EX =i , EY =j ;
        }
    }

    initVis(row, col);
    bfs(grid);
    auto forWard = vis;
    initVis(row , col);
    swap(SX, EX);
    swap(SY, EY);
    const int full = bfs(grid);
    cout << full << '\n' ;

    int64_t total =0 ;

    for (int i  =0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            for (int k = max(0 ,i- 20)  ; k <= min(row- 1, i + 20) ; k++) {
                for (int t = max(0, j - 20) ; t <= min(col - 1, j + 20) ; t++) {
                    if (grid[i][j] != '#' && grid[k][t] != '#') {
                        if (abs(k -i) + abs(t-j) <= 20) {
                            int sc = abs(k -i ) + abs(t-j) + forWard[i][j] + vis[k][t];
                            if (full - sc >= 100) total++;
                        }
                    }
                }
            }
        }
    }

    cout << total << '\n';





}