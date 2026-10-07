class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;
        unordered_set<string> visited;

        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while(!q.empty())
        {
            string current = q.front();
            q.pop();

            int balance = 0;
            bool valid = true;

            for(int i = 0; i < current.size(); i++)
            {
                if(current[i] == '(')
                {
                    balance++;
                }
                else if(current[i] == ')')
                {
                    balance--;

                    if(balance < 0)
                    {
                        valid = false;
                        break;
                    }
                }
            }

            if(balance != 0)
                valid = false;

            if(valid)
            {
                ans.push_back(current);
                found = true;
            }
            if(found)
                continue;

            for(int i = 0; i < current.size(); i++)
            {
                if(current[i] != '(' && current[i] != ')')
                    continue;

                string next = current.substr(0, i) +
                              current.substr(i + 1);

                if(visited.find(next) == visited.end())
                {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};