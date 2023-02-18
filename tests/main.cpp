#include "../include/kqlog.h"

kq::logger Logger("logs.txt", "output/");

struct Workload
{
    Workload() : my_id(_id++) { Start(); }
    void Start() 
    { 
        Logger.out(kq::default_symbols::INFO, {"{%y}{} {%R}Started\n", my_id});
        Run(); 
    }
    void Run() 
    { 
        Logger.out(kq::default_symbols::DEBUG, {"{} Running\n", my_id});
        Stop(); 
    }
    void Stop() 
    {
        Logger.out(kq::default_symbols::CRITICAL, {"{} Stopped\n", my_id});
    };

    int my_id;
    static int _id;
};

int Workload::_id = 0;

int main()
{
    Logger.set_pattern("[{%Y}-{%M}-{%D}{%C} {%H}:{%N}:{%S}] [{%T}] [{%F}@{%L}] {%V}");
    for(int i = 0; i < 10; ++i)
    {
            Workload wl;
    }


    
    
    return 0;
}