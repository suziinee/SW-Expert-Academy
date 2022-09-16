#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 20
int T, N, M;
int ans;

vector<int> cookie;


void dfs(int n, int s, int sum)
{
	if (sum > M) return;
	if (n == 2) {
		if (sum <= M && ans < sum) ans = sum;
		return;
	}

	for (int i = s; i < N; i++) {
		dfs(n + 1, i + 1, sum + cookie[i]);
	}
}

void input()
{
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M;

		//초기화
		cookie = {};
		ans = -1;

		int c;
		for (int i = 0; i < N; i++) {
			cin >> c;
			cookie.push_back(c);
		}

		sort(cookie.begin(), cookie.end(), greater<int>());
		int i;
		for (i = 0; i < N; i++) {
			if (cookie[i] < M) break;
		}
		dfs(0, i, 0);
		cout << "#" << t + 1 << " " << ans << "\n";
	}
}


int main(void)
{
	input();
	return 0;
}