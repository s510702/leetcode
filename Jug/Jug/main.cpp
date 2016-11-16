//
//  main.cpp
//  Jug
//
//  Created by Yang Zhao on 10/2/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <list>
#include <set>

using namespace std;

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if(z == 0) return true;
        if(x == 0 || y == 0) return (z == x+y);
        
        set<int> canMeasure;
        canMeasure.insert(0);
        list<int> workStack;
        workStack = {x, y};
        while(!workStack.empty())
        {
            int m = workStack.front(); workStack.pop_front();
            if(m < x)
            {
                int n = (x-m)%y;
                if(n == z) return true;
                auto p = canMeasure.insert(n);
                if(p.second)
                {
                    workStack.emplace_back(n);
                }
            }
            if(m+y < x)
            {
                int n = m+y;
                if(n == z) return true;
                auto p = canMeasure.insert(n);
                if(p.second)
                {
                    workStack.emplace_back(n);
                }
            }
            else if( m+y == z) return true;
            
            if(m < y)
            {
                int n = (y-m)%x;
                if(n == z) return true;
                auto p = canMeasure.insert(n);
                if(p.second)
                {
                    workStack.emplace_back(n);
                }
            }
            if(m+x < y)
            {
                int n = m+x;
                if(n == z) return true;
                auto p = canMeasure.insert(n);
                if(p.second)
                {
                    workStack.emplace_back(n);
                }
            }
            else if(m+x == z) return true;
        }
        return false;
    }
};


int main(int argc, const char * argv[]) {

    Solution solution;
    if(solution.canMeasureWater(0,2,1))
    {
        cout << "True" <<endl;
    }
    else{
        cout << "False" <<endl;
    }
    
    return 0;
}
