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
<<<<<<< Updated upstream
    Logger.set_pattern("[{%Y}-{%M}-{%D}{%C} {%H}:{%N}:{%S}] [{%T}] [{%F}@{%L}] {%V}");
    for(int i = 0; i < 10; ++i)
    {
            Workload wl;
    }


=======
    std::cout << "\033[1;31m";
    std::cout << "Red Text\n";
    std::cout << "\033[1;31m";
    std::cout << "Red bold text";
    std::cout << "\033[0m\n";
>>>>>>> Stashed changes
    
    
    return 0;
}