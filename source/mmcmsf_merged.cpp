
#include <bits/stdc++.h>
#include <cmath>
#include <limits.h>
#include <algorithm>
#include <chrono>

using namespace std::chrono;
using namespace std::placeholders;

using ll = long long;
using lll = __int128;
#define vi vector<int>
#define vil             vector<ll >
#define pb              push_back
#define fi              first
#define sc              second
#define pii             pair<int , int >

#define rep(a, b)   for(ll a = 0; a < (b); ++a)
#define repi(a, b)   for(int a = 0; a < (b); ++a)
#define repl(a, b)   for(ll a = 0; a < (b); ++a)
#define reps(a, b)   for(size_t a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl2        '\n'

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight > other.weight; // For max weight
    }

	Edge() : u(-1), v(-1), weight(0) {}

	Edge& operator=(const Edge& other) {
		// Self-assignment check
		if (this == &other) {
			return *this;
		}
		u = other.u;
		v = other.v;
		weight = other.weight;
		if (u > v) {
			std::swap(u, v);
		}
		return *this; // Return a reference to the current object
	}

	Edge(const Edge& other) {
		// Self-assignment check
		if (this == &other) {
			return;
		}
		u = other.u;
		v = other.v;
		weight = other.weight;
		if (u > v) {
			std::swap(u, v);
		}
	}

	Edge(int a, int b, int w) {
		if (a > b) {
			std::swap(u, v);
		}
		u = a;
		v = b;
		weight = w;
	}

	int neighbor(ll other) const {
		return u == other ? v : u;
	}

	bool contains(int other) const {
		return u == other || v == other;
	}

	bool operator==(const Edge &other) const;
};

inline ll key(int i,int j) {
	if (i > j) {
		std::swap(i, j);
	}
	return (ll) i << 32 | (unsigned int) j;
}
inline size_t key(const Edge &e) { return key(e.u, e.v); }

bool same_edge(const Edge& e1, const Edge& e2) {
	return (e1.u == e2.u && e1.v == e2.v) || (e1.u == e2.v && e1.v == e2.u);
}

bool Edge::operator==(const Edge& other) const {
	return same_edge(*this, other);
	// return u == other.u && v == other.v && weight == other.weight;
}

using namespace std;
using Graph = vector<vector<Edge>>;
using GraphG = vector<vector<int>>;

void print_graph_bidirectional(Graph &g) {
	cout << "Graph bidirectional hiding back-edges:" << endl;
	repi(k, (int) g.size()) {
		cout << k << ": " << endl;
		for (auto &e : g[k]) {
			if (e.neighbor(k) > k)
				cout << "->" << e.neighbor(k) << endl;
		}
	}
}

void print_graph_directional(Graph &g) {
	cout << "Graph:" << endl;
	repi(k, (int) g.size()) {
		cout << k << ": " << endl;
		for (auto &e : g[k]) {
			// if (e.neighbor(k) > k)
				cout << "->" << e.neighbor(k) << endl;
		}
	}
}

void print_graph_directional(vector<vector<int>> &adj) {
	cout << "Graph:" << endl;
	repi(k, (int) adj.size()) {
		cout << k << ": " << endl;
		for (auto &e : adj[k]) {
			// if (e.neighbor(k) > k)
				cout << "->" << e << endl;
		}
	}
}

void print_graph_directional2(vector<unordered_set<int>> &adj) {
	cout << "Graph:" << endl;
	repi(k, (int) adj.size()) {
		cout << k << ": " << endl;
		for (auto &e : adj[k]) {
			// if (e.neighbor(k) > k)
				cout << "->" << e << endl;
		}
	}
}

void remove_graph_duplicates(Graph &g) {
	for (auto &node : g) {
		sort(node.begin(), node.end());
		node.erase(unique(node.begin(), node.end()), node.end());
	}
}

void remove_duplicate_edges(Graph &g) {
	for (auto &node : g) {
		sort(node.begin(), node.end(), [](const Edge &a, const Edge &b) {
			if (a.u < b.u) {
				return true;
			} else if (a.u > b.u) {
				return false;
			} else {
				return a.v < b.v;
			}
		});
	}
	for (auto &node : g) {
		node.erase(unique(node.begin(), node.end()), node.end());
	}
}

std::string int128ToString(__int128 num) {
	if (num == 0) return "0";

	bool isNegative = false;
	if (num < 0) {
		isNegative = true;
		num = -num;
	}

	std::string str;
	__int128 digit;
	const __int128 ten = static_cast<__int128>(10);
	while (num > 0)
	{
		digit = num % ten;
		str = char('0' + digit) + str;
		num /= ten;
	}

	if (isNegative) {
		str = "-" + str;
	}

	return str;
}

std::ostream& operator<<(std::ostream& os, __int128 num) {
	os << int128ToString(num);
	return os;
}

std::ostream& operator<<(std::ostream& os, array<__int128, 3> point) {
	os << "(" << point[0] << ", " << point[1] << ", " << point[2] << ")";
	return os;
}

__int128 stringToInt128(const std::string& str) {
	__int128 result = 0;
	bool isNegative = (str[0] == '-');
	size_t startIndex = isNegative ? 1 : 0;

	for (size_t i = startIndex; i < str.size(); i++) {
		if (isdigit(str[i])) {
			result = result * 10 + (str[i] - '0');
		} else {
			throw std::invalid_argument("Invalid input for __int128");
		}
	}

	return isNegative ? -result : result;
}

std::istream& operator>>(std::istream& is, __int128& num) {
	std::string str;
	is >> str;
	num = stringToInt128(str);
	return is;
}

#ifdef DEBUG
#define COUT std::cout
#define DEB 
#define DEBN if(false)
#else
#define COUT if(false) std::cout
#define DEB if(false) 
#define DEBN 
#endif

#ifdef DEBUG3
#define DEB2 
#else
#define DEB2 if(false) 
#endif

#ifdef TIME
#define DEB3
#else
#define DEB3 if(false) 
#endif



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
#define DEBUG2
#define DEBUG32


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
