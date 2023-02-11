#include "../include/kqlog.h"

enum Color: uint8_t
{
    Red,
    Green,
    Blue
};

int main()
{
    kq::logger Logger;
    Logger.out(kq::default_symbols::INFO,"Robert");
    std::cout<<Logger.get_time();
    return 0;
    

}