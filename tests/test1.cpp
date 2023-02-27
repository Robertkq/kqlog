#include "../include/kqlog.h"
#include "common_test.h"

TEST_CASE("Basic usage 1", "[Logger]")
{
    kq::logger logger{"test1_output.txt", "output/"};
    for(int i = 0; i < 10; ++i)
        logger.out(KQINFO, {"[1] This is a {1} and hopefully it {0}\n", "works", "test"});
}

TEST_CASE("Basic usage 1 check", "[Logger]")
{
    std::cout << "Check Check 1\n";
    REQUIRE(compareFiles("output/test1_output.txt", "tests/test1_correct.txt"));
}