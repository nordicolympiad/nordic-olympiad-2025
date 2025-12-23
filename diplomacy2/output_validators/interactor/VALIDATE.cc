#include "validate.h"

using namespace std;

using ll = long long;

int main(int argc, char **argv) {
    init_io(argc, argv);

    int N,Q;
    judge_in >> N >> Q;

    cout << N << ' ' << Q << '\n';

    while (Q--) {
    	char t;
		judge_in >> t;
		if (t == 'a')
		{
			int u, v, p;
			judge_in >> u >> v >> p;
			cout << t << ' ' << u << ' ' << v << ' ' << p << '\n';
		}
		else if (t == 'r')
		{
            cout << t << '\n';
		}
		else if (t == 'd')
		{
			cout << 'd' << endl;
            ll resp;
            if (!(cin >> resp)) wrong_answer("EOF");
            ll judge_resp;
            if (!(judge_ans >> judge_resp)) judge_error("EOF in .ans file");
            if (resp != judge_resp) {
                wrong_answer("Incorrect output");
            }
		}
        else assert(0);
	}
    cout << flush;

	string trailing;
	if (cin >> trailing) {
		wrong_answer("Trailing output");
	}
    if (judge_ans >> trailing) {
        judge_error("Judge has trailing output");
    }

    accept();
}
