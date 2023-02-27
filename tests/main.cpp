#include "../include/kqlog.h"


int main()
{
    kq::logger logger("test.txt", "");
    logger.out( KQINFO, { "{} is a nice {}\n", "Today", "day" } );
    
    return 0;
}