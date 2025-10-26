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
  
    for (int x = 0; x <= N+1; x++) { 
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
    } 
}
