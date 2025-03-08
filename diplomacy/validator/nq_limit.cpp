#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 3) quit(_wa, "Incorrect usage");
	registerValidation();
	int mn = stoi(argv[1]);
	int mq = stoi(argv[2]);

	inf.readInt(1, mn, "n");
	inf.readSpace();
	int q = inf.readInt(1, mq, "q");
	inf.readEoln();
	for(int i = 0; i < q; i++) {
		string c = inf.readWord();
		if(c == "a") {
			inf.readSpace();
			inf.readInt();
			inf.readSpace();
			inf.readInt();
			inf.readSpace();
			inf.readInt();
		}
		inf.readEoln();
	}
	inf.readEof();
	return 0;
}
