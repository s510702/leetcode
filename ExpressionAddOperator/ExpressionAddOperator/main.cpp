//
//  main.cpp
//  ExpressionAddOperator
//
//  Created by Yang Zhao on 6/6/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
    enum Operator
    {
        Op_Add,
        Op_Minus,
        Op_Multiply
    };
    typedef shared_ptr<vector<Operator>> OpListPtr;
    
    map<pair<size_t, int>, vector<OpListPtr>> cached_results;
    vector<uint> m_numList;
    
public:
    vector<uint> GetNumbersFromString(string const& num)
    {
        vector<uint> numList;
        for(size_t i=0; i<num.length(); i++)
        {
            numList.push_back(num[i]-'0');
        }
        return numList;
    }
    
    // Concatenate oper on sub-results.
    void GenerateNewResultFromDivide(vector<OpListPtr>& res, vector<OpListPtr> const& divide, Operator oper)
    {
        for(auto const& it : divide)
        {
            OpListPtr p = make_shared<vector<Operator>>();
            p->push_back(oper);
            p->insert(p->end(), it->begin(), it->end());
            res.push_back(p);
        }
    }
    
    // Concatenate *..*<oper> on sub-results.
    void GenerateNewResultFromDivide(vector<OpListPtr>& res, vector<OpListPtr> const& divide, size_t numMultiPly, Operator oper)
    {
        for(auto const& it : divide)
        {
            OpListPtr p = make_shared<vector<Operator>>();
            for(auto i= 0; i<numMultiPly; i++)
            {
                p->push_back(Op_Multiply);
            }
            p->push_back(oper);
            
            p->insert(p->end(), it->begin(), it->end());
            res.push_back(p);
        }
    }

    
    bool addOperatorsRecur(size_t start_idx, int target, vector<OpListPtr>& res)
    {
        if(start_idx >= m_numList.size())
        {
            throw;
        }
        
        uint head = m_numList[start_idx];
        if(start_idx == m_numList.size()-1)
        {
            if(target == head)
            {
                res.push_back(make_shared<vector<Operator>>());
            }
            return target == head;
        }
        
        res.clear();
        auto it = cached_results.find(make_pair(start_idx, target));
        if(it != cached_results.end())
        {
            res = it->second;
            return !(res.empty());
        }
        
        vector<OpListPtr> divide;
        bool found = false;
        // +
        if(addOperatorsRecur(start_idx+1, target-head, divide))
        {
            GenerateNewResultFromDivide(res, divide, Op_Add);
            found = true;
        }
        
        // -
        if(addOperatorsRecur(start_idx+1, target+head, divide))
        {
            GenerateNewResultFromDivide(res, divide, Op_Minus);
            found = true;
        }
        
        //*
        uint mul_res = head;
        for(auto i = start_idx+1; i<= m_numList.size()-1; i++)
        {
            mul_res = mul_res*m_numList[i];
            if(i<m_numList.size()-1)
            {
                if(addOperatorsRecur(i+1, target-mul_res, divide))
                {
                    GenerateNewResultFromDivide(res, divide, i-start_idx, Op_Add);
                    found = true;
                }
                
                if(addOperatorsRecur(i+1, target+mul_res, divide))
                {
                    GenerateNewResultFromDivide(res, divide, i-start_idx, Op_Minus);
                    found = true;
                }
            }
            else
            {
                // * until the last element.
                if(mul_res == target)
                {
                    OpListPtr p = make_shared<vector<Operator>>(i-start_idx,Op_Multiply);
                    res.push_back(p);
                    found = true;
                }
            }
        }
        
        if(found)
        {
            cached_results[make_pair(start_idx, target)] = res;
        }
        
        return found;
    }
    
    vector<string> GenerateResult(string num, vector<OpListPtr> const & res)
    {
        vector<string> ret;
        for(auto const& opers : res)
        {
            if(opers->size() != num.length()-1)
            {
                cout << opers->size() <<endl;
                throw;
            }
            
            string s;
            for(size_t i = 0; i<num.length(); i++)
            {
                s.append(1, num[i]);
                if(i < opers->size())
                {
                    char c = GetCharacter((*opers)[i]);
                    s.append(1, c);
                }
            }
            
            ret.push_back(s);
        }
        return ret;
    }
    
    char GetCharacter(Operator op)
    {
        if(op == Op_Add)
        {
            return '+';
        }
        else if(op == Op_Minus)
        {
            return '-';
        }
        else
        {
            return '*';
        }
    }
    
    vector<string> addOperators(string num, int target)
    {
        m_numList = GetNumbersFromString(num);
        vector<OpListPtr> res;
        if(addOperatorsRecur(0, target, res))
        {
            return GenerateResult(num, res);
        }
        else
        {
            return vector<string>();
        }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    Solution solution;
    auto results = solution.addOperators("232", 8);
    for(auto const& res : results)
    {
        cout << res << endl;
    }
    
    return 0;
}
