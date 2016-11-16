//
//  main.cpp
//  StrongPasswordChecker
//
//  Created by Yang Zhao on 10/31/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    enum Operation{
        None,
        Add,
        Delete,
        Replace,
    };
    
    struct Action
    {
        Operation oper_;
        size_t num_;
        
        Action() : oper_(None), num_(0) {};
        Action(Operation o, size_t n) : oper_(o), num_(n) {};
    };
    
public:
    int strongPasswordChecker(string s) {
        size_t length = s.length();
        bool lowercase(false), uppercase, digit;
        vector<pair<char, size_t>> repeatPatterns;
        
        char lastChar = 0;
        size_t repeatCnt = 0;
        for(size_t i = 0; i<length; i++)
        {
            if(!lowercase && s[i] >='a' && s[i]<='z') lowercase = true;
            if(!uppercase && s[i] >='A' && s[i]<='Z') uppercase = true;
            if(!digit && s[i] >='0' && s[i]<='9') digit = true;
            
            if(s[i] == lastChar)
            {
                ++repeatCnt;
            }
            else
            {
                if(repeatCnt>0) repeatPatterns.emplace_back(lastChar, repeatCnt+1);
                repeatCnt = 0;
                lastChar = s[i];
            }
        }
        
        vector<Action> actions;
        if(length<6) actions.emplace_back(Add, 6-length);
        else if(length>20) actions.emplace_back(Delete, length-20);
        
        size_t add = (uppercase ? 1 : 0) + (lowercase ? 1:0) + (digit ? 1:0);
        if(add > 0)
        {
            if(actions.empty()) actions.emplace_back(Add, add);
            else if(actions[0].oper_ == Add)
            {
                actions[0].num_ = max(actions[0].num_, add);
            }
            else if(actions[0].oper_ == Delete)
            {
                actions.emplace_back(Replace, add);
            }
        }
        
        
        
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution solution;
    auto result = solution.strongPasswordChecker("");
    cout << result;
    return 0;
}
