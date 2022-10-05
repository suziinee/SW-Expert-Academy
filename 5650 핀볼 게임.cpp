#include <iostream>
#include <unordered_map>
using namespace std;

#define MAXN 100
int N;
int map[MAXN][MAXN];

struct AXIS { int y; int x; };
vector<AXIS> blank;
unordered_map<int, AXIS> wormhole;

struct PIN { int y; int x; int d; int score; };
const int dx[] = { 0, 1, -1, 0 };
const int dy[] = { -1, 0, 0, 1 };

int wall[4] = { 3, 2, 1, 0 };
int block[6][4] = {
	{},
	{3, 2, 0, 1}, {1, 2, 3, 0}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 2, 1, 0} };


int play(const AXIS& b, int d)
{
	PIN pin = { b.y, b.x, d, 0 };

	while (true) {
		int nx = pin.x + dx[pin.d];
		int ny = pin.y + dy[pin.d];
		if (nx == b.x && ny == b.y) return pin.score;
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
			pin.d = wall[pin.d];
			pin.x = nx;
			pin.y = ny;
			pin.score += 1;
			continue;
		}
		switch (map[ny][nx]) {
		case 0: {
			pin.x = nx;
			pin.y = ny;
			break;
		}
		case -1: {
			return pin.score;
		}
		case 1: case 2: case 3: case 4: case 5: {
			pin.d = block[map[ny][nx]][pin.d];
			pin.x = nx;
			pin.y = ny;
			pin.score += 1;
			break;
		}
		case 6: case 7: case 8: case 9: case 10: {
			AXIS after = wormhole.find(map[ny][nx] + 100)->second;
			pin.x = after.x;
			pin.y = after.y;
			break;
		}
		case 106: case 107: case 108: case 109: case 110: {
			AXIS after = wormhole.find(map[ny][nx] - 100)->second;
			pin.x = after.x;
			pin.y = after.y;
			break;
		}
		}
	}
}

int solve()
{
	int ans = 0;
	for (AXIS b : blank) {
		for (int d = 0; d < 4; d++) {
			int ret = play(b, d);
			if (ret > ans) ans = ret;
		}
	}
	return ans;
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;

		//초기화
		blank.clear();
		wormhole.clear();
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);

		int n;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> n;
				map[y][x] = n;
				if (n == 0) {
					blank.push_back({ y, x });
				}
				else if (n >= 6 && n <= 10) {
					if (wormhole.find(n) == wormhole.end()) {
						wormhole.insert({ n, {y, x} });
					}
					else {
						map[y][x] = n + 100;
						wormhole.insert({ n + 100, {y, x} });
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