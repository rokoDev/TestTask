//
//  storage.cpp
//  fastmap
//
//  Created by roko on 09/02/2019.
//

#include "storage.h"
#include <iostream>

storage::storage()
{
    
}

void storage::insert(const std::string &str)
{
    //TODO insert str with sorting
    _myset.insert(str);
}

const std::string & storage::get(std::size_t index) const
{
    //TODO return string via index
    return *_myset.find_by_order(index);
}
