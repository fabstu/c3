#pragma once

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
