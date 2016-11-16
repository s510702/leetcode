//
//  main.cpp
//  shortestPalindrome
//
//  Created by Yang Zhao on 8/18/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.length() < 2) return s;
        
        bool after = !(s.length()%2);
        size_t index = s.length()>>1;
        
        while(true)
        {
            bool getit = true;
            size_t i = 0;
            while(true)
            {
                if(after)
                {
                    if(s[index-i] != s[index+i+1])
                    {
                        getit = false;
                        break;
                    }
                    if(index == i)
                    {
                        break;
                    }
                    else
                    {
                        i++;
                    }
                }
                else
                {
                    if(s[index-i-1] != s[index+i+1])
                    {
                        getit = false;
                        break;
                    }
                    if(index == i+1)
                    {
                        break;
                    }
                    else{
                        i++;
                    }
                }
            }
            
            if(getit)
            {
                break;
            }
            
            if (after == true)
                after = false;
            else
            {
                index--;
                after = true;
            }
            
            // That's the end.
            if(index == 0 && after == false)
                break;
        }
        
        // after we found the result
        string result = s.substr(index+1, s.length()-index-1);
        std::reverse(result.begin(), result.end());
        result.append(s.substr(index + (after? 1 : 0), s.length()-index-(after? 1 : 0)));

        return result;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution solution;
    cout << solution.shortestPalindrome("abcd") << endl;
    return 0;
}
