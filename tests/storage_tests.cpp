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
    using HintT = storage::HintType;
    
    StorageTest(): _st(5)
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
    const std::set<std::string> & getSet() const
    {
        return _st._myset;
    }
    const std::vector<storage::HintType> & getHints() const
    {
        return _st._hints;
    }
    std::size_t getBlockSize() const
    {
        return _st._blockSize;
    }
    bool isForward(std::size_t index, std::size_t & stepCount, HintT & startIt) const
    {
        return _st.isForward(index, stepCount, startIt);
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

TEST_F(StorageTest, Test1)
{
    ASSERT_EQ(getSet().size(), 12);
}

TEST_F(StorageTest, Test2)
{
    const auto validHint1 = *std::next(getSet().begin(), getBlockSize()-1);
    const auto actualHint1 = *getHints()[0];
    ASSERT_EQ(validHint1, actualHint1);
}

TEST_F(StorageTest, Test3)
{
    const auto validHint2 = *std::next(getSet().begin(), 2*getBlockSize()-1);
    const auto actualHint2 = *getHints()[1];
    ASSERT_EQ(validHint2, actualHint2);
}

TEST_F(StorageTest, Test4)
{
    const std::size_t index = 0;
    const auto aaa = get(index);
    ASSERT_EQ(aaa, std::string("aaa"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, true);
    ASSERT_EQ(stepCount, 0);
    ASSERT_EQ(*startIt, std::string("aaa"));
}

TEST_F(StorageTest, Test5)
{
    const std::size_t index = 1;
    const auto bbb = get(index);
    ASSERT_EQ(bbb, std::string("bbb"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, true);
    ASSERT_EQ(stepCount, 1);
    ASSERT_EQ(*startIt, std::string("aaa"));
}

TEST_F(StorageTest, Test6)
{
    const std::size_t index = 2;
    const auto ccc = get(index);
    ASSERT_EQ(ccc, std::string("ccc"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 2);
    ASSERT_EQ(*startIt, std::string("eee"));
}

TEST_F(StorageTest, Test7)
{
    const std::size_t index = 3;
    const auto ddd = get(index);
    ASSERT_EQ(ddd, std::string("ddd"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 1);
    ASSERT_EQ(*startIt, std::string("eee"));
}

TEST_F(StorageTest, Test8)
{
    const std::size_t index = 4;
    const auto eee = get(index);
    ASSERT_EQ(eee, std::string("eee"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 0);
    ASSERT_EQ(*startIt, std::string("eee"));
}

TEST_F(StorageTest, Test9)
{
    const std::size_t index = 5;
    const auto fff = get(index);
    ASSERT_EQ(fff, std::string("fff"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, true);
    ASSERT_EQ(stepCount, 1);
    ASSERT_EQ(*startIt, std::string("eee"));
}

TEST_F(StorageTest, Test10)
{
    const std::size_t index = 6;
    const auto kkk = get(index);
    ASSERT_EQ(kkk, std::string("kkk"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, true);
    ASSERT_EQ(stepCount, 2);
    ASSERT_EQ(*startIt, std::string("eee"));
}

TEST_F(StorageTest, Test11)
{
    const std::size_t index = 7;
    const auto lll = get(index);
    ASSERT_EQ(lll, std::string("lll"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 2);
    ASSERT_EQ(*startIt, std::string("nnn"));
}

TEST_F(StorageTest, Test12)
{
    const std::size_t index = 8;
    const auto mmm = get(index);
    ASSERT_EQ(mmm, std::string("mmm"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 1);
    ASSERT_EQ(*startIt, std::string("nnn"));
}

TEST_F(StorageTest, Test13)
{
    const std::size_t index = 9;
    const auto nnn = get(index);
    ASSERT_EQ(nnn, std::string("nnn"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 0);
    ASSERT_EQ(*startIt, std::string("nnn"));
}

TEST_F(StorageTest, Test14)
{
    const std::size_t index = 10;
    const auto ooo = get(index);
    ASSERT_EQ(ooo, std::string("ooo"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 1);
    ASSERT_EQ(*startIt, std::string("ppp"));
}

TEST_F(StorageTest, Test15)
{
    const std::size_t index = 11;
    const auto ppp = get(index);
    ASSERT_EQ(ppp, std::string("ppp"));
    
    std::size_t stepCount;
    HintT startIt;
    const bool isForwardResult = isForward(index, stepCount, startIt);
    
    ASSERT_EQ(isForwardResult, false);
    ASSERT_EQ(stepCount, 0);
    ASSERT_EQ(*startIt, std::string("ppp"));
}

TEST(BasicTests, Test1)
{
    storage st;
    const std::string val("aaa");
    st.insert(val);
    auto val_at_index = st.get(0);
    ASSERT_EQ(val_at_index, val);
}

TEST(BasicTests, Test2)
{
    storage st;
    
    const std::string val_1("aaa");
    st.insert(val_1);
    
    const std::string val_2("bbb");
    st.insert(val_2);
    
    auto val_at_index = st.get(0);
    ASSERT_EQ(val_at_index, val_1);
    
    val_at_index = st.get(1);
    ASSERT_EQ(val_at_index, val_2);
}

TEST(BasicTests, Test3)
{
    storage st;
    
    const std::string val_1("bbb");
    st.insert(val_1);
    
    const std::string val_2("aaa");
    st.insert(val_2);
    
    auto val_at_index = st.get(0);
    ASSERT_EQ(val_at_index, val_2);
    
    val_at_index = st.get(1);
    ASSERT_EQ(val_at_index, val_1);
}

TEST(BasicTests, Test4)
{
    storage st(5);
    
    const std::string val_1("bbb");
    st.insert(val_1);//bbb
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_1);
    }
    
    const std::string val_2("aaa");
    st.insert(val_2);//aaa bbb
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    
    const std::string val_3("eee");
    st.insert(val_3);//aaa bbb eee
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    {
        auto val_at_index = st.get(2);
        ASSERT_EQ(val_at_index, val_3);
    }
    
    const std::string val_4("kkk");
    st.insert(val_4);//aaa bbb eee kkk
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    {
        auto val_at_index = st.get(2);
        ASSERT_EQ(val_at_index, val_3);
    }
    {
        auto val_at_index = st.get(3);
        ASSERT_EQ(val_at_index, val_4);
    }
    
    const std::string val_5("ddd");
    st.insert(val_5);//aaa bbb ddd eee kkk
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    {
        auto val_at_index = st.get(2);
        ASSERT_EQ(val_at_index, val_5);
    }
    {
        auto val_at_index = st.get(3);
        ASSERT_EQ(val_at_index, val_3);
    }
    {
        auto val_at_index = st.get(4);
        ASSERT_EQ(val_at_index, val_4);
    }
    
    const std::string val_6("fff");
    st.insert(val_6);//aaa bbb ddd eee fff kkk
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    {
        auto val_at_index = st.get(2);
        ASSERT_EQ(val_at_index, val_5);
    }
    {
        auto val_at_index = st.get(3);
        ASSERT_EQ(val_at_index, val_3);
    }
    {
        auto val_at_index = st.get(4);
        ASSERT_EQ(val_at_index, val_6);
    }
    {
        auto val_at_index = st.get(5);
        ASSERT_EQ(val_at_index, val_4);
    }
    
    const std::string val_7("ccc");
    st.insert(val_7);//aaa bbb ccc ddd eee fff kkk
    {
        auto val_at_index = st.get(0);
        ASSERT_EQ(val_at_index, val_2);
    }
    {
        auto val_at_index = st.get(1);
        ASSERT_EQ(val_at_index, val_1);
    }
    {
        auto val_at_index = st.get(2);
        ASSERT_EQ(val_at_index, val_7);
    }
    {
        auto val_at_index = st.get(3);
        ASSERT_EQ(val_at_index, val_5);
    }
    {
        auto val_at_index = st.get(4);
        ASSERT_EQ(val_at_index, val_3);
    }
    {
        auto val_at_index = st.get(5);
        ASSERT_EQ(val_at_index, val_6);
    }
    {
        auto val_at_index = st.get(6);
        ASSERT_EQ(val_at_index, val_4);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
