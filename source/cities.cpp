#define DEBUG2
#define DEBUG32

#include "std.h"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.precision(10);

	int n;
	cin >> n;
	DEB cout << "n: " << n << endl;

	ll t;
	cin >> t;

	rep(i, t) {
		ll n, m;
		cin >> n;

		vector<ll> a(n);
		
		rep(i, n) {
			cin >> a[i];
		}

		cin >> m;

		rep(i, m) {
			ll x, y;
			cin >> x >> y;

			ll coins = 0;

			for(ll i = x; i <= y; i++) {
				if (i == 0 || a[i] - a[i-1] > a[i+1] - a[i]) {
					coins += 1;
				}
			}
		}
	}

	return 0;
}
