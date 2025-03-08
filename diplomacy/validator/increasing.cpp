#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
	registerValidation();
	inf.readInt();
	inf.readSpace();
	int q = inf.readInt();
	inf.readEoln();
	int pp = 0;
	for(int i = 0; i < q; i++) {
		string c = inf.readWord();
		if(c == "a") {
			inf.readSpace();
			inf.readInt();
			inf.readSpace();
			inf.readInt();
			inf.readSpace();
			int p = inf.readInt();
			if(p <= pp) {
				quit(_wa, "Priorities are not increasing");
			}
			pp = p;
		}
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
