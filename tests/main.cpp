#include "../include/kqlog.h"

enum Color: uint8_t
{
    Red,
    Green,
    Blue
};

int main()
{
    Color color = Red;
    auto name = magic_enum::enum_name(color);
    std::cout << name << "\n";
    std::cout << magic_enum::enum_count<Color>() << '\n';
    std::cout << sizeof(std::vector<std::string>) << " " << sizeof(std::string) << '\n';
    return 0;
    

}