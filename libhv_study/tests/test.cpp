//
// Created by lbb on 2022/12/22.
//

#include "test.h"

#include <gtest/gtest.h>
#include "requests.h"

using namespace  std;

int add (int a, int b) {
    return  a + b;
}



TEST(test_add, c1) {
    EXPECT_EQ(3, add(1, 2));
}

TEST(test_add,c2) {
    EXPECT_EQ(3, add(1, 2));
}





GTEST_API_ int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}