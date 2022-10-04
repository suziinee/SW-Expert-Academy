#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, W, H;
int map[15][12];
int ans;

struct AXIS { int y; int x; int e; };
queue<AXIS> q;


int count(int(*arr)[12])
{
	int cnt = 0;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (arr[y][x]) cnt++;
		}
	}
	return cnt;
}

void blow(int(*arr)[12], int y, int x)
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	q = {};
	q.push({ y, x, arr[y][x]});
	arr[y][x] = 0;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();
		if (cur.e == 1) continue;
		
		for (int i = 1; i <= cur.e - 1; i++) {
			for (int d = 0; d < 4; d++) {
				int nx = cur.x + i * dx[d];
				int ny = cur.y + i * dy[d];
				if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
				if (arr[ny][nx] == 0) continue;
				q.push({ ny, nx, arr[ny][nx] });
				arr[ny][nx] = 0;
			}
		}
	}
}

void fall_down(int(*arr)[12])
{
	queue<int> qq;
	for (int x = 0; x < W; x++) {
		for (int y = H - 1; y >= 0; y--) {
			if (arr[y][x]) qq.push(arr[y][x]);
			arr[y][x] = 0;
		}

		int y = H - 1;
		while (!qq.empty()) {
			arr[y--][x] = qq.front(); qq.pop();
		}
	}
}

void dfs(int(*arr)[12], int n)
{
	if (n == N) {
		int cnt = count(arr);
		if (cnt < ans) ans = cnt;
		return;
	}

	for (int x = 0; x < W; x++) {
		int y = 0; 
		while (y < H && arr[y][x] == 0) y++;
		if (y == H) {
			if (x == W - 1) dfs(arr, n + 1); //더이상 터트릴게 없음
			else continue;
		}

		//arr[y][x] 터트리기로 결정
		int back[15][12];
		copy(&arr[0][0], &arr[14][12], &back[0][0]); //arr를 back에 복사
		blow(arr, y, x);
		fall_down(arr);
		dfs(arr, n + 1);
		copy(&back[0][0], &back[14][12], &arr[0][0]); //back을 arr에 복사
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> W >> H;

		//초기화
		fill(&map[0][0], &map[14][12], 0);
		ans = 0x7fffffff;

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				cin >> map[y][x];
			}
		}

		dfs(map, 0);
		cout << "#" << t + 1 << " " << ans << "\n";
	}
}


int main()
{
	input();
	return 0;
}