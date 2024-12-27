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
    // PartOne();
    PartTwo();
}

void PartOne() {
    ifstream file("input17.txt");
    string line;
    int64_t A , B , C ;
    vector<int> inst;
    while (getline(file, line)) {
        if (line.find("A") != string::npos) {
            A = stoll(line.substr(11));
        }
        if (line.find("B") != string::npos) {
            B = stoll(line.substr(11));
        }
        if (line.find("C") != string::npos) {
            C = stoll(line.substr(11));
        }

        if (line.find("Program") != string::npos) {//     string val ;
            stringstream ss(line.substr(9));
            while (getline(ss, line, ',')) {
                inst.push_back(stoi(line));
            }
        }
    }
    auto getVal = [&A, &B, &C](int op) -> int64_t {
        if (op >= 0 && op <= 3 ) {
            return op;
        }
        if (op == 4) return A;
        if (op == 5) return B;
        if (op == 6) return C;

        assert(false);
        return 0;
    };

    for (int i =0 ; i + 1 < static_cast<int>(inst.size()) ;) {
        // cout << "=> " << A << " " << B << " " <<C << '\n' ;

        int ins = inst[i];
        int op = inst[i+1] ;
        int64_t operand = getVal(op);
        if (ins == 0) {
            int64_t nxt =0 ;
            if (operand < 63)  nxt = A / (1LL << operand);
            A = nxt;
        }else if (ins == 1) {
            B ^= op;
        }else if (ins == 2) {
            B = operand % 8;
        }else if (ins == 3) {
            if (A != 0) {
                i = op;
                continue;
            }
        }else if ( ins == 4) {
            B ^= C;
        }else if (ins == 5) {
            cout << operand%8 << ",";
        }else if ( ins == 6) {
            int64_t nxt =0 ;
            if (operand < 63)  nxt = A / (1LL << operand);
            B = nxt;
        }else if (ins == 7) {
            int64_t nxt =0 ;
            if (operand < 63)  nxt = A / (1LL << operand);
            C = nxt;
        }


        i+=2;
    }


}

void PartTwo() {
    string ANS = "2411751542550330";
    ifstream file("input17.txt");
    string line;
    int64_t AA , BB , CC ;
    vector<int> inst;
    while (getline(file, line)) {
        if (line.find("A") != string::npos) {
            AA = stoll(line.substr(11));
        }
        if (line.find("B") != string::npos) {
            BB = stoll(line.substr(11));
        }
        if (line.find("C") != string::npos) {
            CC = stoll(line.substr(11));
        }

        if (line.find("Program") != string::npos) {//     string val ;
            stringstream ss(line.substr(9));
            while (getline(ss, line, ',')) {
                inst.push_back(stoi(line));
            }
        }
    }

    // adjust range for prefix => suffix will be a pattern
    // int64_t base =100000LL;
    // for (int64_t  a= 1642784956 ; a <= 1642784978; a++ )
    long long base =100000LL;
    for (int64_t a=  1642784956 * base  ; a <= 1642784978 * base ; a++) {
        // A = a * base;
        int64_t A = a , B = BB, C = CC;
        auto getVal = [&A, &B, &C](int op) -> int64_t {
            if (op >= 0 && op <= 3 ) {
                return op;
            }
            if (op == 4) return A;
            if (op == 5) return B;
            if (op == 6) return C;

            assert(false);
            return 0;
        };

        string cur;
        for (int i =0 ; i + 1 < static_cast<int>(inst.size()) ;) {
            int ins = inst[i];
            int op = inst[i+1] ;
            int64_t operand = getVal(op);
            if (ins == 0) {
                int64_t nxt =0 ;
                if (operand < 63)  nxt = A / (1LL << operand);
                A = nxt;
            }else if (ins == 1) {
                B ^= op;
            }else if (ins == 2) {
                B = operand % 8;
            }else if (ins == 3) {
                if (A != 0) {
                    i = op;
                    continue;
                }
            }else if ( ins == 4) {
                B ^= C;
            }else if (ins == 5) {
                cur += to_string(operand%8);
            }else if ( ins == 6) {
                int64_t nxt =0 ;
                if (operand < 63)  nxt = A / (1LL << operand);
                B = nxt;
            }else if (ins == 7) {
                int64_t nxt =0 ;
                if (operand < 63)  nxt = A / (1LL << operand);
                C = nxt;
            }


            i+=2;
        }

        cout << a << " " <<  cur << ' ' << cur.length() << '\n' ;
        if (cur == ANS) {
            cout << "a ==> " << a << " " << cur.size() <<  '\n' ;
            return;
        }
        if (cur.length() > 16) {
            break;
        }
    }
}