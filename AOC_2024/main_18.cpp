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
    ifstream file("input18.txt");
    string line;
    vector<pair<int, int>> rock ;

    while (getline(file , line)) {
        int X = stoi(line.substr(0 , line.find(',')));
        int Y = stoi(line.substr(line.find(',') + 1));
        rock.emplace_back(X, Y);
    }

    const int row = 71 , col = 71;
    vector grid(row, vector<char>(col, '.'));

    int i =0 ;
    for (auto x : rock ) {
        if (i == 1024) break ;
        auto [a , b] = x;
        grid[b][a] = '#';
        i++;
    }

    vector vis(row , vector<int>(col , -1));
    vis[0][0] = 0;
    queue<pair<int, int>> q;
    q.push({0, 0});

    int dx[4] = { - 1, 0 , 1, 0 };
    int dy[4] = { 0 , 1, 0 , -1};
    while (!q.empty()) {
        auto [x , y ] = q.front();
        q.pop();

        for (int d =0 ;d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] != '#' && vis[nx][ny] == -1) {
                vis[nx][ny] = vis[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }


    cout << vis[row-1][col-1] << '\n' ;

}

void PartTwo() {
    ifstream file("input18.txt");
    string line;
    vector<pair<int, int>> rock ;

    while (getline(file , line)) {
        int X = stoi(line.substr(0 , line.find(',')));
        int Y = stoi(line.substr(line.find(',') + 1));
        rock.emplace_back(X, Y);
    }

    const int row = 71 , col = 71;
    for (int s =0 ; s < rock.size(); s++) {
        vector grid(row, vector<char>(col, '.'));

        int i =0 ;
        for (auto x : rock ) {
            if (i == s + 1) break ;
            auto [a , b] = x;
            grid[b][a] = '#';
            i++;
        }

        vector vis(row , vector<int>(col , -1));
        vis[0][0] = 0;
        queue<pair<int, int>> q;
        q.push({0, 0});

        int dx[4] = { - 1, 0 , 1, 0 };
        int dy[4] = { 0 , 1, 0 , -1};
        while (!q.empty()) {
            auto [x , y ] = q.front();
            q.pop();

            for (int d =0 ;d < 4; d++) {
                int nx = x + dx[d];
                int ny = y + dy[d];
                if (nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] != '#' && vis[nx][ny] == -1) {
                    vis[nx][ny] = vis[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }


        if (vis[row-1][col-1] == -1) {
            cout << rock[s].first << "," << rock[s].second << '\n' ;
            return ;
        }
    }
}