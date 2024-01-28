
#pragma once

#include "std.h"

const lll INF = 1e11 + 7;

struct edge {
	lll from, to;
	lll flow, cap, cost;
	edge* twin;

	bool is_backedge;

	inline lll residual_capacity() const {
		return cap - flow;
	}
};

typedef vector<vector<edge*>> graph;

lll compute_cost(graph &g) {
	lll cost = 0;
	for (auto &v : g) {
		for (auto &e : v) {
			if (e->flow > 0) {
				cost += ((lll) e->flow) * ((lll) e->cost);
			}
		}
	}
	return cost;
}

lll compute_cost_half(graph &g) {
	lll cost = 0;
	for (auto& row : g)
		for (auto e : row)
			cost += e->flow * e->cost;
	return cost / 2;
}

edge* get_edge(graph &adj, lll from, lll to) {
	for (auto &e : adj[from]) {
		if (e->to == to) {
			return e;
		}
	}
	return nullptr;
}

enum class Algorithm {
	Directed,
	Undirected,
};

void prll_edge_flows(graph &adj) {
	cout << "Flows:" << endl;
	for (auto &v : adj) {
		for (auto &e : v) {
			if (e->flow > 0)
				cout << e->from << " " << e->to << " " << e->flow << endl;
		}
	}
}

void prll_edge_flows_zero(graph &adj) {
	cout << "Flows:" << endl;
	for (auto &v : adj) {
		for (auto &e : v) {
			if (e->cap > 0 || e->flow >= 0)
				cout << e->from << " " << e->to << " flow=" << e->flow << " cap=" << e->cap << " cost=" << e->cost << endl;
		}
	}
}

void prll_edge_flows_zero2(graph &adj) {
	cout << "Flows:" << endl;
	for (auto &v : adj) {
		for (auto &e : v) {
			if (e->flow != 0 && !e->is_backedge)
				cout << e->from << " " << e->to << " flow=" << e->flow << " cap=" << e->cap << " cost=" << e->cost << endl;
		}
	}
}

void prll_edge_flows_zero3(graph &adj) {
	cout << "Flows:" << endl;
	for (auto &v : adj) {
		for (auto &e : v) {
			if (!e->is_backedge)
				cout << e->from << " " << e->to << " flow=" << e->flow << " cap=" << e->cap << " cost=" << e->cost << endl;
		}
	}
}

void prll_edge_flows2(graph &adj, vector<vector<lll>> &flow) {
	cout << "Flows:" << endl;

	for (auto &v : adj)
	{
		for (auto &e : v) {
			if (flow[e->from][e->to] > 0)
				cout << e->from << " " << e->to << " " << flow[e->from][e->to] << endl;
		}
	}
}

void prll_vector(vector<lll> &v) {
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}

class FlowGraphReader {
	lll n;
	Algorithm algo;

public:
	// resize me pls
	vector<vector<edge*>> adj;

private:
	vector<lll> next;
	vector<lll> dist;

public:
	FlowGraphReader(lll _n, Algorithm _algo) : n(_n) {
		adj.resize(n);
		this->algo = _algo;
	}

	void add_edge(lll a, lll b, lll cap, lll cost = 0, lll flow = 0)
	{
		DEB2 cout << "Adding edge: " << a << " to " << b << " cap: " << cap << " cost: " << cost << " flow: " << flow << endl;
		edge *ab;
		edge *ba;
		ab = new edge{a, b, flow, cap, cost, nullptr, false};
		if (algo == Algorithm::Undirected) {
			ba = new edge{b, a, -flow, cap, -cost, nullptr, true};
		} else if (algo == Algorithm::Directed) {
			ba = new edge{b, a, -flow, 0, -cost, nullptr, true};
		} else {
			cerr << "Invalid algorithm" << endl;
			exit(1);
		}
		ab->twin = ba;
		ba->twin = ab;
		adj[a].push_back(ab);
		adj[b].push_back(ba);
	}
};

class EdmondsKarpMaxFlow {
public:
	lll n;
	// resize me pls
	vector<vector<edge*>> adj;
	Algorithm algo;

