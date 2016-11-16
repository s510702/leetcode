//
//  main.cpp
//  maxPoints
//
//  Created by Yang Zhao on 4/14/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

class ComparePoints
{
public:
    bool operator() (const Point& a, const Point& b) const
    {
        if(a.x != b.x) return a.x<b.x;
        else return a.y <b.y;
    }
};

class Solution {
    int maxPointsLine;
    map<Point, set<Point, ComparePoints>, ComparePoints > ignorePoints;
    vector<Point> compactPoints;
    
public:
    int maxPoints(vector<Point>& points) {
        if(points.size() < 3) return (int)points.size();
        
        map<pair<int, int>, int> pointsCountMap;
        
        for(auto const& p : points)
        {
            auto key = make_pair(p.x, p.y);
            pointsCountMap[key]++;
            if(pointsCountMap[key] == 1)
            {
                compactPoints.push_back(p);
            }
        }
        
        
        int maxPointsLine = 1;
        for(auto const& cp : compactPoints)
        {
            set<Point, ComparePoints>& ignoreSet = ignorePoints[cp];
            map<float, int> slopeToPoints;
            int vPoints = 0;
            int localmax = 0;
            for(auto const& pnt : compactPoints)
            {
                if(pnt.x == cp.x && pnt.y == cp.y)
                {
                    continue;
                }
                
                if(ignoreSet.find(pnt) == ignoreSet.end())
                {
                    if(pnt.x == cp.x)
                    {
                        vPoints += pointsCountMap[make_pair(pnt.x, pnt.y)];
                        if(vPoints> localmax)
                        {
                            localmax = (int)vPoints;
                        }
                    }
                    else
                    {
                        double slope = (double)(pnt.y - cp.y) / (pnt.x - cp.x);
                        slopeToPoints[slope]++;
                        if(slopeToPoints[slope] > localmax)
                        {
                            localmax = (int) slopeToPoints[slope];
                        }
                        
                    }
                    ignorePoints[pnt].insert(cp);
                }
            }
            
            int numsamepoints = pointsCountMap[make_pair(cp.x,cp.y)];
            if(localmax+numsamepoints > maxPointsLine) maxPointsLine = localmax+numsamepoints;
        } // end of center point loop.
        
        return maxPointsLine;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
