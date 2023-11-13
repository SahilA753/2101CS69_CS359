#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
const int N = 1e3 + 5;
#define int long long
vector<pair<int, int>> g[N];
int dist[N][N];
int pre[N][N];
int tot;
vector<thread> th;
mutex mtx;

map<string, int> mapping;
map<int, string> reverse_mapping;
void fun(int n)
{
    // std::this_thread::sleep_for(chrono::seconds(2));
    set<pair<int, int>> s;
    for (int i = 1; i <= tot; i++)
    {
        if (i != n)
            s.insert({dist[n][i], i});
    }
    while (s.size())
    {
        int node = s.begin()->second;
        int dist1 = s.begin()->first;
        s.erase(s.begin());
        for (auto p1 : g[node])
        {
            int child = p1.first;
            int w = p1.second;
            if (dist1 + w < dist[n][child])
            {
                mtx.lock();
                s.erase({dist[n][child], child});
                dist[n][child] = dist1 + w;
                s.insert({dist[n][child], child});
                pre[n][child] = node;
                mtx.unlock();
            }
        }
    }
    map<int, int> m;
    m[n] = 1;
    for (auto child : g[n])
    {
        m[child.first] = 1;
    }
    for (int i = 1; i <= tot; i++)
    {
        int val = pre[n][i];
        int ct = 0;
        while (pre[n][val] != val && ct <= tot)
        {
            val = pre[n][val];
            ct++;
        }
        mtx.lock();
        pre[n][i] = val;
        mtx.unlock();
    }
    cout << "Distance vector of node " << reverse_mapping[n] << " is : \n";
    cout << "Node"
         << "\t|"
         << "Dist"
         << "\t|"
         << "Next Hop" << endl;
    for (int j = 1; j <= tot; j++)
    {
        cout << reverse_mapping[j] << "\t|" << dist[n][j] << "\t|" << reverse_mapping[pre[n][j]] << endl;
    }
    cout << endl;
}
void dfs(int node, vector<int> vis)
{
    vis[node] = 1;
    for (auto child : g[node])
    {
        if (!vis[child.first])
        {
            dfs(child.first, vis);
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    tot = n;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        mapping[s] = i;
        reverse_mapping[i] = s;
    }
    int edges = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dist[i][j] = INT_MAX;
            pre[i][j] = 0;
        }
        dist[i][i] = 0;
        pre[i][i] = i;
    }
    while (1)
    {
        string s;
        cin >> s;
        if (s == "END")
        {
            break;
        }
        edges++;
        string t;
        cin >> t;
        int w;
        cin >> w;
        int u = mapping[s];
        int v = mapping[t];
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        dist[u][v] = w;
        dist[v][u] = w;
        pre[u][v] = v;
        pre[v][u] = u;
    }
    vector<int> vis(n + 1, 0);
    dfs(1, vis);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            cout << "Graph is not connected" << endl;
            return;
        }
    }
    th.resize(n);

    for (int i = 1; i <= n; i++)
    {
        sleep(2);
        th[i - 1] = thread(fun, i);
    }
    for (int i = 0; i < n; i++)
    {
        th[i].join();
    }
}
signed main()
{
    freopen("topology.txt", "r", stdin);
    solve();
    return 0;
}