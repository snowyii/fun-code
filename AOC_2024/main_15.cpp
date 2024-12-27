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
    ifstream file("input15.txt");
    string line;
    vector<string> grid;
    vector<string> command;
    bool isEmpty = false;
    while (getline(file, line)) {
        if (line.empty()) {
            isEmpty = true;
            continue;
        }
        if (!isEmpty) {
            grid.push_back(line);
        }else {
            command.push_back(line);
        }
    }

    int X =0 , Y = 0 ;
    const int row = grid.size(), col = grid[0].size();
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == '@') {
                X = i , Y = j;
            }
        }
    }

    for (auto &c : command) {
        for (auto &s : c) {
            if (s == '<') {
                int ny = Y - 1;
                while (grid[X][ny] != '#' && grid[X][ny] != '.' ) {
                    ny--;
                }

                if (grid[X][ny] == '.') {
                    for (int k= ny + 1; k <= Y ; k++) {
                        swap(grid[X][k-1] , grid[X][k]);
                    }
                    Y--;
                }
            }else if (s == '>') {
                int ny = Y + 1;
                while (grid[X][ny] != '#' && grid[X][ny] != '.' ) {
                    ny++;
                }

                if (grid[X][ny] == '.') {
                    for (int k= ny - 1; k >= Y ; k--) {
                        swap(grid[X][k+1] , grid[X][k]);
                    }
                    Y++;
                }
            }else if (s == 'v') {
                int nx = X + 1;
                while (grid[nx][Y] != '#' && grid[nx][Y] != '.' ) {
                    nx++;
                }

                if (grid[nx][Y] == '.') {
                    for (int k= nx - 1; k >= X ; k--) {
                        swap(grid[k][Y] , grid[k+1][Y]);
                    }
                    X++;
                }
            }else if (s == '^') {
                int nx = X - 1;
                while (grid[nx][Y] != '#' && grid[nx][Y] != '.' ) {
                    nx--;
                }

                if (grid[nx][Y] == '.') {
                    for (int k= nx + 1; k <= X ; k++) {
                        swap(grid[k][Y] , grid[k-1][Y]);
                    }
                    X--;
                }
            }

        }
    }
    int64_t total =0 ;
   for (int i =0 ; i < row ; i++) {
       for (int j =0 ; j < col ; j++) {
           if (grid[i][j] == 'O') {
               total += 100 * i + j ;
           }
       }
   }

    cout << total << '\n';
}

