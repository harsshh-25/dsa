class Solution {
public:
    int maxVowels(string s, int k) {
        
        int n=s.size();
        int count=0;
        int left=0;

        for(int i=0;i<k;i++)
        {
           if(s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u')
           count++;
        }
        int max_vowel=count;

        for(int i=k;i<n;i++)
        {
           if(s[left]=='a' || s[left]=='e' || s[left]=='i' || s[left]=='o' || s[left]=='u')
           {
            count--;
           }
           if(s[i]=='a' || s[i]=='e' || s[i]=='i' || s[i]=='o' || s[i]=='u')
           {
            count++;
           }
           left++;

           max_vowel=max(max_vowel,count);
        }
        return max_vowel;
    }
};