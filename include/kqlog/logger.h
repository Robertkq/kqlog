#ifndef KQLOG_LOGGER_H
#define KQLOG_LOGGER_H

#include "common.h"
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
        UTC = 0,
        LOCALTIME = 1
    };

    class UTC_CLOCK
    {
    public:
        std::tm* operator()() const noexcept 
        {
            std::time_t _time = time(0);
            return std::gmtime(&_time);
        }
    };

    class LOCALTIME_CLOCK
    {
    public:
        std::tm* operator()() const noexcept 
        {
            std::time_t _time = time(0);
            return std::localtime(&_time);
        }
    };

    template< typename C /* = char / wchar_t*/>
    class time_info
    {
        public:
            using encoding_type = C;
            using string_type = std::conditional_t<std::is_same_v<C, char>, std::string, std::wstring>;

        public:
            time_info(const std::tm* time);
            time_info(const std::tm& time);

            template<typename I>
            string_type str_from_int(I convert) const noexcept;

        public:
            int sec;
            int min;
            int hour;
            int mday;
            int mon;
            int year;
    };

    template<typename C>
    time_info<C>::time_info(const std::tm* tm)
        : time_info(std::tm(*tm))
    {}

    template<typename C>
    time_info<C>::time_info(const std::tm& tm)
        : sec(tm.tm_sec), min(tm.tm_min), hour(tm.tm_hour), mday(tm.tm_mday), mon(tm.tm_mon + 1), year(tm.tm_year + 1900)
    {}

    template<typename C>
    template<typename I>
    typename time_info<C>::string_type time_info<C>::str_from_int(I convert) const noexcept
    {
        string_type ret;
        if(convert < 0)
        {
            ret.push_back('-');
            convert = -1 * convert;
        }
        while(convert != 0)
        {
            ret.insert(ret.begin(), '0' + convert % 10);
            convert /= 10;
        }
        while(ret.size() < 2)
        {
            ret.insert(ret.begin(), '0');
        }
        ret.shrink_to_fit();
        return ret;
    }

    template<typename T, typename C>
    class log
    {
        public:
            using event_type = T;
            using encoding_type = C;
            using string_type = std::conditional_t<std::is_same_v<encoding_type, char>, std::string, std::wstring>;
            using time_info = time_info<encoding_type>;

        public:
            template<typename... Args>
            log(const string_type& fmt, Args&&... args);

            string_type& fmt() { return m_fmt; }
            const string_type& fmt() const { return m_fmt; } 

        private:
            string_type m_fmt;    
    };

    template<typename T, typename C>
    template<typename... Args>
    log<T, C>::log(const string_type& fmt, Args&&... args)
        : m_fmt(fmt::format(fmt, std::forward<Args>(args)...))
    {}

    template<typename T = default_symbols, typename C = char>
    class logger
    {
    public:
        using event_type = T;
        using encoding_type = C;
        using string_type = std::conditional_t<std::is_same_v<encoding_type, char>, std::string, std::wstring>;
        using ofstream_type = std::conditional_t<std::is_same_v<encoding_type, char>, std::ofstream, std::wofstream>;
        using time_info = time_info<encoding_type>;

    public:
        logger(const string_type& filename = "logs.txt", const string_type& directory = "output/", time_zone = time_zone::UTC);
        logger(const logger& other) = delete;
        logger(logger&& other) noexcept;
        ~logger();

        logger& operator=(const logger& other) = delete;
        logger& operator=(logger&& other); // add me

        void set_pattern(const string_type& new_pattern);
        void set_time(time_zone tz) noexcept;
        void backup();

        template<typename... Args>
        void out(event_type type, const log<event_type, encoding_type>& msg, const std::experimental::source_location sl =
               std::experimental::source_location::current());

    private:
        std::mutex m_mutex;
        ofstream_type m_file;
        
        string_type m_filename;
        string_type m_directory;
        string_type m_logpattern;

        time_zone m_timezone;

    private:
        time_info get_time() const;
        string_type month_to_string(const string_type&);
    };

    template<typename T, typename C>
    logger<T, C>::logger(const string_type& filename, const string_type& directory, time_zone tz)
        : m_mutex(), m_file(directory + filename, ofstream_type::out), m_filename(filename), m_directory(directory),
          m_logpattern("{0}/{1}/{2} {3}:{4}:{5} [{6}] [{7}:{8}] [Thr{9}] | {10}\n"), m_timezone(tz)
    {}

    template<typename T, typename C>
    logger<T, C>::logger(logger&& other) noexcept
        : m_mutex(), m_file(std::move(other.m_file)),
         m_filename(std::move(other.m_filename)), m_directory(std::move(other.m_directory)),
         m_timezone(other.m_timezone)
    {
        std::unique_lock lock(other.m_mutex);
        //other.m_file.close();
    }

    template<typename T, typename C>
    logger<T, C>::~logger()
    {
        std::unique_lock lock(m_mutex);
    }

    template<typename T, typename C>
    void logger<T, C>::set_time(time_zone tz) noexcept
    {
        m_timezone = tz;
    }

    template<typename T, typename C>
    void logger<T, C>::backup()
    {
        m_file.close();
        string_type info = get_time();
        info[10] = '-';
        info[4] = ':';
        info[7] = ':';
        system((string_type("mkdir ") + m_directory + string_type("backup/")).c_str());
        system((string_type("cp ") + m_directory + m_filename + string_type (" ") + m_directory
         + string_type("backup/") + info + string_type("-") + m_filename ).c_str());
        m_file.open(m_directory + m_filename, ofstream_type::app);
    }

    template<typename T,typename C>
    template<typename... Args>
    void logger<T, C>::out(event_type type, const log<event_type, encoding_type>& msg, 
    std::experimental::source_location sl)
    {
        time_info ti = get_time();
        string_type my_years = ti.str_from_int(ti.year); // id 0
        string_type my_months = ti.str_from_int(ti.mon); // id 1
        string_type my_days = ti.str_from_int(ti.mday); // id 2
        string_type my_hours = ti.str_from_int(ti.hour); // id 3
        string_type my_minutes = ti.str_from_int(ti.min); // id 4
        string_type my_seconds = ti.str_from_int(ti.sec); // id 5
        std::string_view my_type = magic_enum::enum_name(type); // id 6
        string_type my_function = sl.function_name(); // id 7
        string_type my_line = ti.str_from_int(sl.line()); // id 8
        string_type my_thread = ti.str_from_int(std::hash<std::thread::id>{}(std::this_thread::get_id())); // 9
        const string_type& my_message = msg.fmt(); // id 10

        m_file << fmt::format(m_logpattern, my_years, my_months, my_days,
            my_hours, my_minutes, my_seconds, my_type, my_function, my_line,
            my_thread, my_message);

        std::cout << fmt::format(m_logpattern, my_years, my_months, my_days,
            my_hours, my_minutes, my_seconds, my_type, my_function, my_line,
            my_thread, my_message);
    }

    template<typename T, typename C>
    typename logger<T, C>::time_info logger<T, C>::get_time() const
    {
        std::tm* ret = nullptr;
        if(m_timezone == time_zone::UTC)
            ret = UTC_CLOCK{}();
        else
            ret = LOCALTIME_CLOCK{}();
        time_info _time(ret);
        return _time;
    }

    template<typename T, typename C>
    typename logger<T, C>::string_type logger<T, C>::month_to_string(const string_type& str)
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
