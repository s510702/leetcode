//
//  main.cpp
//  Column Title
//
//  Created by Yang Zhao on 10/2/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        /*
        int m = n;
        string result;
        while(m>0)
        {
            result.insert(0,1,char(m%26+'A'));
            m = m/26;
        }
        --result[0];
        return result;
         */
        if(n<= 0) throw;
        
        // the largest of idx digits.
        vector<unsigned int> largest;
        largest.push_back(0);
        size_t i = 0;
        unsigned int weight = 1;
        while(largest[i] < n && largest[i] <= INT_MAX)
        {
            largest.push_back(largest[i]+26*weight);
            weight *= 26;
            ++i;
        }
        
        for(auto l : largest)
        {
            cout << l << ", ";
        }
        cout << endl;
        
        if(largest[i] ==n ) return string(i, char('Z'));
        //largest[i] > n , n is a i digits number.
        
        string result = string(i, char('A'));
        int m = n - (largest[i-1]+1);
        while(m>0)
        {
            result[i-1] = m%26+'A';
            m = m/26;
            i--;
        }
        
        return result;
        
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution solution;
    cout << (solution.convertToTitle(54)).c_str() << endl;
    
    return 0;
}
