#ifndef KQLOG_LOGGER_H
#define KQLOG_LOGGER_H

#include "common.h"
#include "formatter.h"
#include <ctime>

namespace kq
{
    enum class default_symbols : uint8_t
    {
        INFO,
        DEBUG,
        WARNING
    };

    enum class time_zone : uint8_t
    {
        UTC,
        LOCALTIME
    };


    template<typename T = default_symbols, typename C = char>
    class logger
    {
    public:
        using event_type = T;
        using encoding_type = C;

    public:
        logger();
        logger(const std::string& filename); // TODO: implement me
        logger(const logger& other); // TODO: implement me
        logger(logger&& other) noexcept; // TODO: implement me
        ~logger();

        logger& operator=(const logger& other); // TODO: implement me
        logger& operator=(logger& other); // TODO: implement me

        void set_time(time_zone tz);

        template<typename... Args>
        void out(event_type type, const std::string& fmt, Args&&... args)  
        { 
            std::time_t t = time(0);
            // yyyy-mm-dd time type function line
            // cout << format(fmt, std::forward<Args>(args)...); 
        }
        

    private:
        std::mutex m_mutex;
        std::ofstream m_file;
        time_zone m_time;

    public:
        std::string get_time();
        std::string month_to_string(const std::string&);
    };

    template<typename T, typename C>
    logger<T, C>::logger()
    {
        m_file.open("logs.txt",std::ofstream::out);
    }

    template<typename T, typename C>
    logger<T, C>::~logger()
    {
        
    }

    template<typename T, typename C>
    void logger<T, C>::set_time(time_zone tz)
    {
        m_time = tz;
    }

    template<typename T, typename C>
    std::string logger<T, C>::get_time()        
    {
        std::time_t t = time(0);
        std::string ret;
        ret.reserve(17);
        char *ugly_time;
        if(m_time == time_zone::UTC)
        {
            ugly_time = std::asctime(std::gmtime(&t));
        }
        else
        {
            ugly_time = std::asctime(std::localtime(&t));
        }
        std::string temp(ugly_time+20,ugly_time+24);
        ret += temp;
        temp.assign(ugly_time + 4, ugly_time + 7);
        std::string month_num = month_to_string(temp);
        ret += "/";
        ret += month_num;
        ret += "/";
        temp.assign(ugly_time+8,ugly_time+10);
        ret += temp;
        ret += " ";
        temp.assign(ugly_time+11, ugly_time+19);
        ret += temp;

        std::cout<<ugly_time<< '\n';
        return ret;
    }

    template<typename T, typename C>
    std::string logger<T, C>::month_to_string(const std::string& str)
    {
        if(str == "Ian")
            return "01";
        else if(str == "Feb")
            return "02";
        else if(str == "Mar")
            return "03";
        else if(str == "Apr")
            return "04";
        else if(str == "May")
            return "05";
        else if(str == "Jun")
            return "06";
        else if(str == "Jul")
            return "07";
        else if(str == "Aug")
            return "08";
        else if(str == "Sep")
            return "09";
        else if(str == "Oct")
            return "10";
        else if(str == "Nov")
            return "11";
        else if(str == "Dec")
            return "12";
        else throw std::runtime_error("Bad month code");
    }

} // namespace kq

#endif // KQLOGGER_