void PartTwo() {
    ifstream file("input15.txt");
    string line;
    vector<string> grid;
    vector<string> command;
    bool isEmpty = false;
    while (getline(file, line)) {
        if (line.empty()) {
            isEmpty = true;
            continue;
        }
        if (!isEmpty) {
            string newLine;
            for (char c : line) {
                if (c == '#') {
                    newLine += '#';
                    newLine += '#';
                }else if ( c =='O') {
                    newLine += "[]";
                }else if ( c == '.') {
                    newLine += "..";
                }else if (c == '@'){
                    newLine += "@.";
                }
            }

            grid.push_back(newLine);
        }else {
            command.push_back(line);
        }
    }

    int X =0 , Y = 0 ;
    const int row = grid.size(), col = grid[0].size();
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == '@') {
                X = i , Y = j;
            }
        }
    }

    for (auto &c : command) {
        for (auto &s : c) {
            vector<pair<int,int>> pos;
            if (s == '<') {
                pos.emplace_back(X, Y);
                bool canMove = true ;
                for (int i =0 ; i < pos.size() ; i++) {
                    auto [curX , curY] = pos[i];
                    int ny = curY - 1;
                    bool skip = false;
                    if (grid[curX][ny] != '#' && grid[curX][ny] != '.' ) {
                        pos.emplace_back(curX, ny);
                        skip = true ;
                    }

                    if (!skip && grid[curX][ny] == '#') {
                        canMove = false;
                    }
                }


                if (canMove) {
                    for (int i = pos.size() ; i >= 0 ; i--) {
                        auto [ x, y] = pos[i];
                        swap(grid[x][y] , grid[x][y-1]) ;
                    }
                    Y--;
                }

            }else if (s == '>') {
                pos.emplace_back(X, Y);
                bool canMove = true ;
                for (int i =0 ; i < pos.size() ; i++) {
                    auto [curX , curY] = pos[i];
                    int ny = curY + 1;
                    bool skip = false;
                    if (grid[curX][ny] != '#' && grid[curX][ny] != '.' ) {
                        pos.emplace_back(curX, ny);
                        skip = true ;
                    }


                    if (!skip && grid[curX][ny] == '#') {
                        canMove = false;
                    }
                }
                if (canMove) {
                    for (int i = pos.size() ; i >= 0 ; i--) {
                        auto [ x, y] = pos[i];
                        swap(grid[x][y] , grid[x][y+1]) ;
                    }
                    Y++;
                }
            }else if (s == 'v') {
                pos.emplace_back(X, Y);
                bool canMove = true ;
                set<pair<int,int>> st;
                for (int i =0 ; i < pos.size() ; i++) {
                    auto [curX , curY] = pos[i];
                    int nx = curX + 1;
                    bool skip = false;
                    if (grid[nx][curY] != '#' && grid[nx][curY] != '.' ) {
                        if (grid[nx][curY] == '[') {
                            pair<int, int> left = {nx , curY} ;
                            pair<int ,int> right = {nx , curY+1} ;
                            if (!st.contains(left)) {
                                st.insert(left);
                                pos.push_back(left);
                            }
                            if (!st.contains(right)) {
                                st.insert(right);
                                pos.push_back(right);
                            }
                        }else if (grid[nx][curY] == ']') {
                            pair<int, int> left = {nx , curY-1} ;
                            pair<int ,int> right = {nx , curY} ;
                            if (!st.contains(left)) {
                                st.insert(left);
                                pos.push_back(left);
                            }
                            if (!st.contains(right)) {
                                st.insert(right);
                                pos.push_back(right);
                            }
                        }
                        skip = true ;
                    }

                    if (!skip && grid[nx][curY] == '#') {
                        canMove = false;
                    }
                }

                if (canMove) {
                    for (int i = pos.size() ; i >= 0 ; i--) {
                        auto [ x, y] = pos[i];
                        swap(grid[x][y] , grid[x+1][y]) ;
                    }
                    X++;
                }
            }else if (s == '^') {
                pos.emplace_back(X, Y);
                bool canMove = true ;
                set<pair<int,int>> st;
                for (int i =0 ; i < pos.size() ; i++) {
                    auto [curX , curY] = pos[i];
                    int nx = curX - 1;
                    bool skip = false;
                    if (grid[nx][curY] != '#' && grid[nx][curY] != '.' ) {
                        if (grid[nx][curY] == '[') {
                            pair<int, int> left = {nx , curY} ;
                            pair<int ,int> right = {nx , curY+1} ;
                            if (!st.contains(left)) {
                                st.insert(left);
                                pos.push_back(left);
                            }
                            if (!st.contains(right)) {
                                st.insert(right);
                                pos.push_back(right);
                            }
                        }else if (grid[nx][curY] == ']') {
                            pair<int, int> left = {nx , curY-1} ;
                            pair<int ,int> right = {nx , curY} ;
                            if (!st.contains(left)) {
                                st.insert(left);
                                pos.push_back(left);
                            }
                            if (!st.contains(right)) {
                                st.insert(right);
                                pos.push_back(right);
                            }
                        }
                        skip = true ;
                    }

                    if (!skip && grid[nx][curY] == '#') {
                        canMove = false;
                    }
                }

                if (canMove) {
                    for (int i = pos.size() ; i >= 0 ; i--) {
                        auto [ x, y] = pos[i];
                        swap(grid[x][y] , grid[x-1][y]) ;
                    }
                    X--;
                }
            }
        }
    }


    for (auto x : grid) {
        for (auto y : x) {
            cout << y ;
        }
        cout << '\n' ;
    }

    int64_t total =0 ;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == '[') total += 100 * i + j ;
        }
    }

    cout << total << '\n' ;
}