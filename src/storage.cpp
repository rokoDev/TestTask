//
//  storage.cpp
//  fastmap
//
//  Created by roko on 09/02/2019.
//

#include "storage.h"
#include <iostream>

storage::storage(std::size_t blockSize):_blockSize(blockSize)
{
    
}

void storage::insert(const std::string &str)
{
    //TODO insert str with sorting
    const auto result = _myset.insert(str);
    if (result.second)
    {
        auto firstGreaterThanStr = std::upper_bound(_hints.begin(), _hints.end(), result.first, [](const HintType & it1, const HintType & it2) -> bool
                                                    {
                                                        return *it1 < *it2;
                                                    });
        if (firstGreaterThanStr != _hints.end()) {
            for (auto it = firstGreaterThanStr; it != _hints.end(); ++it)
            {
                *it = --(*it);
            }
        }
        
        if (_myset.size()%_blockSize == 0)
        {
            _hints.push_back(--(_myset.end()));
        }
    }
}

const std::string & storage::get(uint64_t index)
{
    //TODO return string via index
    const auto hintIndex = index/_blockSize;
    if (hintIndex != 0)
    {
        const auto offsetAfterHint = index%_blockSize+1;
        auto val = std::next(_hints[hintIndex-1], offsetAfterHint);
        return *val;
    }
    else
    {
        const auto offsetAfterHint = index%_blockSize;
        auto val = std::next(_myset.begin(), offsetAfterHint);
        return *val;
    }
}
