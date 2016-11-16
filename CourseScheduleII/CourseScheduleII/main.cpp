//
//  main.cpp
//  CourseScheduleII
//
//  Created by Yang Zhao on 9/22/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>

#include <set>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> result;
        
        map<int, size_t> preReqsNum;
        multimap<int, int> enableCourse;
        set<int> noMoreReq;
        
        for(int i = 0; i<numCourses; i++)
        {
            noMoreReq.insert(i);
        }
        
        for (auto& p : prerequisites)
        {
            enableCourse.emplace(p.second, p.first);
            preReqsNum[p.first]++;
            noMoreReq.erase(p.first);
        }
        
        bool done = false;
        while(!done)
        {
            set<int> newEnabledCourses;
            for(auto c : noMoreReq)
            {
                result.push_back(c);
                auto pr = enableCourse.equal_range(c);
                for(auto it = pr.first; it != pr.second; it++)
                {
                    if(--preReqsNum[it->second] == 0)
                    {
                        newEnabledCourses.insert(it->second);
                        preReqsNum.erase(it->second);
                    }
                }
            }
            if(newEnabledCourses.size() == 0)
            {
                done = true;
            }
            else
            {
                noMoreReq = std::move(newEnabledCourses);
            }
        }
        
        if(preReqsNum.size() != 0)
        {
            return vector<int>();
        }
        else
        {
            return result;
        }
    }
};

int main(int argc, const char * argv[]) {

    Solution solution;
    vector<pair<int, int>> coursePairs;
    coursePairs.push_back(make_pair(1,0));
    coursePairs.push_back(make_pair(2,0));
    coursePairs.push_back(make_pair(3,1));
    coursePairs.push_back(make_pair(3,2));
    auto result = solution.findOrder(4, coursePairs);
    for(auto r : result)
    {
        cout << r << " ";
    }
    
    return 0;
}
