#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "common_test.h"

int main(int argc, char* const argv[]) {
    int result = Catch::Session().run(argc, argv);
    std::cout << "Press enter to continue...";
    getch();
    return result;
}