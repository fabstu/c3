#define DEBUG2
#define DEBUG32

#include "std.h"

using lll = __int128;

struct Kingdoms {
	vector<lll> soldiers;
	vector<vector<int>> adj;
	vector<bool> visited;

	vector<int> a, b;

	Kingdoms(vector<lll> &_soldiers, vector<vector<int>> _adj) {
		this->soldiers = _soldiers;
		this->adj = _adj;

		dfs();
	}

	void dfs() {
		visited.assign(soldiers.size(), false);
		dfs(0, true);
	}

	void dfs(int u, bool is_side_a) {
		if (visited[u]) return;
		if (is_side_a) {
			a.push_back(u);
		} else {
			b.push_back(u);
		}
		visited[u] = true;

		for (auto &v : adj[u]) {
			dfs(v, !is_side_a);
		}
	}

	void sum() {
		lll sum_a = 0, sum_b = 0;
		for (auto &x : a) {
			sum_a += soldiers[x];
		}
		for (auto &x : b) {
			sum_b += soldiers[x];
		}
		DEB cout << "Sums: " << sum_a << " " << sum_b << endl;
		DEB cout << "a: " << endl;
		DEB for (auto &x : a) {
			cout << x << " ";
		}
		DEB cout << endl;
		DEB cout << "b: " << endl;
		DEB for (auto &x : b) {
			cout << x << " ";
		}
		DEB cout << endl;
		if (sum_a == sum_b) {
			cout << 0 << endl;
			return;
		}
		if (sum_a > sum_b) {
			sort(a.begin(), a.end());
			cout << sum_a - sum_b << endl;
			reps(i, (int) a.size()) {
				cout << a[i] + 1 << " ";
			}
		} else {
			sort(b.begin(), b.end());
			cout << sum_b - sum_a << endl;
			reps(i, (int) b.size()) {
				cout << b[i] + 1 << " ";
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	int n, m;
	cin >> n >> m;
	DEB cout << "n: " << n << endl;

	vector<vector<int>> adj(n);
	vector<lll> soldiers(n);

	repi(i, n) {
		cin >> soldiers[i];
	}

	repi(i, m) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	Kingdoms king(soldiers, adj);
	king.sum();

	return 0;
}
