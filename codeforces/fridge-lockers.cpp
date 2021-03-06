// template-cpp-algor
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <climits>
#include <cstring>
#include <cctype>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

// type
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
// shortcuts
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define pii pair<int, int>
#define vpii vector<pii>
#define pb push_back
#define pf push_front
#define mp make_pair
#define F first
#define S second
#define R first
#define C second
#define X first
#define Y second
#define INIT_RANDOM_SEED srand(time(0));
// print
template<typename T, typename... Types>
void print_with_space(T t, Types... ts) {
    cout << t << " ";
}
template<typename T, typename... Args>
void DEBUG(T t, Args... args) {
    cout << "DEBUG: " << t << " "; print_with_space(args...); cout << endl;
}

int fact(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++)
        res = res * i;
    return res;
}

int nCr(int n, int r) {
    return fact(n) / (fact(r) * fact(n - r));
}

/* CODE START BELOW THIS POINT!!! */
void test_case(int t) {
    int n, m; cin >> n >> m;
    int cost = 0;
    for (int i = 0; i < n; ++i) {
        int c; cin >> c;
        cost += (2 * c);
    }
    if (m < n || n <= 2) {
        cout << -1 << endl;
        return;
    }
    cout << cost << endl;
    for (int i = 1; i <= (n-1); ++i) {
        cout << i << " " << i + 1 << endl;
    }
    cout << n << " " << 1 << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        test_case(t);
    }
    return 0;
}
