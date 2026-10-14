class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        string ans = "";

        if(sum > num * 9)
            return "";

        for(int i = 0; i < num; i++) {
            if(sum >= 9) {
                ans += '9';
                sum -= 9;
            }
            else {
                ans += char('0' + sum);
                sum = 0;
            }
        }

        return ans;
    }
};