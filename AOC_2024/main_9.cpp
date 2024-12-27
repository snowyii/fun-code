#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <array>

void PartOne();
void PartTwo();

using namespace std;

int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input9.txt");
    string s;
    getline(file, s);
    cout << s.length() << endl;
    vector<int> v;
    int cur =0 ;
    for (int i =0 ; i < static_cast<int>(s.length()) ; i++ ) {
        if (i % 2 == 0) {
                for (int j =0 ; j < s[i] - '0'; j++) {
                    v.push_back(cur);
                }
                cur++;
        }else {
            for (int  j =0 ; j < s[i] - '0' ; j++) {
                    v.push_back(-1);
            }
        }
    }

    int i =0 ;
    int j = static_cast<int>(v.size() - 1);

    while (i < j) {
        if (v[i] == -1) {
            while (i < j && v[j] == -1) {
                j--;
            }
            if (i < j) {
                v[i] = v[j];
                v[j] = -1;
                j--;
            }
        }else {
            i++;
        }
    }

    int64_t total =0 ;
    for (int i =0 ; i < static_cast<int>(v.size()) ; i++) {
        if (v[i] != -1) total += static_cast<int64_t>(v[i]) * i;
    }
    for (auto x : v) {
        if (x == -1) cout << '.';
        cout << x ;
    }

    cout << '\n' ;
    cout << total << endl;
}

void PartTwo() {
    ifstream file("input9.txt");
    string s;
    getline(file, s);
    vector<array<int ,3>> v;
    int cur =0 ;
    int pos =0 ;
    for (int i =0 ; i < static_cast<int>(s.length()) ; i++ ) {
        if (i % 2 == 0) {
            v.push_back(array<int, 3>{cur , s[i] - '0', pos});
            cur++;
        }else {
            v.push_back(array<int, 3>{-1, s[i] - '0', pos }) ;
        }
        pos += s[i] - '0' ;
    }

    vector<array<int ,3>> res;
    const int sz = static_cast<int>(v.size());
    for (int i = sz - 1; i >= 0 ; i--) {
        auto [value ,freq ,_] = v[i];
        if (value != -1) {
            for (int j =0 ; j < i ; j++) {
                auto [ val , f, pos] = v[j];
                if (val == -1 && f >= freq) {
                    res.push_back(array<int, 3>{value , freq, pos});
                    v[j] = array<int,3>{val , f -freq, pos + freq};
                    v[i] = array<int, 3>{-1 , freq, 0};
                    break;
                }
            }
        }
    }

    int64_t total =0 ;
    for (auto [ a , f , c] : v) {
        if ( a != -1) {
            total += static_cast<int64_t>(a) * (f ) * (c + c + f -1) /2 ;
        }
    }

    for (auto [ a , b, c ] : res) {
        total += static_cast<int64_t>(a) * (b) * (c + c + b - 1) /2;
    }

    cout << total << endl;
}
