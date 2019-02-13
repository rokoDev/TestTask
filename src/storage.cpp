//
//  storage.cpp
//  fastmap
//
//  Created by roko on 09/02/2019.
//

#include "storage.h"
#include <iostream>
#include <thread>

storage::storage(std::size_t blockSize):_blockSize(blockSize)
{
    _vec.reserve(std::thread::hardware_concurrency());
}

void storage::altIterators(std::vector<HintType>::iterator first, std::vector<HintType>::iterator last)
{
    for (auto it = first; it != last; ++it)
        *it = --(*it);
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
        
#ifdef SINGLE_THREAD
//        for (auto it = firstGreaterThanStr; it != _hints.end(); ++it)
//            *it = --(*it);
        
        if (firstGreaterThanStr != _hints.end()) {
            
            const std::size_t countToProcess = std::distance(firstGreaterThanStr, _hints.end());
            //if (countToProcess >= 32)
            {
                const auto maxThreadCount = 8;//std::thread::hardware_concurrency();
                
                const std::size_t wholeCount = countToProcess/maxThreadCount;
                const std::size_t restCount = countToProcess%maxThreadCount;
                
                const std::size_t threadCountToCreate = (wholeCount > 0) ? maxThreadCount : restCount;
                
                std::vector<HintType>::iterator lastIt = firstGreaterThanStr;
                
                for (int i = 0; i < threadCountToCreate; ++i)
                {
                    auto firstIt = lastIt;
                    const std::size_t count = wholeCount+((i < restCount)?1:0);
                    lastIt = std::next(firstIt, count);
                    _vec.push_back({firstIt, lastIt});
                }
                _group.run([this](){
                    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, _vec.size()), [this](const tbb::blocked_range<std::size_t> &r){
                        for (size_t i = r.begin(); i != r.end(); ++i)
                        {
                            auto lastIt = _vec[i].second;
                            for (auto it = _vec[i].first; it != lastIt; ++it)
                                *it = --(*it);
                        }
                    });
                });
                
                _group.wait();
                _vec.clear();
            }
//            else {
//                for (auto it = firstGreaterThanStr; it != _hints.end(); ++it)
//                    *it = --(*it);
//            }
        }
#endif

        
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
