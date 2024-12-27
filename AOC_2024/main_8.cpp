#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

void PartOne();
void PartTwo();

using namespace std;


int main() {
    // PartOne();
    PartTwo();

}

void PartOne() {
    ifstream file("input8.txt");
    vector<string> grid;
    string line;
    while (getline(file,line )) {
        grid.push_back(line);
    }

    map<char , vector<pair<int ,int>>> mp;
    int row = static_cast<int>(grid.size()) ;
    int col = static_cast<int>(grid[0].size()) ;
    set<pair<int ,int>> st;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] != '.' ) {
                const char c= grid[i][j];
                mp[c].push_back({i ,j});
            }
        }
    }

    for (const auto [ _ , p] : mp) {
        const int vlen = static_cast<int>(p.size());
        if (vlen == 1) continue;
        for (int i =0 ; i < vlen ; i++) {
            for (int j = i + 1; j < vlen ; j++) {
                int diffX = p[i].first - p[j].first;
                int diffY = p[i].second - p[j].second;
                int rightX = p[i].first + diffX , rightY = p[i].second + diffY;
                int leftX = p[j].first - diffX , leftY = p[j].second - diffY;
                if (rightX >= 0 && rightX < row && rightY >= 0 && rightY < col) st.insert({rightX,rightY});
                if (leftX >= 0 &&leftX < row && leftY >= 0 && leftY < col) st.insert({leftX,leftY});
            }
        }
    }


    cout << st.size() << endl;
}

void PartTwo() {
    ifstream file("input8.txt");
    vector<string> grid;
    string line;
    while (getline(file,line )) {
        grid.push_back(line);
    }

    map<char , vector<pair<int ,int>>> mp;
    int row = static_cast<int>(grid.size()) ;
    int col = static_cast<int>(grid[0].size()) ;
    set<pair<int ,int>> st;
    for (int i =0 ; i < row ; i++) {
        for (int j =0 ; j < col ; j++) {
            if (grid[i][j] != '.' ) {
                const char c= grid[i][j];
                mp[c].push_back({i ,j});
            }
        }
    }

     const auto isValid = [row, col](const int i ,const  int j) -> bool {
        return i >= 0 && i < row && j >= 0 && j < col;
    };

    for (const auto [ _ , p] : mp) {
        const int vlen = static_cast<int>(p.size());
        if (vlen == 1) continue;
        for (int i =0 ; i < vlen ; i++) {
            for (int j = i + 1; j < vlen ; j++) {
                st.insert({p[i].first,p[i].second});
                st.insert({p[j].first,p[j].second});
                int diffX = p[i].first - p[j].first;
                int diffY = p[i].second - p[j].second;
                int rightX = p[i].first + diffX , rightY = p[i].second + diffY;
                int leftX = p[j].first - diffX , leftY = p[j].second - diffY;

                while (isValid(rightX , rightY)) {
                    st.insert({rightX,rightY});
                    grid[rightX][rightY] = '#';
                    rightX += diffX , rightY +=  diffY;
                }

                while (isValid(leftX , leftY)) {
                    st.insert({leftX,leftY});
                    grid[leftX][leftY] = '#';
                    leftX -= diffX , leftY -= diffY;
                }
            }
        }
    }
    cout << st.size() << endl;
}

