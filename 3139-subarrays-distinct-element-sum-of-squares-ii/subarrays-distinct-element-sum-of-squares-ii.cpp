
class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum, sqSum, lazy;
    };

    vector<Node> seg;
    int n;

    void build(int idx, int l, int r) {
        seg[idx] = {0, 0, 0};

        if (l == r) return;

        int mid = (l + r) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
    }

    void apply(int idx, int l, int r, long long val) {
        long long len = r - l + 1;

        seg[idx].sqSum = (
            seg[idx].sqSum
            + 2LL * val % MOD * seg[idx].sum % MOD
            + len % MOD * val % MOD * val % MOD
        ) % MOD;

        seg[idx].sum = (seg[idx].sum + len * val) % MOD;
        seg[idx].lazy = (seg[idx].lazy + val) % MOD;
    }

    void push(int idx, int l, int r) {
        if (seg[idx].lazy == 0 || l == r) return;

        int mid = (l + r) / 2;

        apply(idx * 2, l, mid, seg[idx].lazy);
        apply(idx * 2 + 1, mid + 1, r, seg[idx].lazy);

        seg[idx].lazy = 0;
    }

    void update(int idx, int l, int r,
                int ql, int qr, long long val) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(idx, l, r, val);
            return;
        }

        push(idx, l, r);

        int mid = (l + r) / 2;

        update(idx * 2, l, mid, ql, qr, val);
        update(idx * 2 + 1, mid + 1, r, ql, qr, val);

        seg[idx].sum =
            (seg[idx * 2].sum + seg[idx * 2 + 1].sum) % MOD;

        seg[idx].sqSum =
            (seg[idx * 2].sqSum + seg[idx * 2 + 1].sqSum) % MOD;
    }

    // Query the sum of squares in range [ql, qr]
    long long query(int idx, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;

        if (ql <= l && r <= qr) {
            return seg[idx].sqSum;
        }

        push(idx, l, r);

        int mid = (l + r) / 2;

        long long left = query(idx * 2, l, mid, ql, qr);
        long long right = query(idx * 2 + 1, mid + 1, r, ql, qr);

        return (left + right) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        seg.resize(4 * n);

        build(1, 0, n - 1);

        unordered_map<int, int> last;
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int prev = -1;

            if (last.count(nums[i])) {
                prev = last[nums[i]];
            }

            update(1, 0, n - 1, prev + 1, i, 1);

            // Sum squares for ALL subarrays ending at i
            ans = (ans + query(1, 0, n - 1, 0, i)) % MOD;

            last[nums[i]] = i;
        }

        return ans;
    }
};
