
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = (long long)k1 + k2;
        int n = nums1.size();

        vector<long long> diff(n);
        long long total = 0, mx = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
            mx = max(mx, diff[i]);
        }

        if (total <= k) return 0;

        long long lo = 0, hi = mx;

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            long long need = 0;

            for (long long d : diff) {
                if (d > mid) need += d - mid;
                if (need > k) break;
            }

            if (need <= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        long long ans = 0, used = 0;

        for (long long d : diff) {
            if (d > lo) {
                used += d - lo;
                d = lo;
            }
            ans += d * d;
        }

        long long rem = k - used;

        // Reduce rem elements from lo to lo - 1.
        // Only elements originally above lo can be reduced further.
        for (long long d : diff) {
            (void)d;
        }

        // Reconstruct the answer directly from the threshold.
        ans = 0;
        for (long long d : diff) {
            long long x = min(d, lo);
            ans += x * x;
        }

        // Need = sum(max(0, diff[i] - lo)).
        // Remaining operations reduce some values equal to lo.
        for (long long d : diff) {
            if (d >= lo && rem > 0 && lo > 0) {
                ans -= 2 * lo - 1;
                rem--;
            }
        }

        return ans;
    }
};
