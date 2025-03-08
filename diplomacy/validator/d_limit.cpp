#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
	if(argc != 2) quit(_wa, "Incorrect usage");
	int maxd = stoi(argv[1]);
	registerValidation();
	inf.readInt();
	inf.readSpace();
	int q = inf.readInt();
	inf.readEoln();
	int cd = 0;
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
		if(c == "d") cd++; 
		inf.readEoln();
	}
	if(cd > maxd) {
		quit(_wa, "Too many d commands. Expected at most " + to_string(maxd) + " but got " + to_string(cd));
	}
	inf.readEof();
	return 0;
}
