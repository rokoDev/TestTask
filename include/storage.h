//
//  storage.h
//  fastmap
//
//  Created by roko on 09/02/2019.
//

#ifndef storage_h
#define storage_h

#include <vector>
#include <set>
#include <string>
//#include <memory>
#include "tbb/tbb.h"

#define SINGLE_THREAD

#ifndef SINGLE_THREAD
#include "threadpool11/threadpool11.hpp"
#endif

class storage
{
    friend class StorageTest;
public:
    storage(std::size_t blockSize = 1000);
    void insert(const std::string &str);
    const std::string &get(std::size_t index) const;
    std::size_t getBlockSize() const
    {
        return _blockSize;
    }

private:
    using HintType = std::set<std::string>::iterator;
    using VecHintIt = std::vector<HintType>::iterator;
    bool isForward(std::size_t index, std::size_t & stepCount, HintType & startIt) const;
    void altIterators(VecHintIt first, VecHintIt last);
    
    std::set<std::string> _myset;
    std::vector<HintType> _hints;
    std::size_t _blockSize;
    tbb::task_group _group;
    std::vector<std::pair<VecHintIt, VecHintIt>> _vec;
};

#endif /* storage_h */
