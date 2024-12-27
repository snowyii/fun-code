#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <math.h>

void PartOne();
void PartTwo();

using namespace std;


int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input6.txt");
    vector<string> grid ;
    string s;
    while (getline(file, s )) {
        grid.push_back(s);
    }

    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());
    int x=0,y=0;
    for (int i = 0 ;i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '^' ) {
                x = i ,y = j ;
            }
        }
    }

    int cnt = 1 ;
    char cur = '^';
    map<char , pair<int,int>> mp = {
        {'^' , pair<int,int>{-1, 0}},
        {'>' , pair<int,int>{0, 1}},
        {'v' , pair<int,int>{1, 0}},
        {'<' , pair<int,int>{0, -1}},
    };

    map<char, char> nxt = {
        {'^' , '>'},
        {'>' , 'v'},
        {'v' , '<'},
        {'<' , '^'},
    };
    while (x >= 0 && y >= 0 && x < row && y < col) {
        const auto [ dx , dy] = mp[cur] ;
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && ny >= 0 && nx < row && ny < col) {
            if (grid[nx][ny] == '#') {
                cur = nxt[cur];
            }else {
                if (grid[nx][ny] == '.' ) cnt++;
                grid[nx][ny] = '%';
                x = nx, y = ny;
            }
        }else {
            x = nx, y = ny;
        }
    }
    cout << cnt << '\n';
}

void PartTwo() {
    ifstream file("input6.txt");
    vector<string> grid ;
    string s;
    while (getline(file, s )) {
        grid.push_back(s);
    }

    vector<string> save = grid ;
    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());
    int X=0,Y=0;
    for (int i = 0 ;i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '^' ) {
                X = i ,Y = j ;
            }
        }
    }

    int cnt =0 ;
    map<char , pair<int,int>> mp = {
        {'^' , pair<int,int>{-1, 0}},
        {'>' , pair<int,int>{0, 1}},
        {'v' , pair<int,int>{1, 0}},
        {'<' , pair<int,int>{0, -1}},
    };

    map<char, char> nxt = {
        {'^' , '>'},
        {'>' , 'v'},
        {'v' , '<'},
        {'<' , '^'},
    };

    for (int i =  0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = '#';
                int x = X, y = Y;
                char cur = '^';

                while (x >= 0 && y >= 0 && x < row && y < col) {
                    const auto [ dx , dy] = mp[cur] ;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && ny >= 0 && nx < row && ny < col) {
                        if (grid[nx][ny] == '#') {
                            cur = nxt[cur];
                        }else if (grid[nx][ny] ==  cur) {
                            cnt++;
                            break ;
                        }else{
                            grid[nx][ny] = cur;
                            x = nx, y = ny;
                        }
                    }else {
                        x = nx, y = ny;
                    }
                }
                grid = save;
            }
        }
    }

    cout << cnt << '\n';
}
