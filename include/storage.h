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
public:
    storage(std::size_t blockSize = 1000);
    void insert(const std::string &str);
    const std::string &get(uint64_t index);
private:
    using HintType = std::set<std::string>::iterator;
    std::set<std::string> _myset;
    std::vector<HintType> _hints;
    std::size_t _blockSize;
};

#endif /* storage_h */
