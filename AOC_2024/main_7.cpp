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
    ifstream file("input7.txt");
    string ans, txt;
    string line;

    int64_t total =0 ;
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> ans;
        int64_t ANS = stoll(ans.substr(0, ans.size()- 1));
        vector<int64_t> v;
        while (iss >> txt) {
            v.push_back(stoll(txt));
        }

        int op = static_cast<int>(v.size()) - 1;
        bool good = false;
        for (int i = 0 ; i < ( 1 << op) ; i++) {
            int64_t cur = v[0];
            for (int j =0; j < op ; j++) {
                if (i & (1 << j )) {
                    cur += v[j + 1];
                }else {
                    cur *= v[j+1] ;
                }
            }

            if (cur == ANS) {
                good = true ;
            }
        }

        if (good) total += ANS;
    }

    cout << total << endl;
}

bool generate(vector<int> &op , vector<int64_t> &v,  int idx, const int64_t ans) {
    if (idx == static_cast<int>(op.size())) {
        int sz = static_cast<int>(v.size()) ;
        int64_t cur = v[0];
        for (int i =0 ; i < op.size(); i++) {
            if (op[i] ==  0) {
                cur *= v[i+1];
            }else if (op[i] == 1) {
                cur += v[i+1] ;
            } else {
                string cc = to_string(cur) + to_string(v[i+1]);
                cur = stoll(cc);
            }

        }
        return cur == ans;
    }
    bool p = false;
    for (int i =0 ; i< 3 ; i++) {
        op[idx] = i;
        p |= generate(op, v , idx+1, ans);
    }
    return p;
}


void PartTwo() {
    ifstream file("input7.txt");
    string ans, txt;
    string line;

    int64_t total =0 ;
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> ans;
        int64_t ANS = stoll(ans.substr(0, ans.size()- 1));
        vector<int64_t> v;
        while (iss >> txt) {
            v.push_back(stoll(txt));
        }

        int sz = static_cast<int>(v.size());
        vector<int> op(sz-1) ;

        bool res = generate(op, v, 0 , ANS) ;
        if (res) {
            total += ANS;
        }
    }

    cout << total << endl;
}

