#include "xoracle.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cassert>

using namespace std;

static FILE *fin;
static FILE *fout;

int query(int v, int u) {
    fprintf(fout, "? %d %d\n", v, u);
    fflush(fout);
    int result;
    if (fscanf(fin, "%d", &result) != 1) {
        cerr << "tester error" << endl;
        cerr << "could not read query response" << endl;
        exit(0);
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "grader error" << endl;
        cerr << "number of arguments isn't 3" << endl;
        exit(0);
    }

    fin = fopen(argv[1], "r11");
    fout = fopen(argv[2], "a");

    int N, Q;
    if (fscanf(fin, "%d %d", &N, &Q) != 2) {
        cerr << "tester error" << endl;
        cerr << "could not read 'n'" << endl;
        exit(0);
    }

	vector<int> deg = degrees(N, Q);
    fprintf(fout, "!");
	for (auto d : deg) fprintf(fout, " %d", d);
    fflush(fout);
    return 0;
}
