#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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

void PartTwo() {
    ifstream file("input10.txt");
    string line;
    vector<string> grid;
    while(getline(file, line)) {
        grid.push_back(line);
    }
    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());
    int dx[4] = {-1, 0 ,1 ,0 } ;
    int dy[4] = {0 , 1 , 0 , -1};
    vector<vector<int64_t>> score(row , vector<int64_t>(col, 0));
    for (int i = 9 ; i >= 1; i--) {
        for (int j =0 ; j < row ; j++) {
            for (int k =0 ; k < col ; k++) {
                if (grid[j][k] != '0' + i) continue;
                if (i == 9 ) {
                    score[j][k] = 1;
                }
                for (int d =0 ;d < 4 ;d++) {
                    int nx = j + dx[d];
                    int ny = k + dy[d];
                    if (nx >= 0 && nx < row && ny >= 0 && ny < col && (grid[nx][ny] - '0')  == i-1) {
                        score[nx][ny] += score[j][k];
                    }
                }
            }
        }

        cout << "ite" << i << '\n' ;
        for (auto x : score) {
            for (auto y : x) {
                cout << y ;
            }
            cout << '\n' ;
        }
    }
    int64_t sum = 0;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == '0') sum += score[i][j];
        }
    }
    cout << sum << '\n' ;
}


void PartOne() {
    fstream file("input10.txt");
    string line;
    vector<string> grid;
    while(getline(file, line)) {
        grid.push_back(line);
    }
    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());
    int dx[4] = {-1, 0 ,1 ,0 } ;
    int dy[4] = {0 , 1 , 0 , -1};

    bool visited[row][col] ;
    int cnt =0 ;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            int num = grid[i][j] - '0';
            if (num == 0) {
                memset(visited , 0 , sizeof(visited));
                queue<pair<int,int>> q;
                q.emplace(i ,j);
                while (!q.empty()) {
                    auto [x ,y ] = q.front();
                    cout << "X" << x << "Y" << y << '\n' ;
                    q.pop();
                    for (int d =0 ;d < 4 ;d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 &&  nx < row && ny >= 0 && ny < col && grid[nx][ny] - '0' == grid[x][y] - '0' + 1) {
                            if (visited[nx][ny]) {
                                continue ;
                            }
                            visited[nx][ny] = true;
                            if (grid[nx][ny] == '9') {
                                cnt++;
                            }else {
                                q.emplace(nx,ny);
                            }
                        }
                    }
                }
            }
        }
    }
    cout << cnt << '\n';
}



