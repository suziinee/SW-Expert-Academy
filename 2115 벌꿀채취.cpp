#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 10
int N, M, C;
int map[MAXN][MAXN];
int ans;

struct AXIS { int y; int x; };
AXIS pick[2]; //채집의 시작위치


void dfs_harvest(vector<int>& vec, int s, int n, int sum, int square_sum, int& res)
{
	if (sum > C) return;
	if (square_sum > res) res = square_sum;
	if (n == M - 1) return;
	for (int i = s; i < M; i++) {
		dfs_harvest(vec, i + 1, n + 1, sum + vec[i], square_sum + (vec[i] * vec[i]), res);
	}
}

int harvest()
{
	int sum = 0;
	for (AXIS p : pick) {

		int tmp_sum = 0;
		for (int x = p.x; x < p.x + M; x++) tmp_sum += map[p.y][x];

		if (tmp_sum <= C) { //그대로 모두 채취
			for (int x = p.x; x < p.x + M; x++) sum += map[p.y][x] * map[p.y][x];
		}
		else { //1개~M-1개 조합 돌리기
			vector<int> vec; //M개짜리 벡터
			for (int x = p.x; x < p.x + M; x++) vec.push_back(map[p.y][x]);
			int res = 0;
			dfs_harvest(vec, 0, 0, 0, 0, res); //vec, s, n, sum, square_sum, res
			sum += res;
		}
	}
	return sum;
}

void solve()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x <= N - M; x++) {
			pick[0] = { y, x };
			for (int p = y; p < N; p++) {
				for (int q = 0; q <= N - M; q++) {
					if (p == y && q < x + M) continue;
					pick[1] = { p, q };
					int ret = harvest();
					if (ret > ans) ans = ret;
				}
			}
		}
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M >> C;

		//초기화
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		pick[0] = {}; pick[1] = {};
		ans = 0;

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> map[y][x];
			}
		}

		solve();
		cout << "#" << t + 1 << " " << ans << "\n";
	}
}


int main()
{
	input();
	return 0;
}