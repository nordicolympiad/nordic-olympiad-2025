#include <iostream>
#include <fstream>
#include <vector>
#include <signal.h>

using namespace std;

#ifdef _MSC_VER
#   define NORETURN __declspec(noreturn)
#elif defined __GNUC__
#   define NORETURN __attribute__ ((noreturn))
#else
#   define NORETURN
#endif

FILE *fin;
FILE *fout;

vector<int> degrees;
int N, Q;

NORETURN void WA(string msg) {
	cout << 0 << endl;
	cerr << "Wrong Answer" << endl;
	cerr << msg << endl;
	exit(0);
}

inline int readValidInt() {
	int index;
	if (fscanf(fin, "%d", &index) != 1)
		WA("io error, could not read int");
	if (index < 0 || index > N)
		WA("invalid int");
	return index;
}

int main(int argc, char **argv) {
	signal(SIGPIPE, SIG_IGN);
	fout = fopen(argv[2], "a");
	if (fout == NULL)
		WA("couldn't open pipe");
	fin = fopen(argv[1], "r");

	int subtask; cin >> subtask;

	cin >> N >> Q;
	degrees.resize(N, 0);
	for (int _ = 1; _ < N; _++) {
		int v, u;
		cin >> v >> u;
		degrees[v]++;
		degrees[u]++;
	}

	if (fprintf(fout, "%d %d\n", N, Q) <= 0)
		WA("couldn't output problem parameters");
	if (fflush(fout) != 0)
		WA("error while flushing problem parameters");

	int qcount = 0;
	while (true) {
		char tmp[1000];
		if (fscanf(fin, "%999s", tmp) != 1)
			WA("io error, could not read command");
		string cmd(tmp);
		if (cmd == "?") { // Query
			int v = readValidInt(); 
			int u = readValidInt();
			if (v == 0 || u == 0)
				WA("invalid index");
			v -= 1;
			u -= 1;
			qcount++;
			if (qcount > Q) {
				fprintf(fout, "-1\n");
				fflush(fout);
				WA("query limit exceeded");
			}
			int ans = degrees[v] ^ degrees[u];
			if (fprintf(fout, "%d\n", ans) <= 0)
				WA("couldn't answer query");
			if (fflush(fout) != 0)
				WA("error while flushing query answer");
		}
		else if (cmd == "!") { // answer
			vector<int> cnt(N, 0);
			for (int i = 0; i < N; i++) {
				int d = readValidInt();
				cnt[d]++;
			}
			vector<int> facit(N, 0);
			for (auto d : degrees) facit[d]++;
			for (int i = 0; i < N; i++)
				if (cnt[i] != facit[i])
					WA("incorrect degree count");
			cout << 1 << endl;
			cerr << "Correct" << endl;
			break;
		}
		else WA("io error, invalid command");
	}
	return 0;
}
