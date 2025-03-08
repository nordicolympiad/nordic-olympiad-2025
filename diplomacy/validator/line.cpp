#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	registerValidation();
	inf.readInt();
	inf.readSpace();
	int q = inf.readInt();
	inf.readEoln();
	for(int i = 0; i < q; i++) {
		string c = inf.readWord();
		if(c == "a") {
			inf.readSpace();
			int u = inf.readInt();
			inf.readSpace();
			int v = inf.readInt();
			inf.readSpace();
			inf.readInt();
			if(u+1 != v) {
				quit(_wa, "Graph is not a line");
			}
		}
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
