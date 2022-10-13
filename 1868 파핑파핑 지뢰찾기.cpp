#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 300
int N;
int total; //지뢰를 제외한 모든 칸의 개수
char map_c[MAXN][MAXN];
int map[MAXN][MAXN]; //지뢰 -1, 터진 부분 -2

struct ZERO {
	int y, x, cnt; //주변 0의 개수
	bool operator<(const ZERO& z) const {
		return cnt < z.cnt;
	}
};
priority_queue<ZERO> pq;

const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };


void dfs(int y, int x, int& pop_cnt)
{
	map[y][x] = -2;
	++pop_cnt;
	for (int d = 0; d < 8; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == 1) { //터트리고 말기
			map[ny][nx] = -2;
			++pop_cnt;
		}
		else if (map[ny][nx] == 0) {
			dfs(ny, nx, pop_cnt);
		}
	}
}

int get_bombcnt(int y, int x) //map_c에서 주변 * 찾아주기
{
	for (int d = 0; d < 8; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map_c[ny][nx] == '*') return 1;
	}
	return 0;
}

int get_zerocnt(int y, int x) //map에서 주변 0 찾아주기
{
	int ret = 0;
	for (int d = 0; d < 8; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == 0) ++ret;
	}
	return ret;
}

int solve()
{
	//지뢰 개수 구하기
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map_c[y][x] == '*') {
				map[y][x] = -1;
				continue;
			}
			int ret = get_bombcnt(y, x);
			map[y][x] = ret;
		}
	}
	//0들의 주변 0 개수 세기
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 0) {
				int ret = get_zerocnt(y, x);
				pq.push({ y, x, ret });
			}
		}
	}

	int pop_cnt = 0;
	int click = 0;
	while (!pq.empty()) {
		ZERO cur = pq.top(); pq.pop();
		if (map[cur.y][cur.x] == -2) continue;
		dfs(cur.y, cur.x, pop_cnt);
		++click;
		if (pop_cnt == click) return click;
	}
	//0을 다 터트려도 남는 부분이 있을 수 있음 -> total-pop_cnt만큼
	return click + (total - pop_cnt);
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;
		fill(&map_c[0][0], &map_c[MAXN - 1][MAXN], '\0');
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		pq = {};
		total = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> map_c[y][x];
				if (map_c[y][x] == '.') total++;
			}
		}
		cout << "#" << t << " " << solve() << "\n";
	}
}


int main()
{
	input();
	return 0;
}