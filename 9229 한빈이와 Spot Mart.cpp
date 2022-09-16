#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 20
int T, N, M;
int ans;

vector<int> cookie;


void two_pointers(int st)
{
	int sum;

	for (int s = st; s < N; s++) {
		int e = s + 1;
		while (e < N) {
			sum = cookie[s] + cookie[e];
			if (sum <= M && ans < sum) ans = sum;
			e++;
		}
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
		if (i < N - 1) two_pointers(i);
		cout << "#" << t + 1 << " " << ans << "\n";
	}
}


int main(void)
{
	input();
	return 0;
}