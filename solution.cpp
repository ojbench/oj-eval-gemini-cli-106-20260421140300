#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int sz[MAXN];
int parent[MAXN];
int n, k;
vector<int> results;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> order;
    stack<int> s;
    s.push(1);
    parent[1] = 0;
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                s.push(v);
            }
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                sz[u] += sz[v];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        int u = order[i];
        bool ok = true;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                if (sz[v] > k) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok && n - sz[u] > k) {
            ok = false;
        }
        if (ok) {
            results.push_back(u);
        }
    }

    if (results.empty()) {
        cout << "None" << endl;
    } else {
        sort(results.rbegin(), results.rend());
        for (int i = 0; i < results.size(); ++i) {
            cout << results[i] << (i == results.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}