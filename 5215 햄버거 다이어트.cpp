#include <iostream>
#include <vector>
using namespace std;

#define MAXN 20
int T, N, L;
int ans;

struct MAT { int score; int cal; };
vector<MAT> mat;


void dfs(int n, int score_sum, int cal_sum)
{
	if (cal_sum > L) return;
	if (cal_sum <= L && score_sum > ans) ans = score_sum;
	if (n == N) return;

	//n번째 mat 포함
	dfs(n + 1, score_sum + mat[n].score, cal_sum + mat[n].cal);
	//n번째 mat 미포함
	dfs(n + 1, score_sum, cal_sum);
}

void input()
{
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> L;

		//초기화
		mat = {};
		ans = -1;

		int s, c;
		for (int i = 0; i < N; i++) {
			cin >> s >> c;
			mat.push_back({ s, c });
		}

		dfs(0, 0, 0);
		cout << "#" << t + 1 << " " << ans << "\n";
	}
}


int main(void)
{
	input();
	return 0;
}