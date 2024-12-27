#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>

void PartOne();
void PartTwo();

using namespace std;


int main() {
    // PartOne();
    PartTwo();
}

/*
 X
 XM
 XMA
 XMAS

S
 SA
 SAM
 SAMX
 */
void PartTwo(){
    ifstream file("input4.txt");
    string s;
    vector<string> grid ;
    while (getline(file , s)) {
        grid.push_back(s);
    }

    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());

    int64_t total =0 ;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] == 'A') {
                if (i -1 >= 0 && j - 1 >= 0 && j + 1 < col && i + 1 < row ) {
                    string wordL = string(1, grid[i-1][j-1]) + grid[i+1][j+1];
                    string wordR = string(1 , grid[i-1][j+1]) + grid[i+1][j-1];
                    if ((wordL == "MS" || wordL == "SM") &&
                        (wordR == "MS" || wordR == "SM")
                        ) {
                        total++;
                    }
                }
            }
        }
    }
    cout << total << endl;
}

void PartOne() {
    ifstream file("input4.txt");
    string s;
    vector<string> grid ;
    while (getline(file , s)) {
        grid.push_back(s);
    }

    int row = static_cast<int>(grid.size());
    int col = static_cast<int>(grid[0].size());

    int64_t total =0 ;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j + 3 < col ; j++) {
            if (grid[i][j] == 'X' && grid[i][j+1] == 'M' && grid[i][j+2] == 'A' && grid[i][j+3] == 'S') {
                total += 1;
            }
            if (grid[i][j] == 'S' && grid[i][j+1] == 'A' && grid[i][j+2] == 'M' && grid[i][j+3] == 'X') {
                total += 1;
            }
        }
    }

    for (int j =0 ; j < row ; j++) {
        for (int i =0 ; i + 3 < col ; i++) {
            if (grid[i][j] == 'X' && grid[i+1][j] == 'M' && grid[i+2][j] == 'A' && grid[i+3][j] == 'S') {
                total += 1;
            }
            if (grid[i][j] == 'S' && grid[i+1][j] == 'A' && grid[i+2][j] == 'M' && grid[i+3][j] == 'X') {
                total += 1;
            }
        }
    }

    for (int i =0 ; i +3  < row ; i++) {
        for (int j =0 ; j + 3 < col ; j++) {
            if (grid[i][j] == 'X' && grid[i+1][j+1] == 'M' && grid[i+2][j+2] == 'A' && grid[i+3][j+3] == 'S') {
                total += 1;
            }
            if (grid[i][j] == 'S' && grid[i+1][j+1] == 'A' && grid[i+2][j+2] == 'M' && grid[i+3][j+3] == 'X') {
                total += 1;
            }
        }
    }

    for (int i = row -1  ; i - 3  >= 0  ; i--) {
        for (int j =0 ; j + 3 < col ; j++) {
            if (grid[i][j] == 'X' && grid[i-1][j+1] == 'M' && grid[i-2][j+2] == 'A' && grid[i-3][j+3] == 'S') {
                total += 1;
            }
            if (grid[i][j] == 'S' && grid[i-1][j+1] == 'A' && grid[i-2][j+2] == 'M' && grid[i-3][j+3] == 'X') {
                total += 1;
            }
        }
    }
    cout << total << '\n' ;
}