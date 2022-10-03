#include <iostream>
#include <algorithm>
using namespace std;

int gu[9];
int in[9];
bool chk[9];
int win; int lose;


void dfs(int n, int gu_score, int in_score)
{
	if (gu_score > 171) {
		win++; return;
	}
	if (in_score > 171) {
		lose++; return;
	}
	if (n == 9) {
		if (gu_score > in_score) win++;
		else if (gu_score < in_score) lose++;
		return;
	}

	for (int i = 0; i < 9; i++) {
		if (chk[i]) continue;
		chk[i] = true;
		
		if (in[i] > gu[n]) dfs(n + 1, gu_score, in_score + in[i] + gu[n]);
		else if (in[i] < gu[n]) dfs(n + 1, gu_score + in[i] + gu[n], in_score);

		chk[i] = false;
	}
}

inline bool is_gu(int& n)
{
	for (int i = 0; i < 9; i++) {
		if (gu[i] == n) return true;
	}
	return false;
}

void input()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		
		for (int i = 0; i < 9; i++) {
			cin >> gu[i];
		}

		int idx = 0;
		for (int i = 1; i <= 18; i++) {
			if (!is_gu(i)) in[idx++] = i;
		}

		//초기화
		win = 0; lose = 0;
		fill(chk, chk + 9, false);

		dfs(0, 0, 0);
		cout << "#" << t + 1 << " " << win << " " << lose << "\n";
	}
}


int main()
{
	input();
	return 0;
}