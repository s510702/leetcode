//
//  main.cpp
//  TwoOrderedArrayMedian
//
//  Created by Yang Zhao on 4/16/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    typedef pair<size_t, size_t> Range;
private:
    void PreprocessSortedArray(vector<int>& array)
    {
        int head = *array.begin();
        int tail = *array.rbegin();
        
        if(tail < head)
        {
            // descending ordering, let's revert it.
            for(int i =0; i < (array.size() >> 1); i++)
            {
                int tmp = array[i];
                array[i] = array[array.size()-1-i];
                array[array.size()-1-i] = tmp;
            }
        }
        
    }
    
    size_t GetTargetSize(size_t total_size)
    {
        size_t target_size;
        bool odd = (total_size % 2) == 1;
        if( odd )
        {
            target_size = (total_size+1)>>1;
        }
        else
        {
            target_size = (total_size >> 1) + 1;
        }
        return target_size;
    }
    
public:
    double findMediaOrderdSortedArrays(vector<int>& lower, vector<int>& upper)
    {
        size_t total_size = lower.size() + upper.size();
        if(total_size == 0)
        {
            throw;
        }
        
        size_t target_size = GetTargetSize(total_size);
        bool odd = (total_size % 2) == 1;
        
        if(lower.size()>=target_size)
        {
            if(odd)
            {
                return static_cast<double>(lower[target_size-1]);
            }
            else
            {
                return static_cast<double>(lower[target_size-1] + lower[target_size-2])/2;
            }
        }
        else if(lower.size() == target_size - 1)
        {
            if(odd)
            {
                return static_cast<double>(upper[0]);
            }
            else
            {
                return static_cast<double>(*lower.rbegin() + upper[0])/2;
            }
        }
        else
        {
            if(odd)
            {
                return static_cast<double>(upper[target_size-lower.size()-1]);
            }
            else
            {
                return static_cast<double>(upper[target_size-lower.size()-1] + upper[target_size-lower.size()-2])/2;
            }
            
        }

    }
    
    size_t GetFromShortByRange(Range const& range)
    {
        // Native approach
        //return range.first;
        
        // Binary search approach
        return (range.first+range.second)/2;
    }
    
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() == 0 && nums2.size() == 0)
            return 0;
        
        if(nums1.size()>nums2.size())
        {
            return findMedianSortedArrays(nums2,nums1);
        }
        
        // from now on, nums1.size() < nums2.size()
        if(nums1.size() == 0)
        {
            if(nums2.size()%2 == 1)
            {
                // even number array
                size_t idx = (nums2.size())>>1;
                return nums2[idx];
            }
            else
            {
                size_t idx = (nums2.size())>>1;
                return static_cast<double>(nums2[idx] + nums2[idx-1])/2;
            }
        }
        
        // Revert vector if it is not in acsending order
        // TODO: optimize it out
        PreprocessSortedArray(nums1);
        PreprocessSortedArray(nums2);
        
        // From here, we can assume nums1 and nums2 are sorted in acsending order.
        if(*nums1.rbegin() <= *nums2.begin())
        {
            return findMediaOrderdSortedArrays(nums1, nums2);
        }
        else if(*nums1.begin() >= *nums2.rbegin())
        {
            return findMediaOrderdSortedArrays(nums2, nums1);
        }
        else
        {
            // main case
            size_t target_size = GetTargetSize(nums1.size()+nums2.size());
            Range range = make_pair(0, nums1.size());
            size_t from_short = GetFromShortByRange(range);
            size_t from_long = target_size-from_short;
            bool done = false;
            do
            {
                if(from_short == 0)
                {
                    if(from_long <= nums2.size() && nums1[0]>=nums2[from_long - 1])
                    {
                        done = true;
                    }
                    else
                    {
                        range = make_pair(1, range.second);
                        from_short = 1;
                        from_long =target_size - from_short;
                    }
                }
                else if(nums1[from_short-1] == nums2[from_long-1])
                {
                    done = true;
                }
                else if(nums1[from_short-1] > nums2[from_long-1])
                {
                    if(from_long >= nums2.size() || nums1[from_short-1] <= nums2[from_long])
                    {
                        done = true;
                    }
                    else
                    {
                            range = make_pair(range.first, from_short - 1);
                            from_short = GetFromShortByRange(range);
                            from_long = target_size - from_short;
                    }
                }
                else // nums1[from_short-1] < nums2[from_long-1]
                {
                    if(from_short >= nums1.size() || nums1[from_short] >= nums2[from_long-1])
                    {
                        done = true;
                    }
                    else
                    {
                        range = make_pair(from_short+1, range.second);
                        from_short = GetFromShortByRange(range);
                        from_long = target_size - from_short;
                    }
                }
                
                // make the new from_short from the new range.
                if(range.first == range.second)
                {
                    done = true;
                    from_short = range.first;
                    from_long = target_size - from_short;
                }
            } while(!done);
            
            // Find the right element
            if((nums1.size()+nums2.size())%2==0)
            {
                if(from_short == 0)
                    return static_cast<double>(nums2[target_size-1] + nums2[target_size-2])/2;
                else
                {
                    int p1 = static_cast<int> (from_short - 1);
                    int p2 = static_cast<int> (from_long - 1);
                    int result = 0;
                    for(int i=0; i<2; i++)
                    {
                        if( p1<0 || nums1[p1] < nums2[p2])
                        {
                            result += nums2[p2];
                            p2--;
                        }
                        else
                        {
                            result += nums1[p1];
                            p1--;
                        }
                    }
                    return static_cast<double>(result)/2;
                }
            }
            else
            {
                if(from_short == 0)
                    return nums2[target_size-1];
                else
                    return nums1[from_short-1] > nums2[from_long-1] ? nums1[from_short-1] : nums2[from_long-1];
            }
        }
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<int> nums1={1,6,7,8};
    vector<int> nums2={2,3,4,5};
    
    Solution solution;
    double res = solution.findMedianSortedArrays(nums1, nums2);
    cout << "The result is: " << res << endl;
    
    return 0;
}
