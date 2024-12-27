#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include<algorithm>
#include <set>
#include <array>
#include <queue>


void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}
int dx[4] = {- 1, 0 , 1, 0} ;
int dy[4] = {0, 1, 0, -1 };

void PartOne() {
    ifstream file("input12.txt");
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.emplace_back(line);
    }

    map<int,int> mp;
    map<int, int> per;
    int row = grid.size();
    int col = grid[0].size();


    int grp = 0 ;
    vector<vector<bool>> vis(row , vector<bool>(col, false));
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (vis[i][j] == false) {
                grp++;
                queue<pair<int ,int>> q;
                q.push(make_pair(i,j));
                vis[i][j] = true;
                while (q.size() > 0 ) {
                    auto [x ,y ] = q.front();
                    mp[grp]++;
                    q.pop();
                    int score = 4;
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 && nx < row && ny >= 0 && ny < col) {
                            if (grid[nx][ny] == grid[x][y]) {
                                score--;
                                if (!vis[nx][ny] ) q.push({nx,ny});
                                vis[nx][ny] = true;
                            }
                        }
                    }
                    per[grp] += score;
                }
            }
        }
    }

    long long total = 0 ;
    for (auto [a ,b ] : mp) {
        cout <<  a << " " << b << ' '  << per[a] << '\n' ;
        total += static_cast<long long>(b) * per[a];
    }
    cout << total << '\n' ;
}

void PartTwo() {
    ifstream file("input12.txt");
    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.emplace_back(line);
    }

    map<int,int> mp;
    map<int, int> per;
    int row = grid.size();
    int col = grid[0].size();

    int grp = 0 ;
    vector<vector<bool>> vis(row , vector<bool>(col, false));
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (vis[i][j] == false) {
                map<pair<int, int> , vector<int>> LINE;
                grp++;
                queue<pair<int ,int>> q;
                q.push(make_pair(i,j));
                vis[i][j] = true;
                while (q.size() > 0 ) {
                    auto [x ,y ] = q.front();
                    mp[grp]++;
                    q.pop();
                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        bool good = nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == grid[x][y];
                        if (d == 0 || d == 2) {
                            if (!good) {
                                //out of bound or not match, should have fence
                                if (d == 0) LINE[{1, x-1 }].emplace_back(y);
                                else LINE[{2, x + 1 }].emplace_back(y);
                            }
                        }else {
                            if (!good) {
                                if (d == 1) LINE[{ 3 , y + 1 }].emplace_back(x);
                               else  LINE[{ 4 , y - 1}].emplace_back(x);
                            }
                        }
                        if (good) {
                            if (!vis[nx][ny] ) q.push({nx,ny});
                            vis[nx][ny] = true;
                        }
                    }
                }

                int CNT =0 ;
                for (auto &[ k , v ] : LINE) {
                    sort(v.begin(), v.end());
                    cout << k.first << " " << k.second << '\n';
                    for (auto x : v) {
                        cout <<  "==>" << x ;
                    }
                    cout << '\n' ;
                    int cnt = 1;
                    for (int t =1 ;t < v.size() ; t++ ) {
                        if (v[t] != v[t-1] + 1) {
                            cnt++;
                        }
                    }
                    CNT += cnt;
                }
                per[grp] = CNT;
            }
        }
    }
    long long total = 0 ;
    for (auto [a ,b ] : mp) {
        cout <<  a << " " << b << ' '  << per[a] << '\n' ;
        total += static_cast<long long>(b) * per[a];
    }

    cout << total << '\n' ;
}