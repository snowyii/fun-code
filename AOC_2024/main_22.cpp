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
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input22.txt");
    string line;
    vector<int64_t> b;
    while (getline(file, line)) {
        b.push_back(stoll(line));
    }

    const int MOD = 16777216;
    for (auto &x : b) {
        for (int i =0 ; i < 2000 ; i++) {
            x = (x ^ (x * 64)) % MOD;
            int64_t y = x/ 32;
            x = (x ^ y) % MOD;
            y = x * 2048;
            x = (x ^ y) % MOD;
        }
    }

    int64_t sum = 0 ;
    for (auto x : b) {
        sum +=x;
    }

    cout << sum << '\n';
}

void PartTwo() {
    ifstream file("input22.txt");
    string line;
    vector<int64_t> b;
    while (getline(file, line)) {
        b.push_back(stoll(line));
    }

    using SEQ = array<int64_t ,4>;
    map<SEQ, int64_t> score;
    const int MOD = 16777216;
    for (auto &x : b) {
        set<SEQ> pass;
        vector<int> lastFour;
        lastFour.reserve(2000);
        for (int i =0 ; i < 2000 ; i++) {
            int64_t last = x%10;

            x = (x ^ (x * 64)) % MOD;
            int64_t y = x/ 32;
            x = (x ^ y) % MOD;
            y = x * 2048;
            x = (x ^ y) % MOD;

            int64_t diff = x%10 - last;
            lastFour.push_back(diff);
            int sz = static_cast<int>(lastFour.size());
            if (sz >= 4) {
                SEQ seq = {lastFour[sz-1], lastFour[sz-2], lastFour[sz-3], lastFour[sz-4]};
                if (!pass.contains(seq)) {
                    pass.insert(seq);
                    score[seq]+= x % 10;
                }
            }
        }
    }

    int64_t mx =0 ;

    cout << score.size() << '\n';
    for (auto &[ a , v] : score) {
        mx = max(mx,  v);
    }


    cout << mx << '\n' ;
}