#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 12
int N;
int map[MAXN][MAXN]; //1 : 전선, 2 : 코어

struct AXIS { int y; int x; };
vector<AXIS> unconn;


int count()
{
	int ret = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 1) ret++;
		}
	}
	return ret;
}

void dfs(int n, int cnt, const int& cnt_end, int& ans)
{
	if (cnt == cnt_end) { //불이 cnt_end만큼 켜짐 -> 1의 개수 세기
		int ret = count();
		if (ret < ans) ans = ret;
		return;
	}
	if (n == unconn.size()) return; //실패

	/*n번 core를 4방향으로 연결하기*/
	//북쪽
	bool nor = true;
	for (int y = unconn[n].y - 1; y >= 0; y--) {
		if (map[y][unconn[n].x]) { nor = false; break; }
	}
	if (nor) {
		for (int y = unconn[n].y - 1; y >= 0; y--) map[y][unconn[n].x] = 1;
		dfs(n + 1, cnt + 1, cnt_end, ans);
		for (int y = unconn[n].y - 1; y >= 0; y--) map[y][unconn[n].x] = 0;
	}
	//동쪽
	bool east = true;
	for (int x = unconn[n].x + 1; x < N; x++) {
		if (map[unconn[n].y][x]) { east = false; break; }
	}
	if (east) {
		for (int x = unconn[n].x + 1; x < N; x++) map[unconn[n].y][x] = 1;
		dfs(n + 1, cnt + 1, cnt_end, ans);
		for (int x = unconn[n].x + 1; x < N; x++) map[unconn[n].y][x] = 0;
	}
	//남쪽
	bool sou = true;
	for (int y = unconn[n].y + 1; y < N; y++) {
		if (map[y][unconn[n].x]) { sou = false; break; }
	}
	if (sou) {
		for (int y = unconn[n].y + 1; y < N; y++) map[y][unconn[n].x] = 1;
		dfs(n + 1, cnt + 1, cnt_end, ans);
		for (int y = unconn[n].y + 1; y < N; y++) map[y][unconn[n].x] = 0;
	}
	//서쪽
	bool west = true;
	for (int x = unconn[n].x - 1; x >= 0; x--) {
		if (map[unconn[n].y][x]) { west = false; break; }
	}
	if (west) {
		for (int x = unconn[n].x - 1; x >= 0; x--) map[unconn[n].y][x] = 1;
		dfs(n + 1, cnt + 1, cnt_end, ans);
		for (int x = unconn[n].x - 1; x >= 0; x--) map[unconn[n].y][x] = 0;
	}
	//안켜기
	dfs(n + 1, cnt, cnt_end, ans);
}

int solve()
{
	for (int i = unconn.size(); i >= 1; i--) {
		int ans = 0x7fffffff;
		dfs(0, 0, i, ans); //core 인덱스(n), 불 켠 core의 수(cnt), cnt_end, ans
		if (ans != 0x7fffffff) return ans;
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;

		//초기화
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		unconn.clear();

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> map[y][x];
				if (map[y][x]) {
					if (x == 0 || y == 0 || x == N - 1 || y == N - 1) {
						map[y][x] = 2; 
					}
					else {
						unconn.push_back({ y, x });
						map[y][x] = 2; 
					}
				}
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