#include "../include/kqlog.h"

kq::logger Logger("logs.txt", "output/");

struct Workload
{
    Workload() : my_id(_id++) { Start(); }
    void Start() 
    { 
        Logger.out(kq::default_symbols::INFO, {"{} Started\n", my_id});
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        Run(); 
    }
    void Run() 
    { 
        Logger.out(kq::default_symbols::INFO, {"{} Running\n", my_id});
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        Stop(); 
    }
    void Stop() 
    {
        Logger.out(kq::default_symbols::INFO, {"{} Stopped\n", my_id});
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
    };

    int my_id;
    static int _id;
};

int Workload::_id = 0;

int main()
{
    for(int i = 0; i < 10; ++i)
    {
            Workload wl;
    }
    
    return 0;
}