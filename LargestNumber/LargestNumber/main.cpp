//
//  main.cpp
//  LargestNumber
//
//  Created by Yang Zhao on 9/19/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    class comparer
    {
    public:
        bool operator () (string s1, string s2)
        {
            string l,s;
            bool neg = false;
            if(s1.length()>=s2.length())
            {
                l = s1; s = s2;
            }
            else
            {
                l = s2; s = s1;
                neg = true;
            }
            
            size_t i = 0;
            
            while(i<l.length()+s.length())
            {
                if(i<s.length())
                {
                    if(l[i] < s[i])
                        return neg;
                    else if(l[i] > s[i])
                        return !neg;
                }
                else if(i>=s.length() && i < l.length())
                {
                    if(l[i] < l[i-s.length()])
                        return neg;
                    else if(l[i] > l[i-s.length()])
                        return !neg;
                }
                else if(i>= l.length())
                {
                    if(s[i-l.length()] < l[i-s.length()])
                        return neg;
                    else if(s[i-l.length()] > l[i-s.length()])
                        return !neg;
                }
                
                i++;
            }
            return false;
        }
    };
    
    string NumToString(int n)
    {
        if(n == 0) return "";
        else
        {
            return NumToString(n/10) + string(1,'0'+n%10);
        }
        
    }
    
public:
    string largestNumber(vector<int>& nums) {
        vector<string> numToString;
        for(auto n: nums)
        {
            if(n==0) numToString.push_back(string("0"));
            else numToString.push_back(NumToString(n));
        }
        
        std::sort(numToString.begin(),numToString.end(), comparer());
        
        string result;
        for(auto s:numToString)
        {
            result.append(s);
        }
        return result;
    }
};


int main(int argc, const char * argv[]) {
    Solution solution;
    
    vector<int> nums = {121,12};
    auto res = solution.largestNumber(nums);
    cout << res <<endl;
    return 0;
}
