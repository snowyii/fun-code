#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
void PartOne();
void PartTwo();

using namespace std;

struct Tk {
    vector<string> tokens;
    bool isOK() const {
        return !tokens.empty();
    }
};

Tk split(const string &s) {
    istringstream iss(s);
    string tok;
    Tk token;
    while (iss >> tok) {
        token.tokens.push_back(tok);
    }

    return token;
}



int main() {
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input2.txt");
    string line;
    int cnt =0 ;
    while (getline(file , line)) {
        vector<int> v;
        istringstream iss(line);
        int x;
        while (iss >> x) {
            v.push_back(x);
        }

        int d = 0, e = 0 ;
        for (int i = 1 ;i < static_cast<int>(v.size()); i++) {
            int diff = v[i] - v[i-1] ;
            if (diff >=  1 && diff <=3 ) {
                d++;
            }
            if (diff >= -3 && diff <= -1) {
                e++;
            }
        }

        if (d + 1  == v.size() || e+ 1  == v.size()) {
            cnt++;
        }
    }
    cout << cnt << '\n';
}

void PartTwo() {
    ifstream file("input2.txt");
    string line;
    int cnt =0 ;
    while (getline(file , line)) {
        vector<int> v;
        istringstream iss(line);
        int x;
        while (iss >> x) {
            v.push_back(x);
        }
        int d = 0, e = 0;
        int sz = static_cast<int>(v.size());
        for (int i = 1 ;i < static_cast<int>(v.size()); i++) {
            int diff = v[i] - v[i-1] ;
            if (diff >=  1 && diff <=3 ) {
                d++;
            }
            if (diff >= -3 && diff <= -1) {
                e++;
            }
        }
        bool good = false;
        if (d + 1  == v.size() || e+ 1  == v.size()) {
            cnt++;
            good = true ;
        }

        if (!good) {
            for (int i =0 ; i < sz && !good ; i++) {
                int old = v[i] ;
                v[i] = -1;
                d =0 , e =0 ;
                for (int j = 1; j < sz;  j++) {
                    if (v[j] != -1) {
                        int diff = 0 ;
                        if (v[j-1] != -1) {
                            diff = v[j] - v[j-1] ;
                        }else if (v[j-1] == -1 && j-2 >= 0) {
                            diff = v[j] - v[j-2];
                        }

                        if (diff >=  1 && diff <=3 ) {
                            d++;
                        }
                        if (diff >= -3 && diff <= -1) {
                            e++;
                        }
                    }
                }

                if (d + 2 == sz || e + 2 == sz ) {
                    cnt++;
                    good = true;
                }
                v[i] = old;
            }
        }
    }
    cout << cnt << '\n';
}