	EdmondsKarpMaxFlow(lll _n, Algorithm _algo) : n(_n) {
		adj.resize(n);
		this->algo = _algo;
	}

	void add_edge(lll a, lll b, lll cap, lll cost = -1)
	{
		edge *ab;
		edge *ba;
		ab = new edge{a, b, 0, cap, cost, nullptr, false};
		if (algo == Algorithm::Undirected) {
			ba = new edge{b, a, 0, cap, -cost, nullptr, true};
		} else if (algo == Algorithm::Directed) {
			ba = new edge{b, a, 0, 0, -cost, nullptr, true};
		} else {
			cerr << "Invalid algorithm" << endl;
			exit(1);
		}
		// 	uncomment to make it directed
		ab->twin = ba;
		ba->twin = ab;
		adj[a].push_back(ab);
		adj[b].push_back(ba);
	}

	lll flow(lll s, lll t) {
		lll flow = 0;
		while (true) {
			vector<edge *> inc(n, nullptr);
			queue<lll> q{{s}};
			while (!q.empty()) {
				lll x = q.front();
				q.pop();
				for (auto e : adj[x]) {
					if (e->cap > e->flow && inc[e->to] == nullptr) {
						inc[e->to] = e;
						q.push(e->to);
					}
				}
			}
			if (inc[t] == nullptr) break;
			lll aug = INF;
			for (lll v = t; v != s; v = inc[v]->from) {
				aug = min(aug, inc[v]->residual_capacity());
			}
			flow += aug;
			for (lll v = t; v != s; v = inc[v]->from)
			{
				inc[v]->flow += aug;
				inc[v]->twin->flow -= aug;
			}
		}
		return flow;
	}
};

class Dinic {
	lll n;
	lll s, t;
	Algorithm algo;

public:
	// resize me pls
	vector<vector<edge*>> adj;

private:
	vector<lll> next;
	vector<lll> dist;

public:
	Dinic(lll _n, Algorithm _algo) : n(_n) {
		adj.resize(n);
		this->algo = _algo;
	}

	Dinic(graph &&_adj) : adj(std::move(_adj)) {
		n = (lll) adj.size();
	}

	void add_edge(lll a, lll b, lll cap, lll cost = -1)
	{
		edge *ab;
		edge *ba;
		ab = new edge{a, b, 0, cap, cost, nullptr, false};
		if (algo == Algorithm::Undirected) {
			ba = new edge{b, a, 0, cap, -cost, nullptr, true};
		} else if (algo == Algorithm::Directed) {
			ba = new edge{b, a, 0, 0, -cost, nullptr, true};
		} else {
			cerr << "Invalid algorithm" << endl;
			exit(1);
		}
		ab->twin = ba;
		ba->twin = ab;
		adj[a].push_back(ab);
		adj[b].push_back(ba);
	}

	lll dfs(lll v, lll aug) {
		if (v == t) return aug;
		for (lll& i = next[v]; i < (lll) adj[v].size(); ++i) {
			auto e = adj[v][i];
			if (e->flow == e->cap) continue;
			if (dist[e->to] != dist[v] + 1) continue;
			lll pushed = dfs(e->to,
				min(aug, e->cap - e->flow));
			if (pushed == 0) continue;
			e->flow += pushed;
			e->twin->flow -= pushed;
			return pushed;
		}
		return 0;
	}

	lll flow(lll _s, lll _t)
	{
		DEB cout << "Dinic flow s: " << _s << " t: " << _t << endl;
		s = _s;
		t = _t;
		lll flow = 0;
		while (true) {
			// create layered network
			dist.assign(n, -1);
			queue<lll> q{{s}};
			dist[s] = 0;
			while (!q.empty()) {
				lll x = q.front();
				q.pop();
				for (auto e : adj[x]) {
					if (e->cap > e->flow && dist[e->to] == -1) {
						dist[e->to] = dist[x] + 1;
						q.push(e->to);
					}
				}
			}
			if (dist[t] == -1) break;
			next.assign(n, 0);
			// while s-t path in L
    		// 		augment path
			while (lll aug = dfs(s, INF)) flow += aug;
		}
		DEB cout << "Dinic flow done: " << flow << endl;
		return flow;
	}
};




