//
// Created by johnathan on 02/06/18.
//

#include <googletest/googletest/include/gtest/gtest.h>
#include <Commons.h>

TEST(JoyAxis_Constructor, WhenDefaultBuilded_ShouldBeZero){
    JoyAxis joyAxis;

    EXPECT_EQ(joyAxis.axis[0], 0);
    EXPECT_EQ(joyAxis.axis[1], 0);
}
