class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        
        unordered_set<int> st;
        int n=nums.size();

        for(int i=0;i<n;i++)
        {
            if(st.find(nums[i])!=st.end())
            return true;

            st.insert(nums[i]);
            
            if(i>=k)
            {
                st.erase(nums[i-k]);
            }
        }
        return false;
    }
};