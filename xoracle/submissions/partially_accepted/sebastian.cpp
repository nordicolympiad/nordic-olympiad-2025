#include <bits/stdc++.h> 
using namespace std; 
  
int main() { 
    ios::sync_with_stdio(0); cin.tie(0); 
    int N, Q; 
    cin >> N >> Q; 
    vector<int> val(N); 
    for (int i = 1; i < N; i++) {
        cout << "? 1 " << i+1 << endl;
        cin >> val[i]; 
    }
  
    for (auto x : val) { 
        int sum = 0; 
        for (auto &v : val) { 
            sum += v ^ x ^ 1; 
            if ((v ^ x ^ 1) <= 0) {
                sum = -1;
                break;
            }
        } 
        if (sum == 2*N-2) { 
            cout << '!'; 
            for (auto &v : val) cout << ' ' << (v ^ x ^ 1); 
            return 0; 
        } 
        sum = 0; 
        for (auto v : val) { 
            sum += v ^ x ^ 2; 
            if ((v ^ x ^ 2) <= 0) {
                sum = -1;
                break;
            }
        } 
        if (sum == 2*N-2) { 
            cout << '!'; 
            for (auto &v : val) cout << ' ' << (v ^ x ^ 2); 
            return 0; 
        } 
    } 
}

