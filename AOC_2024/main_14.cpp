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
    PartOne();
    // PartTwo();
}

void PartOne() {
    ifstream file("input14.txt");
    vector<pair<int,int>> v;
    vector<pair<int,int>> move;
    string line;
    int turn =7687;
    while (getline(file, line)) {
        line = line.substr(2);
        stringstream ss(line);
        string coord, dir;
        ss >> coord >> dir;
        coord.find(',');
        int pos = coord.find(',');
        int x= stoi(coord.substr(0,pos));
        int y = stoi(coord.substr(pos + 1));
        v.emplace_back(x,y);

        dir = dir.substr(2);
        pos = dir.find(',');
        x = stoi(dir.substr(0,pos));
        y = stoi(dir.substr(pos + 1));
        move.emplace_back(x *turn,y * turn );
    }

    const int row = 101, col = 103;
    vector<vector<char>> grid(col , vector<char>(row,'='));
    vector<int> qd(4);
    for (int i =0 ; i < static_cast<int>(v.size()); i++) {
        auto [ x, y ] = v[i];
        int change = move[i].first;
        if (change < 0 ) {
            change*= -1;
            if (change > x ) {
                change -= x;
                x = 0;
                int rest = change %(row);
                if (rest > 0 ) {
                    x = row - rest ;
                }
            }else {
                x -= change ;
            }
        }else {
            if (change > row - 1 - x) {
                change -= (row - 1- x) ;
                x = row - 1;
                int rest = change %( row );
                if (rest > 0 ) {
                    x = -1 + rest ;
                }
            } else {
                x += change;
            }
        }

        change = move[i].second;
        if (change < 0 ) {
            change *= -1;
            if (change > y) {
                change -= y;
                y= 0 ;
                int rest = change % (col);
                if (rest > 0 ) {
                    y = col - rest ;
                }
            } else {
                y -= change;
            }
        }else {
            if (change > col - 1 - y) {
                change -= (col - 1 - y) ;
                y = col - 1;
                int rest = change % (col);
                if (rest > 0 ) {
                    y = -1 + rest;
                }

            }else {
                y += change;
            }
        }

        if ( x < row /2 &&  y < col /2) {
            qd[0]++;
        }else if (x > row /2 && y < col /2) {
            qd[1]++;
        }else if (x < row/ 2&& y > col / 2) {
            qd[2]++;
        }else if (x > row / 2  && y > col / 2) {
            qd[3]++;
        }

        grid[y][x] = 'X';
    }

    for (auto x : grid) {
        for (auto y : x) {
            cout << y ;
        }
        cout << endl;
    }

    cout << static_cast<long long>(qd[0]) * qd[1] * qd[2] * qd[3] << endl;
}

//7687
/*
================================XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX======================================
====================X===========X=============================X======================================
================================X=============================X===================================XX=
================================X=============================X============================X=========
================================X=============================X======================================
================X===X===========X==============X==============X=====================X================
================================X=============XXX=============X======================================
==========================X=====X============XXXXX============X======X===============================
===========================X====X===========XXXXXXX===========X====X=================================
==========X=====================X==========XXXXXXXXX==========X==================X=====X=============
================================X============XXXXX============X======================================
================================X===========XXXXXXX===========X=======X=====X========================
================================X==========XXXXXXXXX==========X======================================
================================X=========XXXXXXXXXXX=========X=====================X================
=========X=============X========X========XXXXXXXXXXXXX========X======================================
==========================X=====X==========XXXXXXXXX==========X======================================
==========X=====================X=========XXXXXXXXXXX=========X======================================
X===============================X========XXXXXXXXXXXXX========X======================================
=========================X======X=======XXXXXXXXXXXXXXX=======X=========X============================
================================X======XXXXXXXXXXXXXXXXX======X============X=========================
================================X========XXXXXXXXXXXXX========X=====================================X
=============================X==X=======XXXXXXXXXXXXXXX=======X========================X=============
============X===================X======XXXXXXXXXXXXXXXXX======X======================================
=======X========================X=====XXXXXXXXXXXXXXXXXXX=====X======================================
=================X==============X====XXXXXXXXXXXXXXXXXXXXX====X======================================
================================X=============XXX=============X======================================
================================X=============XXX=============X=====================X================
X===============================X=============XXX=============X===============X======================
===========================XX===X=============================X==============================X=======
================================X=============================X======================================
================================X=============================X======================================
================================X=============================X==========X===========================
================================XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX======================================
*/

void PartTwo() {
    ifstream file("input14.txt");
    vector<pair<int,int>> v;
    vector<pair<int,int>> move;
    string line;
    while (getline(file, line)) {
        line = line.substr(2);
        stringstream ss(line);
        string coord, dir;
        ss >> coord >> dir;
        coord.find(',');
        int pos = coord.find(',');
        int x= stoi(coord.substr(0,pos));
        int y = stoi(coord.substr(pos + 1));
        v.emplace_back(x,y);

        dir = dir.substr(2);
        pos = dir.find(',');
        x = stoi(dir.substr(0,pos));
        y = stoi(dir.substr(pos + 1));
        move.emplace_back(x,y );
    }

     const int row = 101, col = 103;

    int turn = 0;
    while (turn <= 142926 ) {
        turn++;
        // usleep(100000);
        vector<vector<char>> grid(col  , vector<char>(row ,' '));
        vector<int> qd(4);
        for (int i =0 ; i < static_cast<int>(v.size()); i++) {
            auto [ x, y ] = v[i];
            int changeX = move[i].first * turn ;
            int changeY = move[i].second * turn ;
            int change = changeX;
            if (change < 0 ) {
                change*= -1;
                if (change > x ) {
                    change -= x;
                    x = 0;
                    int rest = change %(row);
                    if (rest > 0 ) {
                        x = row - rest ;
                    }
                }else {
                    x -= change ;
                }
            }else {
                if (change > row - 1 - x) {
                    change -= (row - 1- x) ;
                    x = row - 1;
                    int rest = change %( row );
                    if (rest > 0 ) {
                        x = -1 + rest ;
                    }
                } else {
                    x += change;
                }
            }

            change = changeY;
            if (change < 0 ) {
                change *= -1;
                if (change > y) {
                    change -= y;
                    y= 0 ;
                    int rest = change % (col);
                    if (rest > 0 ) {
                        y = col - rest ;
                    }
                } else {
                    y -= change;
                }
            }else {
                if (change > col - 1 - y) {
                    change -= (col - 1 - y) ;
                    y = col - 1;
                    int rest = change % (col);
                    if (rest > 0 ) {
                        y = -1 + rest;
                    }

                }else {
                    y += change;
                }
            }

            if ( x < row /2 &&  y < col /2) {
                qd[0]++;
            }else if (x > row /2 && y < col /2) {
                qd[1]++;
            }else if (x < row/ 2&& y > col / 2) {
                qd[2]++;
            }else if (x > row / 2  && y > col / 2) {
                qd[3]++;
            }

            int t = grid.size();
            int k = grid[0].size() ;
            assert(y >= 0 && y < t && x >= 0 && x < k);
            grid[y][x] = '#';
        }

        for (auto x : grid) {
            for (auto y : x) {
                cout << y ;
            }
            cout << endl;
        }

        cout << "TURN " << turn << " => "  << static_cast<long long>(qd[0]) * qd[1] * qd[2] * qd[3] << endl;
        cout << '\n' ;
    }
}