#define DEBUG2
#define DEBUG32

#include "std.h"
#include "std_flow.h"

lll MAXN = 0;

struct Edgee {
	lll to, capacity, originalCapacity, cost;
};

std::vector<vector<Edgee>> adj;
lll maxFlow;

bool bfs(lll s, lll t, std::vector<lll>& parent) {
	std::fill(parent.begin(), parent.end(), -1);
	std::queue<lll> q;
	q.push(s);
	parent[s] = -2;

	while (!q.empty()) {
		lll u = q.front();
		q.pop();

		for (const auto& e : adj[u]) {
			if (parent[e.to] == -1 && e.capacity > 0) {
				parent[e.to] = u;
				if (e.to == t) return true;
				q.push(e.to);
			}
		}
	}
	return false;
}

void edmondsKarp(lll s, lll t) {
	maxFlow = 0;
	std::vector<lll> parent(MAXN);

	while (bfs(s, t, parent)) {
		lll flow = INF;
		lll cur = t;
		while (cur != s) {
			lll prev = parent[cur];
			for (auto& e : adj[prev]) {
				if (e.to == cur && e.capacity > 0) {
					flow = std::min(flow, e.capacity);
					break;
				}
			}
			cur = prev;
		}

		maxFlow += flow;
		cur = t;
		while (cur != s) {
			lll prev = parent[cur];
			for (auto& e : adj[prev]) {
				if (e.to == cur && e.capacity > 0) {
					e.capacity -= flow;
					// Find the reverse edge
					for (auto& rev : adj[cur]) {
						if (rev.to == prev) {
							rev.capacity += flow;
							break;
						}
					}
					break;
				}
			}
			cur = prev;
		}
	}
}

bool checkFlow(lll s, lll t, lll desiredFlow, lll maxProduct) {
	// Reset capacities to min(originalCapacity, maxProduct / cost)
	for (lll i = 0; i < MAXN; ++i) {
		for (auto& e : adj[i]) {
			e.capacity = std::min(e.originalCapacity, maxProduct / e.cost);
		}
	}

	edmondsKarp(s, t);
	return maxFlow >= desiredFlow;
}

lll binarySearchMaxProduct(lll s, lll t, lll desiredFlow, lll maxCost) {
	lll low = 0, high = maxCost * desiredFlow;
	while (low < high) {
		lll mid = low + (high - low) / 2;
		if (checkFlow(s, t, desiredFlow, mid)) high = mid;
		else low = mid + 1;
	}
	return high;
}

void solve(lll n, lll m) {
	FlowGraphReader reader(n, Algorithm::Directed);
	lll max_cost = 0;
	repi(i, m) {
		lll a, b, cap, cost;
		cin >> a >> b >> cap >> cost;
		a--, b--;
		reader.add_edge(a, b, cap, cost);
		max_cost = max(max_cost, cost);
	}
	lll source = 0;
	lll sink = n - 1;

	// Copy dinic.adj to adj
	adj.resize(reader.adj.size());
	MAXN = reader.adj.size();
	for (size_t i = 0; i < reader.adj.size(); ++i) {
		for (const auto& e : reader.adj[i]) {
			adj[i].push_back({e->to, e->cap, e->cap, e->cost});
		}
	}

	Dinic dinic(std::move(reader.adj));
	lll desiredFlow = dinic.flow(source, sink);
	lll maxCost = max_cost * desiredFlow + 1e12;

	lll minMaxProduct = binarySearchMaxProduct(source, sink, desiredFlow, maxCost);
	DEB std::cout << "Minimum possible maximum product of flow and cost: " << minMaxProduct << std::endl;

	cout << desiredFlow << " " << minMaxProduct << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	lll t;
	cin >> t;
	DEB cout << "t: " << t << endl;

	repi(tt, t) {
		lll n, m;
		cin >> n >> m;
		DEB cout << "n: " << n << " m: " << m << endl;
		solve(n, m);
	}

	return 0;
}
