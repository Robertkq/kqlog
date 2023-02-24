#include "../include/kqlog.h"





int main()
{
    kq::logger Logger("logs.txt", "output/");
    for(int i = 0; i < 10; ++i)
    {
        Logger.set_pattern("{%R}[{%Y}-{%M}-{%D}{%y} {%H}:{%N}:{%S}] {%G}[{%T}] {%E}[{%F}@{%L}] {%V}\n");
        Logger.out(KQINFO, {"{%C} {0:5} {%g}START", i + 10});
        Logger.set_pattern("{%y}[{%Y}-{%M}-{%D}{%G} {%H}:{%N}:{%S}] {%C}[{%T}] [{%F}@{%L}] {%V}\n");
        Logger.out(KQDEBUG, {"{%g} {0:5} {%R}CONTINUE", i + 10});
        Logger.set_pattern("{%G}[{%Y}-{%M}-{%D}{%C} {%H}:{%N}:{%S}] {%E}[{%T}] [{%F}@{%L}] {%V}\n");
        Logger.out(KQCRITICAL, {"{%R} {0:5} {%E}END", i + 10});
    }
    
    return 0;
}