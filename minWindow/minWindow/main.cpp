//
//  main.cpp
//  minWindow
//
//  Created by Yang Zhao on 8/25/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
    string s_;
public:
    void GenerateTargetSet(string const& t, map<char, int>& targetSet)
    {
        for(int i = 0; i<t.length(); i++)
        {
            targetSet[t[i]]++;
        }
    }
    
    void GenerateCompactStringIndices(string const& s, map<char, int> const& target, vector<size_t>& indices)
    {
        for(size_t i = 0; i< s.length(); i++)
        {
            if(target.find(s[i]) != target.end())
            {
                indices.emplace_back(i);
            }
        }
    }
    
    bool GenerateWindowIndices(vector<size_t> const& indices, map<char, int> const& target, size_t& start_idx, size_t& end_idx)
    {
        map<char, int> window_content;
        char missing_char = target.begin()->first;
        
        size_t win_start = 0; // this is the indexi of indices array
        char win_start_char = s_[indices[win_start]];
        
        
        size_t best_win_start = 0;
        size_t best_win_end = 0;
        size_t best_win_size = 0;
        
        bool get_window = false;
        
        int i = 0;
        for(size_t idx : indices)
        {
            char c =s_[idx];
            ++window_content[c];
            
            // see if we can furthur shrink the window
            if(c == win_start_char && i>0)
            {
                bool done = false;
                while(!done)
                {
                    char s = s_[indices[win_start]];
                    auto it = target.find(s);
                    if (it==target.end()) throw;
                    
                    if(window_content[s] > it->second)
                    {
                        win_start++;
                        window_content[s]--;
                    }
                    else
                    {
                        // this char can not be removed from window now, stop shrinking.
                        done = true;
                    }
                }
                win_start_char = s_[indices[win_start]];
            }
            
            if(!get_window)
            {
                // If we have not yet get window, check here
                if(missing_char == c)
                {
                    bool getit = true;
                    for(auto const& p : target)
                    {
                        auto it = window_content.find(p.first);
                        if (it==window_content.end() || it->second < p.second)
                        {
                            getit = false;
                            missing_char = p.first;
                            break;
                        }
                    }
                    
                    if(getit)
                    {
                        get_window = true;
                        best_win_size = idx - indices[win_start];
                        best_win_start = win_start;
                        best_win_end = i;
                    }
                }
                // if not we are still missing c
            }
            else
            {
                // Here we only care whether it is the best one.
                if(best_win_size > idx - indices[win_start])
                {
                    best_win_size = idx - indices[win_start];
                    best_win_start = win_start;
                    best_win_end = i;
                }
                
            }
            
            ++i;
        }
        
        if(get_window)
        {
            start_idx = indices[best_win_start];
            end_idx = indices[best_win_end];
        }
        
        return get_window;
    }
    
    string minWindow(string s, string t) {
        s_ = s;
        
        string result;
        map<char, int> targetT;
        vector<size_t> indices;
        
        GenerateTargetSet(t, targetT);
        
        GenerateCompactStringIndices(s, targetT, indices);
        
        if(indices.size() == 0) return result;
        
        size_t start_idx, end_idx;
        if(GenerateWindowIndices(indices, targetT, start_idx, end_idx))
        {
            result = s.substr(start_idx, end_idx-start_idx+1);
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    string res = solution.minWindow("a","b");
    std::cout << res << endl;
    return 0;
}
