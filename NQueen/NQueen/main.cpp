//
//  main.cpp
//  NQueen
//
//  Created by Yang Zhao on 4/13/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int sizeBoard_;
    vector<int> board_;

public:
    void Print(vector<int> board)
    {
        if(board.size() != sizeBoard_)
        {
           throw;
        }
        else
        {
            for (int i=0; i<sizeBoard_-1; i++)
            {
                cout << board[i] << " ";
            }
            if(sizeBoard_>1)
            {
                cout << board[sizeBoard_-1] << ";\n";
            }
        }
    }
    
    int NQueensRecur(int idx)
    {
        //cout << "Idx: " << idx <<endl;
        int result = 0;
        if(idx == sizeBoard_)
        {
            // end of recursion, got a result.
            Print(board_);
            return 1;
        }
        else if(idx > sizeBoard_ || idx < 0)
        {
            throw;
        }
        else
        {
            // placing the idx column
            vector<char> isAllow(sizeBoard_, 1);
            for(int i=0; i<idx; i++)
            {
                int place = board_[i];
                int dist = idx - i;
                isAllow[place] = 0;
                if(place + dist < sizeBoard_) isAllow[place+dist] = 0;
                if(place - dist >= 0) isAllow[place-dist] = 0;
            }
            
            
            for(int i = 0; i<sizeBoard_; i++)
            {
                if(isAllow[i]>0)
                {
                    board_[idx] = i;
                    result += NQueensRecur(idx+1);
                }
            }
        }
        return result;
    }
    
    int totalNQueens(int n) {
        int result = 0;
        
        if(n<0)
        {
            cerr << "Error: n must be non-negative." <<endl;
            return result;
        }
        cout << "Number of queens: " << n <<endl;
        sizeBoard_ = n;
        board_.resize(n);
        
        result = NQueensRecur(0);
        
        return result;
    }
};

int main(int argc, const char * argv[]) {
    int n;
    std::cout << "Input n: \n";
    std::cin >> n;
    
    Solution solution;
    std::cout << solution.totalNQueens(n) <<endl;
    
    return 0;
}
