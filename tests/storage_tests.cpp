//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include "gtest/gtest.h"
#include "storage.h"

TEST(StorageTests, Test1)
{
    storage st;
    const std::string val("aaa");
    st.insert(val);
    auto val_at_index = st.get(0);
    ASSERT_EQ(val_at_index, val);
}

TEST(StorageTests, Test2)
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

TEST(StorageTests, Test3)
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

TEST(StorageTests, Test4)
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
