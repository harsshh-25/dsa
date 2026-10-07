class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        
     int n=blocks.size();
     int count=0;
     int left=0;

     for(int i=0;i<k;i++)
     {
        if(blocks[i]=='W')
        {
            count++;
        }
     }
     int recolor=count;

     for(int i=k;i<n;i++)
     {
        if(blocks[left]== 'W')
        {
            count--;
        }
        if(blocks[i]=='W')
        {
            count++;
        }
        left++;

       recolor=min(recolor,count);
     }
     return recolor;
    }
};