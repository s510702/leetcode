//
//  main.cpp
//  SpiralMatrix
//
//  Created by Yang Zhao on 11/14/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    enum Direct{
        unknown,
        right, down, left, up
    };
    size_t row, colume;
    size_t upperBound, lowerBound, leftBound, rightBound;
    pair<size_t, size_t> position = make_pair(0,0);
    
    bool CheckTerminate(Direct direct)
    {
        if(direct == right)
        {
            return (rightBound - position.second) <= 0;
        }
        else if(direct == left)
        {
            return (position.second - leftBound) <= 0;
        }
        else if(direct == down)
        {
            return (lowerBound - position.first) <= 0;
        }
        else if(direct == up)
        {
            return (position.first - upperBound) <= 0;
        }
        else
        {
            throw;
            return false;
        }
    }
    
    void StepOne(Direct direct, vector<vector<int>> const& matrix, vector<int>& result)
    {
        if(direct == right)
        {
            result.emplace_back((matrix[position.first])[++position.second]);
        }
        else if(direct == left)
        {
            result.emplace_back((matrix[position.first])[--position.second]);
        }
        else if(direct == down)
        {
            result.emplace_back((matrix[--position.first])[position.second]);
        }
        else if(direct == up)
        {
            result.emplace_back((matrix[++position.first])[position.second]);
        }
        else
        {
            throw;
        }
    }
    
    void Going(Direct direct, vector<vector<int>> const& matrix, vector<int>& result)
    {
        while(!CheckTerminate(direct))
        {
            StepOne(direct, matrix, result);
        }
    }
    
    void UpdateDirectAndBound(Direct& direct)
    {
        if(direct== right) { ++upperBound; direct = down; }
        else if(direct == down) { --rightBound; direct = left;}
        else if(direct == left) {--lowerBound; direct = up;}
        else if(direct == up) {++ leftBound; direct = right;}
    }
    
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        row = matrix.size();
        if (row == 0) return result;
        colume = matrix[0].size();
        
        //max/min reachable index.
        upperBound = 0; lowerBound = row-1; leftBound = 0; rightBound = colume-1;
        
        result.emplace_back(matrix[0][0]);
        Direct direct = right;
        while(1)
        {
            if(CheckTerminate(direct)) break;
            Going(direct, matrix, result);
            UpdateDirectAndBound(direct);
        }
        return result;
    }
};


int main(int argc, const char * argv[]) {
    Solution solution
    return 0;
}
