class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<int> tin(n), tout(n), depth(n);
        vector<vector<int>> up(LOG, vector<int>(n));
        int timer = 0;

        function<void(int, int)> dfs = [&](int u, int p) {
            tin[u] = timer++;
            up[0][u] = p;

            for (int j = 1; j < LOG; j++)
                up[j][u] = up[j - 1][up[j - 1][u]];

            for (int v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }

            tout[u] = timer;
        };

        dfs(0, 0);

        vector<int> bit(n + 1, 0);

        auto add = [&](int i, int val) {
            for (++i; i <= n; i += i & -i)
                bit[i] ^= val;
        };

        auto get = [&](int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res ^= bit[i];
            return res;
        };

        auto rangeXor = [&](int l, int r, int val) {
            add(l, val);
            if (r < n) add(r, val);
        };

        for (int u = 0; u < n; u++)
            rangeXor(tin[u], tout[u], 1 << (s[u] - 'a'));

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int d = depth[u] - depth[v];

            for (int j = LOG - 1; j >= 0; j--)
                if (d & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        vector<bool> ans;

        for (auto& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                rangeXor(tin[u], tout[u], delta);
                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);
                int x = get(tin[u] + 1);
                int y = get(tin[v] + 1);

                int mask = x ^ y ^ (1 << (s[w] - 'a'));
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};