//
//  main.cpp
//  3Sum
//
//  Created by Yang Zhao on 9/16/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>

using namespace std;

class Solution {
    unordered_map<int, size_t> numberCountMap;
    vector<vector<int>> results;
    set<pair<int,int>> forbidden;
    void Recur(vector<int> const& picks)
    {
        if(picks.size() == 2)
        {
            int last = 0-picks[1]-picks[0];
            auto it = numberCountMap.find(last);
            if(it != numberCountMap.end() && it->second >0 )
            {
                vector<int> r = picks;
                r.push_back(last);
                results.push_back(r);
                
                forbidden.insert((r[0] <= r[1])? make_pair(r[0],r[1]):make_pair(r[1], r[0]));
                forbidden.insert((r[0] <= r[2])? make_pair(r[0],r[2]):make_pair(r[2], r[0]));
                forbidden.insert((r[1] <= r[2])? make_pair(r[1],r[2]):make_pair(r[2], r[1]));
            }
            
            numberCountMap[picks[1]]++;
        }
        else
        {
            for(auto n : numberCountMap)
            {
                if(n.second > 0)
                {
                    if(picks.size() == 1)
                    {
                        auto it = forbidden.find((picks[0]<=n.first)? make_pair(picks[0], n.first) : make_pair(n.first, picks[0]));
                        if(it != forbidden.end())
                        {
                            continue;
                        }
                    }
                    
                    vector<int> r = picks;
                    r.push_back(n.first);
                    numberCountMap[n.first]--;
                    Recur(r);
                }
            }
            if(picks.size() == 1)
            {
                numberCountMap[picks[0]]++;
            }
        }
    }
    
    void NoRecur()
    {
        for(auto& p1 : numberCountMap)
        {
            numberCountMap[p1.first]--;
            
            for(auto& p2 : numberCountMap)
            {
                if(p2.second == 0)
                {
                    continue;
                }
                
                auto fit = forbidden.find((p1.first <= p2.first)? make_pair(p1.first, p2.first) : make_pair(p2.first, p1.first));
                if(fit != forbidden.end())
                {
                    continue;
                }
                
                numberCountMap[p2.first]--;
                
                // If we can make it after made two picks.
                int last = 0-p1.first-p2.first;
                auto it = numberCountMap.find(last);
                if(it != numberCountMap.end() && it->second >0 )
                {
                    vector<int> r({p1.first, p2.first, last});
                    results.push_back(r);
                    
                    forbidden.insert((r[0] <= r[1])? make_pair(r[0],r[1]):make_pair(r[1], r[0]));
                    forbidden.insert((r[0] <= r[2])? make_pair(r[0],r[2]):make_pair(r[2], r[0]));
                    forbidden.insert((r[1] <= r[2])? make_pair(r[1],r[2]):make_pair(r[2], r[1]));
                }
                
                numberCountMap[p2.first]++;
            }
        
            numberCountMap[p1.first]++;
        }

    }
    
public:
    vector<vector<int>> threeSum(vector<int>& nums) {;
        // Initialize
        for(auto& i : nums)
        {
            numberCountMap[i]++;
        }
        
        //Recur(vector<int>());
        NoRecur();
        return results;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> nums = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    auto results = solution.threeSum(nums);
    
    for(auto res: results)
    {
        for(auto n:res)
        {
            cout<< n << ",";
        }
        cout << endl;
    }
    return 0;
}