// Check negative cycle
bool bellman_ford_check_negative_cost_cycle(graph &G, lll source) {
	lll V = (lll) G.size();
	lll dist[V];
	fill(dist, dist + V, INF);
	dist[source] = 0;

	repi(i, V - 1) {
		reps(u, G.size()) {
			for (const auto &edge : (G[u])) {
				if (dist[u] + edge->cost < dist[edge->to])
				{
					dist[edge->to] = dist[u] + edge->cost;
				}
			}
		}
	}
	reps(u, G.size()) {
		for (auto &edge : G[u]) {
			if (dist[u] + edge->cost < dist[edge->to]) {
				return true;
			}
		}
	}
	return false;
}

class SSP {
	vector<lll> dist;
	vector<edge*> prev;
	vector<bool> in_queue;

public:
	graph adj;
	lll n;

public:
	SSP(graph&& _adj) : adj(std::move(_adj)), n((lll) adj.size()) {
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
				lll newDist = dist[v] + edge->cost;

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
			lll f = K - flow;
			lll cur = t;
			while (cur != s) {
				f = std::min(f, prev[cur]->cap);
				cur = prev[cur]->from;
			}

			// apply flow
			flow += f;
			cost += ((lll) f) * ((lll) dist[t]);
			cur = t;
			while (cur != s) {
				prev[cur]->cap -= f;
				prev[cur]->flow += f;
				prev[cur]->twin->cap += f;
				prev[cur]->twin->flow -= f;
				cur = prev[cur]->from;
			}
		}
		return pair<ll, ll>(cost, flow);
	}
};

class FlowDecomposition {
public:
	lll n;
	// resize me pls
	vector<vector<edge*>> adj;

private:
	vector<vector<lll>> flow;  // Flow matrix
	vector<lll> next_edge;   // Stores the index of the next edge with positive flow
	std::vector<bool> in_path;

public:
	FlowDecomposition(FlowGraphReader &g) :
		FlowDecomposition(std::move(g.adj)) {}

	FlowDecomposition(graph &&_adj) {
		n = (lll) _adj.size();
		adj = std::move(_adj);
		flow.assign(n, vector<lll>(n, 0));
	}

private:
	void initialize_next_edge(lll _n) {
		next_edge.assign(_n, 0);
		repi(i, n) {
			for (auto &e : adj[i]) {
				if (e->flow > 0)
					flow[e->from][e->to] = e->flow;
			}
		}
	}

	void update_next_edge(lll from) {
		while (next_edge[from] < (lll) adj[from].size() && flow[from][adj[from][next_edge[from]]->to] <= 0) {
			DEB cout << "Skipping source edge due to no flow: " << from << " to " << adj[from][next_edge[from]]->to << endl;
			next_edge[from]++;
		}
	}

	void remove_cycle(lll node, vector<lll>& stack) {
		lll min_flow = INF;
		lll i;
		stack.push_back(node);
		for (i = (lll)stack.size() - 2; i >= 0; i--)
		{
			min_flow = std::min(min_flow, flow[stack[i]][stack[i + 1]]);
			if (stack[i] == node) break;
		}
		DEB cout << "Reducing cycle flow: " << min_flow << endl;
		DEB cout << "Stack: ";
		DEB prll_path(stack);
		for (i = (lll)stack.size() - 2; i >= 0; i--)
		{
			DEB cout << "Reducing cycle flow from " << stack[i] + 1 << " to " << stack[i + 1] + 1 << " by " << min_flow << " to " << flow[stack[i]][stack[i + 1]] - min_flow << endl;
			flow[stack[i]][stack[i + 1]] -= min_flow;
			if (stack[i] == node) break;
		}
		stack.pop_back();
	}

