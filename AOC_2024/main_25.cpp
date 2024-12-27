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
#include <signal.h>
#include <unistd.h>


void PartOne();
void PartTwo();

using namespace std;

int main() {
    PartOne();
    // PartTwo();
}


void PartOne() {
    ifstream file("input25.txt") ;
    string line;
    int i =0 ;

    vector<string> pattern(7);
    vector<array<int , 5>> lock, key;

    auto parse = [&pattern, &lock, &key]() {
        bool isLock = true;
        if (pattern[0][0] == '.') {
            isLock = false;
        }

        cout << '\n' ;
        array<int ,5> it;
        for (int col = 0  ; col < 5 ; col++) {
            int cnt = 0 ;
            for (int row = 1 ;  row <= 5 ; row++) {
                if (pattern[row][col] == '#') {
                    cnt++;
                }
            }
            it[col] = cnt;
        }

        if (isLock) {
            lock.emplace_back(it);
        }else {
            key.emplace_back(it);
        }
    };
    while (getline(file, line)) {
        if (line.empty()) {
            i =0 ;

            parse();
            continue;
        }
        pattern[i] = line;
        i++;
    }
    parse();


    int cnt =0 ;
    for (auto &x : lock) {
        for (auto &y : key) {
            bool good = true ;
            for (int d =0 ;d <5;d++) {
                if (x[d] + y[d] > 5 ) good = false;
            }
            if (good) cnt++;
        }
    }

    cout << cnt << '\n';

    set<array<int, 5>> st;
    for (auto x: lock) {
        st.insert(x);
    }

    cout << st.size() << '\n';
}


void PartTwo() {

}
