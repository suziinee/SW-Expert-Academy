#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int ans;
int pick[10]; //s1에 들어갈 숫자

struct AXIS { int y, x; };
vector<AXIS> people;

struct STEP { int y, x, t; };
STEP s1, s2;

struct STATUS { int arv; int rem; }; //도착 시간+1, 계단 남은 시간(계단 안올라간 사람은 -1, 계단 끝난 사람은 0)
bool compare(const STATUS& s1, const STATUS& s2) { return s1.arv < s2.arv; }


int simul(int* arr, int n, STEP& s)
{
	int time = 0x7fffffff;
	//STATUS 구하기
	vector<STATUS> st;
	for (int i = 0; i < n; i++) {
		int dist = abs(s.y - people[arr[i]].y) + abs(s.x - people[arr[i]].x);
		st.push_back({ dist + 1, -1 });
		if (time > dist) time = dist;
	}

	sort(st.begin(), st.end(), compare);
	int q = 0; //현재 계단에 있는 사람
	int complete = 0; //계단 다 내려온 사람
	while (complete < n) {
		time++;
		for (int i = 0; i < n; i++) {
			if (st[i].rem == 0) continue;
			if (st[i].rem > 0) { //이미 올라탄 사람은 하나씩 내려가기
				st[i].rem -= 1;
				if (st[i].rem == 0) {
					q--; complete++;
				}
				continue;
			}

			if (st[i].rem == -1 && st[i].arv <= time && q < 3) { //계단 올라타기
				st[i].rem = s.t;
				q++;
			}
		}
	}
	
	if (time == 0x7fffffff) return 0;
	return time;
}

void dfs(int n, int s)
{
	if (n >= 0) { //0개~people수 만큼의 조합에 대해서
		//s1은 n명, s2는 people-n명
		int unpick[10] = { 0 }; int u = 0;
		for (int i = 0; i < people.size(); i++) {
			bool fg = false;
			for (int j = 0; j < n; j++) { //pick에 있는지 확인
				if (i == pick[j]) { fg = true; break; }
			}
			if (!fg) unpick[u++] = i;
		}
		int ret1 = simul(pick, n, s1);
		int ret2 = simul(unpick, u, s2);
		if (max(ret1, ret2) < ans) ans = max(ret1, ret2);
	}
	if (n == people.size()) return;

	for (int i = s; i < people.size(); i++) {
		pick[n] = i;
		dfs(n + 1, i + 1);
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;

		//초기화
		ans = 0x7fffffff;
		people.clear();
		fill(pick, pick + 10, 0);
		s1 = { -1, -1, -1 };
		s2 = { -1, -1, -1 };

		int n;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> n;
				if (n) {
					if (n == 1) {
						people.push_back({ y, x });
					}
					else {
						if (s1.y == -1) {
							s1.y = y; s1.x = x; s1.t = n;
						}
						else {
							s2.y = y; s2.x = x; s2.t = n;
						}
					}
				}
			}
		}

		dfs(0, 0);
		cout << "#" << t << " " << ans << "\n";
	}
}


int main()
{
	input();
	return 0;
}