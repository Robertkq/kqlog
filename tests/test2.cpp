#include "../include/kqlog.h"
#include "common_test.h"

TEST_CASE("Basic usage 2", "[Logger]")
{
    kq::logger logger{"test2_output.txt", "output/"};
    for(int i = 0; i < 10; ++i)
        logger.out(KQINFO, {"[2] This is a {1} and hopefully it {0}\n", "works", "test"});
}