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
        for (auto it = firstGreaterThanStr; it != _hints.end(); ++it)
            *it = --(*it);
        
        if (_myset.size()%_blockSize == 0)
            _hints.push_back(--(_myset.end()));
    }
}

const std::string & storage::get(std::size_t index) const
{
    //TODO return string via index
    std::size_t stepCount;
    HintType startIt;
    if (isForward(index, stepCount, startIt))
        return *std::next(startIt, stepCount);
    else
        return *std::prev(startIt, stepCount);
}

bool storage::isForward(std::size_t index, std::size_t & stepCount, HintType & startIt) const
{
    const std::size_t hintIndex = index/_blockSize;
    const std::size_t left = (hintIndex > 0) ? hintIndex*_blockSize-1 : 0;
    const std::size_t right = ((hintIndex+1)*_blockSize-1 < _myset.size()) ? (hintIndex+1)*_blockSize-1 : _myset.size()-1;
    
    const auto fromLeft = index-left;
    const auto fromRight = right-index;
    std::string retVal;
    if (fromLeft < fromRight)
    {
        stepCount = fromLeft;
        startIt = (hintIndex > 0) ? _hints[hintIndex-1] : _myset.begin();
        return true;
    }
    else
    {
        stepCount = fromRight;
        startIt = (_myset.size()-1 != right) ? _hints[hintIndex] : std::prev(_myset.end());
        return false;
    }
}
