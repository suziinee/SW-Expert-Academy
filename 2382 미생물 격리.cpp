#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define MAXN 100
int N, M, K;
int map[MAXN][MAXN]; //미생물 군집의 숫자 1~K 기록

struct GROUP {
	int y, x;
	int size;
	int d;
};
unordered_map<int, GROUP> group;

const int dx[] = { 0, 0, -1, 1 }; //up down left right
const int dy[] = { -1, 1, 0, 0 };
const int dir[] = { 1, 0, 3, 2 };


void move_group()
{
	int back[MAXN][MAXN][2] = {0,}; //[0]은 가장 큰 미생물 군집의 번호, [1]은 그 군집의 크기
	//이때 합쳐진 크기는 군집의 size에 저장되어 있고 [1]은 합쳐질 당시의 초반 크기
	
	for (int i = 1; i <= K; i++) {
		if (group.find(i) == group.end()) continue;
		
		GROUP& g = group[i];
		int nx = g.x + dx[g.d];
		int ny = g.y + dy[g.d];
		if (nx == 0 || ny == 0 || nx == N - 1 || ny == N - 1) { //미생물 죽고 방향 전환
			g.size /= 2;
			g.d = dir[g.d];
			if (g.size == 0) {
				group.erase(i);
				continue;
			}
		}
		
		if (back[ny][nx][0]) { //가려는 곳에 미생물 존재
			int bef_max = back[ny][nx][0];
			if (g.size > back[ny][nx][1]) { //최대 미생물 군집 갱신
				back[ny][nx][0] = i;
				back[ny][nx][1] = g.size; //합쳐질 당시의 크기 저장
				g.size += group[bef_max].size;
				g.x = nx;
				g.y = ny;
				group.erase(bef_max); //bef_max는 사라짐
			}
			else { //i가 합쳐짐 -> i는 사라짐
				group[bef_max].size += g.size;
				group.erase(i);
			}
		}
		else { //가려는 곳이 빈곳
			back[ny][nx][0] = i;
			back[ny][nx][1] = g.size;
			g.x = nx;
			g.y = ny;
		}
	}

	//back을 map으로 옮기기
	fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (back[y][x][0]) map[y][x] = back[y][x][0];
		}
	}
}

int solve()
{
	for (int t = 0; t < M; t++) {
		move_group();
	}

	int cnt = 0;
	for (auto it = group.begin(); it != group.end(); it++) {
		cnt += (it->second).size;
	}
	return cnt;
}


void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N >> M >> K;

		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		group.clear();

		int y, x, size, d;
		for (int i = 1; i <= K; i++) {
			cin >> y >> x >> size >> d;
			d--;
			group.insert({ i, {y, x, size, d} });
			map[y][x] = i;
		}

		cout << "#" << t << " " << solve() << "\n";
	}
}


int main()
{
	input();
	return 0;
}