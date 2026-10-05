class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        
        int n=nums.size();
        int left=0;
        int sum=0;

        for(int i=0;i<k;i++)
        {
          sum=sum+nums[i];
        }
         
        int max_sum=sum;

        for(int i=k;i<n;i++)
        {
        sum=sum-nums[left];
        sum=sum+nums[i];
        left++;

        max_sum=max(max_sum,sum);
        }

        return (double)max_sum/k;
    }
};