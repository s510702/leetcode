//
//  main.cpp
//  LRUCache
//
//  Created by Yang Zhao on 5/30/16.
//  Copyright © 2016 Yang Zhao. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <list>



using namespace std;

class LRUCache{
    typedef int Key;
    typedef int Value;
    typedef list<Key>::iterator HistoryPos;
    typedef pair<Value, HistoryPos> CacheItem;
    unordered_map<Key, CacheItem> cache;
    int capacity;
    // Head is the most recent visited key, while the tail is the oldest visited key.
    list<Key> history;
    
    const Value NO_EXIST_KEY = -1;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        cout << "get : " << key <<endl;
        auto it = cache.find(key);
        if(it != cache.end())
        {
            CacheItem& item = (it->second);
            history.erase(item.second);
            history.push_front(key);
            item.second = history.begin();
            return item.first;
        }
        else
        {
            return NO_EXIST_KEY;
        }
    }
    
    void set(int key, int value) {
        cout << "set : key - " << key << " value - " << value << endl;
        auto it = cache.find(key);
        if(it != cache.end())
        {
            CacheItem& item = (it->second);
            history.erase(item.second);
            history.push_front(key);
            item.second = history.begin();
            item.first = value;
        }
        else
        {
            // add new item
            if(cache.size() > capacity)
            {
                throw;
            }
            
            if(cache.size() == capacity)
            {
                Key rmkey = history.back();
                auto it = cache.find(rmkey);
                if(it!=cache.end())
                {
                    cache.erase(it);
                    history.pop_back();
                }
                else
                {
                    throw;
                }
            }
            history.push_front(key);
            cache.emplace(key, make_pair(value, history.begin()));
        }

    }
    
    void runtest()
    {
        set(10,13);set(3,17);set(6,11);set(10,5);set(9,10);get(13);set(2,19);get(2);get(3);set(5,25);get(8);set(9,22);set(5,5);
        set(1,30);get(11);set(9,12);get(7);get(5);get(8);get(9);set(4,30);set(9,3);get(9);get(10);get(10);set(6,14);set(3,1);get(3);set(10,11);get(8);set(2,14);get(1);get(5);get(4);set(11,4);set(12,24);set(5,18);get(13);set(7,23);get(8);get(12);set(3,27);set(2,12);get(5);set(2,9);set(13,4);set(8,18);set(1,7);get(6);set(9,29);set(8,21);get(5);set(6,30);set(1,12);get(10);set(4,15);set(7,22);set(11,26);set(8,17);set(9,29);get(5);set(3,4);set(11,30);get(12);set(4,29);get(3);get(9);get(6);set(3,4);get(1);get(10);set(3,29);set(10,28);set(1,20);set(11,13);get(3);set(3,12);set(3,8);set(10,9);set(3,26);get(8);get(7);get(5);set(13,17);set(2,27);set(11,15);get(12);set(9,19);set(2,15);set(3,16);get(1);set(12,17);set(9,1);set(6,19);get(4);get(5);get(5);set(8,1);set(11,7);set(5,2);set(9,28);get(1);set(2,2);set(7,4);set(4,22);set(7,24);set(9,26);set(13,28);set(11,26);
    }
};

int main(int argc, const char * argv[]) {
    LRUCache lruCache(10);
    lruCache.runtest();
    return 0;
}
