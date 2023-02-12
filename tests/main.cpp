#include "../include/kqlog.h"

enum Color: uint8_t
{
    Red,
    Green,
    Blue
};

int main()
{
    kq::logger Logger("BIGTEST.txt");
    kq::logger Logger2(Logger);
    Logger2.set_time(kq::time_zone::UTC);
    Logger2.out(kq::default_symbols::INFO,"Robert");
    Logger2.out(kq::default_symbols::INFO, "Geroge");
    return 0;
    

}
