#include "../include/kqlog.h"
#include "common_test.h"

TEST_CASE("Basic usage 1", "[Logger]")
{
    kq::logger logger{"test1_output.txt", "output/"};
    logger.set_pattern("[{%T}] [{%F}@{%L}] {%V}");
    for(int i = 0; i < 10; ++i)
    {
        // Do not modify the lines of .out calls
        logger.out(KQINFO, {"The {} just {}\n", "server", "started"});
        logger.out(KQDEBUG, {"Players are joining the {}\n", "server"});
        logger.out(KQCRITICAL, {"A player lost connection to the {}\n", "server"});
    }
}

TEST_CASE("Basic usage 1 check", "[Logger]")
{
    REQUIRE(compareFiles("output/test1_output.txt", "tests/test1_correct.txt"));
}