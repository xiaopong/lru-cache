/*
 * Copyright (C) 2012, xp@renzhi.ca
 * All rights reserved.
 */


#pragma once

#include <iterator>
#include <boost/bimap.hpp> 
#include <boost/bimap/list_of.hpp> 
#include <boost/bimap/set_of.hpp> 
#include <cassert> 

const size_t default_max_cap = 1000;

/**
 * Template class for a least recently used cache. The cache has a maximum
 * number of records to be stored. When the cache is full, the least recently
 * used record will be evicted to make space.
 *
 * The left side is a set of keys, and the right side is a list of values.
 * The most recently used value is at the end of the list. Therefore, the first
 * one in the list is the record that has been used the least. When the cache
 * is full and needs to make room for new record, the first record in the right-side
 * list will be evicted.
 */
template < 
    typename K,
    typename V
    > class LRUCache
{
public:
    typedef K key_type;
    typedef V value_type;

    typedef boost::bimaps::bimap< 
        boost::bimaps::set_of<key_type>, 
        boost::bimaps::list_of<value_type> 
        > container_type;

    typedef typename container_type::left_iterator iterator;
    typedef typename container_type::left_const_iterator const_iterator;

    LRUCache() {
        _capacity = default_max_cap;
    }

    /**
     * Constructor that specifies the maximum number of records to be stored.
     */
    LRUCache(size_t cap) : _capacity(cap) { 
        assert(_capacity != 0); 
    }


    void set_capcity(size_t cap) {
        _capacity = cap;
        while (_container.size() > _capacity) {
            _container.right.erase(_container.right.begin());
        }
    }

    iterator begin() { return _container.left.begin(); }
    iterator end() { return _container.left.end(); }

    /**
     * Get the value for key k.
     */
    iterator get(const key_type& k) { 
 
        iterator it = _container.left.find(k);
 
        if (it != _container.left.end()) { 
            // Found it. Need to update the access record view. 
            _container.right.relocate(_container.right.end(), 
                                      _container.project_right(it)); 
        } 

        return it;
    } 

    void insert(const key_type& k, const value_type& v) { 
         assert(_container.size() <= _capacity); 
 
         // If necessary, make space 
         if (_container.size() == _capacity) { 
             // by purging the least-recently-used element 
             _container.right.erase(_container.right.begin()); 
         } 
 
         // Create a new record from the key and the value 
         // bimap's list_view defaults to inserting this at 
         // the list tail (considered most-recently-used). 
         _container.insert(typename container_type::value_type(k, v)); 
    }

    size_t size() { return _container.size(); }

private:
    size_t _capacity;
    container_type _container;

};

