#include <iostream>
#include "../include/kqlog.h"

kq::logger Logger("logs.txt", "output/", kq::time_zone::UTC);

int main()
{
    Logger.out(kq::default_symbols::INFO, {"Started {}", "Server"});
    
    
    return 0;
}