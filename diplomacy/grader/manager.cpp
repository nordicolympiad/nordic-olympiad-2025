#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

/******************************** Begin testlib-related material ********************************/

inline FILE* openFile(const char* name, const char* mode) {
	FILE* file = fopen(name, mode);
	if (!file)
		quitf(_fail, "Could not open file '%s' with mode '%s'.", name, mode);
	closeOnHalt(file);
	return file;
}


vector<FILE*> mgr2sol, sol2mgr;
FILE* log_file = nullptr;

void nullifyFile(int idx) {
	mgr2sol[idx] = sol2mgr[idx] = nullptr;
}

void registerManager(int num_processes, char* argv[]) {

	{//Keep alive on broken pipes
		//signal(SIGPIPE, SIG_IGN);
		struct sigaction sa;
		sa.sa_handler = SIG_IGN;
		sigaction(SIGPIPE, &sa, NULL);
	}


	mgr2sol.resize(num_processes);
	sol2mgr.resize(num_processes);
	for (int i = 0; i < num_processes; i++) {
		mgr2sol[i] = openFile(argv[1 + 2*i + 1], "a");
		sol2mgr[i] = openFile(argv[1 + 2*i + 0], "r");
	}
}
/********************************* End testlib-related material *********************************/


// utils

#define rep(i, n) for(int i = 0, i##__n = (int)(n); i < i##__n; ++i)

// grader/manager protocol

int fifo_idx = 0;

void out_flush() {
	fflush(mgr2sol[fifo_idx]);
}

void write_int(int x) {
	if(1 > fprintf(mgr2sol[fifo_idx], "%d ", x)) {
		nullifyFile(fifo_idx);
		cerr << "Could not write int to mgr2sol" << endl;
		exit(0);
	}
}
void write_int_endl(int x) {
	if(1 > fprintf(mgr2sol[fifo_idx], "%d\n", x)) {
		nullifyFile(fifo_idx);
		cerr << "Could not write int to mgr2sol" << endl;
		exit(0);
	}
}

void write_string(string s) {
	if(1 > fprintf(mgr2sol[fifo_idx], "%s ", s.c_str())) {
		nullifyFile(fifo_idx);
		cerr << "Could not write string to mgr2sol" << endl;
		exit(0);
	}
}

void write_string_endl(string s) {
	if(1 > fprintf(mgr2sol[fifo_idx], "%s\n", s.c_str())) {
		nullifyFile(fifo_idx);
		cerr << "Could not write string to mgr2sol" << endl;
		exit(0);
	}
}

int read_int() {
	int x;
	if(1 != fscanf(sol2mgr[fifo_idx], "%d", &x)) {
		nullifyFile(fifo_idx);
		cerr << "Could not read int from sol2mgr:" <<  fifo_idx << endl;
		exit(0);
	}
	return x;
}

// problem logic

int N, Q;
std::vector<std::vector<int>> adj;

struct query {
	string type;
	int u,v,p;
};

int main(int argc, char *argv[]) {
	registerManager(1, argv);
	argc++;
	// read input
	cin >> N >> Q;
	std::vector<query> C(Q);
	int dCount = 0; 
	rep(i, Q) {
		cin >> C[i].type;
		if(C[i].type == "a") {
			cin >> C[i].u;
			cin >> C[i].v;
			cin >> C[i].p;
		} else if(C[i].type == "d") {
			dCount++;
		}
	}
	
	int cA = 0;
	std::vector<int> A(dCount);

	write_int(N);
    write_int_endl(Q);
	rep(i, Q) {
		if(C[i].type == "a") {
			write_string(C[i].type);
			write_int(C[i].u);
			write_int(C[i].v);
			write_int_endl(C[i].p);
		} else if (C[i].type == "r") {
			write_string_endl(C[i].type);
		} else if (C[i].type == "d") {
			write_string_endl(C[i].type);
			out_flush();
			A[cA++] = read_int();
		}
	}
	out_flush();
	for(int i = 0; i < cA; i++) cout << A[i] << "\n";

	return 0;
}