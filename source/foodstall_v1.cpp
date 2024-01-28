#define DEBUG2
#define DEBUG32

#include "std.h"

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> s(n), visits(n+1, 0);
	
	for(int i = 0; i < n; ++i) {
		cin >> s[i];
	}

	while(m--) {
		int l, r;
		cin >> l >> r;
		visits[l-1]++;
		visits[r]--;
	}

	for(int i = 1; i < n; ++i) {
		visits[i] += visits[i-1];
	}

	sort(s.begin(), s.end(), greater<int>());
	sort(visits.begin(), visits.end()-1, greater<int>());

	long long total_satisfaction = 0;
	for(int i = 0; i < n; ++i) {
		total_satisfaction += (long long)visits[i] * s[i];
	}

	cout << total_satisfaction << endl;
	return 0;
}
