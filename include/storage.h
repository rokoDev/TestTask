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
    bool isForward(std::size_t index, std::size_t & stepCount, HintType & startIt) const;
    
    std::set<std::string> _myset;
    std::vector<HintType> _hints;
    std::size_t _blockSize;
};

#endif /* storage_h */
