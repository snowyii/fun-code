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


void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input13.txt");
    string line;
    vector<pair<int ,int>> A, B, target;
    while (getline(file, line)) {
        if (line.find("Button A:") != string::npos ) {
            string cut = line.substr(12);
            stringstream ss(cut);
            vector<int> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y+") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoi(cut));
            }
            A.emplace_back(t[0] , t[1]);
        }
        if (line.find("Button B:") != string::npos) {
            string cut = line.substr(12);
            stringstream ss(cut);
            vector<int> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y+") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoi(cut));
            }
            B.emplace_back(t[0] , t[1]);
        }
        if (line.find("Prize:") != string::npos) {
            string cut = line.substr( 9);
            stringstream ss(cut);
            vector<int> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y=") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoi(cut));
            }
            target.emplace_back(t[0] , t[1]);
        }
    }

    long long cnt =0 ;

    for (int t = 0 ; t < target.size(); t++) {
        cout << target[t].first << " " << target[t].second << endl;
        int best = INT_MAX;
        for (int i =0 ; i <= 100 ; i++) {
            for (int j =0 ; j <= 100 ; j++) {
                int posX = i * A[t].first + j * B[t].first;
                int posY = i * A[t].second + j * B[t].second;
                if (posX == target[t].first && posY == target[t].second) {
                    best = min(best , 3 * i + j);
                }
            }
        }

        if (best != INT_MAX) {
            cnt += best;
        }
    }

    cout << cnt << endl;
}

void PartTwo() {
    ifstream file("input13.txt");
    string line;
    vector<pair<long ,long>> A, B, target;
    while (getline(file, line)) {
        if (line.find("Button A:") != string::npos ) {
            string cut = line.substr(12);
            stringstream ss(cut);
            vector<int> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y+") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoi(cut));
            }
            A.emplace_back(t[0] , t[1]);
        }
        if (line.find("Button B:") != string::npos) {
            string cut = line.substr(12);
            stringstream ss(cut);
            vector<int> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y+") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoi(cut));
            }
            B.emplace_back(t[0] , t[1]);
        }
        if (line.find("Prize:") != string::npos) {
            string cut = line.substr( 9);
            stringstream ss(cut);
            vector<long long> t;
            while (getline(ss , cut, ',')) {
                if (cut.find("Y=") != string::npos) {
                    cut = cut.substr(3);
                }
                t.push_back(stoll(cut) + 10000000000000LL);
            }
            target.emplace_back(t[0] , t[1]);
        }
    }

    long long cnt =0 ;

    for (int t = 0 ; t < target.size(); t++) {
        // ax + by =c
        // dx + ey = f
        using ll =  long long;
        ll a = A[t].first , b = B[t].first, c = target[t].first;
        ll d = A[t].second, e = B[t].second, f = target[t].second;

        ll q = c *e - f * b ;
        ll p = a * e - d * b;

        if (q % p == 0) {
            ll X = q / p;
            ll g = c - a * X;
            if (g % b == 0) {
                ll Y = g/b;
                if (X >= 0 && Y >= 0) {
                    cnt += 3LL * X + Y;
                }
            }

        }

    }

    cout << cnt << endl;
}