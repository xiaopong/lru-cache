/*
 * Copyright (C) 2012, xp@renzhi.ca
 * All rights reserved.
 */

#include <iostream>
#include <string>
#include <time.h>
#include <boost/lexical_cast.hpp>
#include "lru_cache.hpp"

using namespace std;

void test1()
{
    size_t cap = 5;
    LRUCache<std::string, std::string> cache(cap);

    std::cout << "insert key1 value1" << std::endl;
    cache.insert("key1", "value1");
    std::cout << "size = " << cache.size() << std::endl;

    std::cout << "insert key2 value2" << std::endl;
    cache.insert("key2", "value2");
    std::cout << "size = " << cache.size() << std::endl;

    std::cout << "insert key3 value3" << std::endl;
    cache.insert("key3", "value3");
    std::cout << "size = " << cache.size() << std::endl;

    std::cout << "insert key4 value4" << std::endl;
    cache.insert("key4", "value4");
    std::cout << "size = " << cache.size() << std::endl;

    std::cout << "insert key5 value5" << std::endl;
    cache.insert("key5", "value5");
    std::cout << "size = " << cache.size() << std::endl;

    LRUCache<std::string, std::string>::iterator it = cache.get("key1");
    if (it == cache.end())
        std::cout << "key1 not found" << std::endl;
    else
        std::cout << "key1: " << it->second << std::endl;

    LRUCache<std::string, std::string>::iterator it2 = cache.begin();
    while (it2 != cache.end())
    {
        std::cout << "key=" << it2->first << "; value=" << it2->second << std::endl;
        it2++;
    }

    std::cout << "insert key6 value6" << std::endl;
    cache.insert("key6", "value6");
    std::cout << "size = " << cache.size() << std::endl;

    it2 = cache.begin();
    while (it2 != cache.end())
    {
        std::cout << "key=" << it2->first << "; value=" << it2->second << std::endl;
        it2++;
    }

    // LRUCache<std::string, std::string>::iterator it2 = cache.get("key1");
    // if (it2 == cache.end())
    //     std::cout << "key1 not found" << std::endl;

    std::cout << "insert key7 value7" << std::endl;
    cache.insert("key7", "value7");
    std::cout << "size = " << cache.size() << std::endl;

    it2 = cache.begin();
    while (it2 != cache.end())
    {
        std::cout << "key=" << it2->first << "; value=" << it2->second << std::endl;
        it2++;
    }
    
}

void test2()
{
    size_t cap = 1000000;
    LRUCache<std::string, std::string> cache(cap);

    clock_t bt = clock();
    for (size_t i = 0; i < cap; i++)
    {
        std::string key("key " + boost::lexical_cast<string>(i+1));
        std::string val("val " + boost::lexical_cast<string>(i+1));
        cache.insert(key, val);
    }
    clock_t et = clock();
    std::cout << "Time to insert " << cap << " records : " << ((double)(et - bt) / CLOCKS_PER_SEC) << std::endl;

    string key("key " + boost::lexical_cast<string>(cap+1));
    string val("val " + boost::lexical_cast<string>(cap+1));
    bt = clock();
    cache.insert(key, val);
    et = clock();
    std::cout << "Time to insert one record : " << ((double)(et - bt) / CLOCKS_PER_SEC) << std::endl;
    
    bt = clock();
    LRUCache<std::string, std::string>::iterator it = cache.get("key 500001");
    if (it == cache.end())
        std::cout << "key not found" << std::endl;
    else
        std::cout << it->first << " : " << it->second << std::endl;
    et = clock();
    std::cout << "Time to find one record : " << ((double)(et - bt) / CLOCKS_PER_SEC) << std::endl;

    std::cin.get();

}

int main(int argc, char *argv[])
{
    //test1();
    test2();
    return 0;
}
