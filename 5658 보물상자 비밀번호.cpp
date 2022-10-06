#include <iostream>
#include <cmath>
#include <deque>
#include <set>
#include <unordered_map>
using namespace std;

int N, K;
deque<char> dq;
set<int, greater<int>> s;
unordered_map<char, int> map;


void rotate()
{
	dq.push_front(dq.back());
	dq.pop_back();
}

int calcul(string& str, int n)
{
	int ret = 0;
	for (int i = 0; i < n; i++) {
		ret += pow(16, i) * map[str[n - 1 - i]];
	}
	return ret;
}

void separate()
{
	int n = N / 4; //자릿수
	for (int i = 0; i < N; i+=n) {
		string str;
		for (int j = 0; j < n; j++) {
			str += dq[i + j];
		}
		int ret = calcul(str, n);
		if (s.find(ret) == s.end()) s.insert(ret);
	}
}

int solve()
{
	//N번 rotate
	for (int i = 0; i < N; i++) {
		rotate();
		separate();
	}
	
	int i = 1;
	for (auto it = s.begin(); it != s.end(); it++) {
		if (i == K) return *it;
		i++;
	}
}

void map_init()
{
	map.insert({ '0', 0 });
	map.insert({ '1', 1 });
	map.insert({ '2', 2 });
	map.insert({ '3', 3 });
	map.insert({ '4', 4 });
	map.insert({ '5', 5 });
	map.insert({ '6', 6 });
	map.insert({ '7', 7 });
	map.insert({ '8', 8 });
	map.insert({ '9', 9 });
	map.insert({ 'A', 10 });
	map.insert({ 'B', 11 });
	map.insert({ 'C', 12 });
	map.insert({ 'D', 13 });
	map.insert({ 'E', 14 });
	map.insert({ 'F', 15 });
}

void input()
{
	int T;
	cin >> T;
	map_init();
	for (int t = 1; t <= T; t++) {
		cin >> N >> K;

		dq.clear();
		s.clear();

		char c;
		for (int i = 0; i < N; i++) {
			cin >> c;
			dq.push_back(c);
		}

		cout << "#" << t << " " << solve() << "\n";
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	input();
	return 0;
}