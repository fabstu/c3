#define DEBUG2
#define DEBUG32

#include "std.h"
#include "std_flow.h"

class SSP2 {
	vector<lll> dist;
	vector<edge*> prev;
	vector<bool> in_queue;

public:
	graph adj;
	lll n;

public:
	SSP2(graph&& _adj) : adj(std::move(_adj)), n((ll) adj.size()) {
		DEB cout << "SPFA constructor n: " << n << " adj.size(): " << adj.size() << endl;
	}

private:
	void bellman_ford(lll source) {
		DEB cout << "SPFA bellman_ford source: " << source << " n: " << n << endl;
		dist.assign(n, INF);
		prev.assign(n, nullptr);
		in_queue.assign(n, false);

		queue<lll> q;
		q.push(source);
		in_queue[source] = true;
		dist[source] = 0;

		while (!q.empty()) {
			lll v = q.front();
			q.pop();
			in_queue[v] = false;
			DEB cout << "Popping " << v << endl;

			for (auto& edge : adj[v]) {
				lll nei = edge->to; // edge is v to nei
				lll newDist = max(dist[v], (edge->flow + 1) * edge->cost);

				if (edge->cap == 0) continue;

				if (newDist >= dist[nei]) {
					DEB cout << "Not reducing cost of " << nei << " from " << dist[nei] << " to " << newDist << endl;
					continue;
				}
				DEB cout << "Reducing cost of " << nei << " from " << dist[nei] << " to " << newDist << endl;
				dist[nei] = newDist; prev[nei] = edge;
				if (!in_queue[nei]) {
					DEB cout << "Pushing " << nei << endl;
					q.push(nei);
					in_queue[nei] = true;
				}
			}
		}
	}

public:
	pair<ll, ll> min_cost(lll s, lll t) {
		return min_cost(INF, s, t);
	}

	// Basis: https://cp-algorithms.com/graph/min_cost_flow.html
	pair<ll, ll> min_cost(lll K, lll s, lll t) {
		DEB cout << "SPFA flow K: " << K << " s: " << s << " t: " << t << endl;
		lll flow = 0;
		lll cost = 0;
		while (flow < K) {
			bellman_ford(s);
			if (dist[t] == INF)
				break;

			// find max flow on that path
			lll f = 1;
			// lll cur = t;
			// while (cur != s) {
			// 	f = std::min(f, prev[cur]->cap);
			// 	cur = prev[cur]->from;
			// }

			// apply flow
			flow += f;
			// cost = max(cost, ((ll) f) * ((ll) dist[t]));
			lll cur = t;
			while (cur != s) {
				prev[cur]->cap -= f;
				prev[cur]->flow += f;
				prev[cur]->twin->cap += f;
				prev[cur]->twin->flow -= f;
				cur = prev[cur]->from;
			}
		}

		repi(u, n) {
			for (auto& edge : adj[u]) {
				if (edge->flow > 0) {
					cost = max(cost, ((lll) edge->flow) * ((lll) edge->cost));
				}
			}
		}

		return pair<ll, ll>(cost, flow);
	}
};

void solve(lll n, lll m) {
	FlowGraphReader reader(n, Algorithm::Directed);
	repi(i, m) {
		lll a, b, cap, cost;
		cin >> a >> b >> cap >> cost;
		a--, b--;
		reader.add_edge(a, b, cap, cost);
	}
	SSP2 ssp(std::move(reader.adj));
	lll source = 0;
	lll sink = n - 1;
	auto [additional_cost, flow] = ssp.min_cost(source, sink);
	cout << flow << " " << additional_cost << endl;
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