	vector<lll> find_st_path(lll s, lll t) {
		vector<lll> path;

		lll cycle_node = -1;
		in_path.assign(n, false);
		function<bool(lll)> dfs = [&](lll node)
		{
			in_path[node] = true;
			path.push_back(node);
			if (node == t)
			{
				return true;
			}

			// Problem i++ also changes next_edge when arriving again
			// at the same node.
			//
			// So.. reset counter when arriving at cycle? No, just remove cycle and go back.
			for (lll &i = next_edge[node]; i < (lll)adj[node].size() && (cycle_node == -1 || cycle_node == node); ++i)
			{
				DEB cout << "Checking edge: " << node << " to " << adj[node][i]->to << endl;
				// if (node == cycle_node) {
				// 	// DEB cout << "Returning back due to cycle: " << node << " to " << adj[node][i]->to << endl;
				// 	DEB cout << "Returned back to initial node deu to cycle: " << node << endl;
				// 	cycle_node = -1;
				// }
				lll to = adj[node][i]->to;
				if (flow[node][to] < 0) {
					DEB cout << "Skipping edge due to negative flow: " << node << " to " << to << endl;
					continue;
				}
				if (flow[node][to] == 0) {
					DEB cout << "Skipping edge due to no flow: " << node << " to " << to << endl;
					continue;
				}
				if (in_path[to]) {
					DEB cout << "Cycle detected: " << node << " to " << to << endl;
					remove_cycle(to, path);
					// Stop alll because we want to go back to where the cycle started.
					cycle_node = to;
					continue;
				}
				if (!dfs(to)) {
					if (node == cycle_node) {
						i--;
						cycle_node = -1;
						continue;
					}
					else if (cycle_node != -1) {
						next_edge[node] = max((lll) 0, next_edge[node] - 1);
						DEB cout << "Returning back due to cycle: " << node << " to " << to << endl;
						break;
					}
					DEB cout << "Skipping edge due to dfs not found: " << node << " to " << to << endl;
					continue;
				}
				
				return true;
			}
			DEB cout << "Exiting node: " << node << endl;
			in_path[node] = false;
			path.pop_back();
			return false;
		};
		dfs(s);
		// reverse(path.begin(), path.end());
		DEB cout << "Found path from " << s << " to " << t << ": ";
		DEB prll_path(path);
		return path;
	}

	void prll_path(vector<lll>& path) {
		cout << "size: " << path.size() << " - ";
		for (lll state : path) {
			cout << state + 1 << " ";
		}
		cout << endl;
	}

public:
	using process_path = function<void(vector<lll>&, ll)>;

	lll decompose_flow(lll s, lll t, process_path _process_path) {
		initialize_next_edge(n);
		lll number_of_paths = 0;
		while (true)
		{
			update_next_edge(s);
			if (next_edge[s] == (lll) adj[s].size()) break;  // No more paths

			auto path = find_st_path(s, t);
			if (path.empty()) break;  // No path found

			lll min_flow = INF;
			reps(i, path.size() - 1) {
				min_flow = std::min(min_flow, flow[path[i]][path[i + 1]]);
			}
			// Remove flow from path.
			reps(i, path.size() - 1) {
				DEB cout << "Reducing flow from " << path[i] + 1 << " to " << path[i + 1] + 1 << " by " << min_flow << " to " << flow[path[i]][path[i + 1]] - min_flow << endl;
				flow[path[i]][path[i + 1]] -= min_flow;
			}
			_process_path(path, min_flow);
			number_of_paths++;
			DEB prll_edge_flows2(adj, flow);
		}
		return number_of_paths;
	}
};

class FlowDecompositionStored {
public:
	lll path_count;
	vector<vector<lll>> paths;
	vector<lll> path_flows;

private:
	FlowDecomposition fd;

public:
	FlowDecompositionStored(FlowGraphReader &g) : fd(g) {
		path_count = 0;
	}

	FlowDecompositionStored(graph &&_adj) : fd(std::move(_adj)) {
		path_count = 0;
	}

	void decompose(lll s, lll t) {
		path_count = fd.decompose_flow(s, t, bind(&FlowDecompositionStored::store_path, this, _1, _2));
	}

	void store_path(vector<lll>& path, lll path_flow) {
		DEB cout << "Found path with flow " << path_flow << ": ";
		DEB for (lll state : path) {
			cout << state + 1 << " ";
		}
		DEB cout << endl;
		paths.push_back(std::move(path));
		path_flows.push_back(path_flow);
	}
};
