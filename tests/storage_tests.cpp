//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include "gtest/gtest.h"
#include "storage.h"

class StorageTest: public ::testing::Test {
    
public:
    
    StorageTest(): _st()
    {
        
    }
    void insert(const std::string &str)
    {
        _st.insert(str);
    }
    const std::string &get(std::size_t index)
    {
        return _st.get(index);
    }
protected:
    void SetUp()
    {
        std::vector<std::string> initStrings =
        {
            "bbb",
            "aaa",
            "eee",
            "kkk",
            "ddd",
            "kkk",
            "fff",
            "ccc",
            "lll",
            "mmm",
            "nnn",
            "ooo",
            "ppp"
        };
        for (auto & str : initStrings)
        {
            _st.insert(str);
        }
        //aaa bbb ccc ddd eee fff kkk lll mmm nnn ooo ppp
    }
    
private:
    storage _st;
};

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
