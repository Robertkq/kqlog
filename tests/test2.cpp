#include "../include/kqlog.h"
#include "common_test.h"

enum class myTypes
{
    Trade,
    Whisper,
    Duel,
    Announcement
};

TEST_CASE("Basic usage 2", "[Logger]")
{
    kq::logger<myTypes> logger{"test2_output.txt", "output/"};
    logger.set_pattern("[{%T}] [{%F}@{%L}] {%V}");
    for(int i = 0; i < 5; ++i)
    {
        logger.out(myTypes::Announcement, {"Mr. {}, joined the server.\n", i});
        logger.out(myTypes::Trade, {"Mr. {} traded with Mr. {}\n", i, i+1});
        logger.out(myTypes::Duel, {"Mr. {} challenged Mr. {} to a duel\n", i, i+1});
        logger.out(myTypes::Whisper, {"Mr. {} whispered to Mr. {}: {}\n", i, i+1, "gg"});
    }
}

TEST_CASE("Basic usage 2 check", "[Logger]")
{
    REQUIRE(compareFiles("output/test2_output.txt", "tests/test2_correct.txt"));
}