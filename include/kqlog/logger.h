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
        WARNING,
        ERROR,
        CRITICAL
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
            using string_type   = std::conditional_t<std::is_same_v<C, char>, std::string, std::wstring>;

        public:
            time_info(const std::tm* time);
            time_info(const std::tm& time);

            string_type pretty_month(bool abbr) const;
            string_type pretty_day(bool abbr) const;

            template<typename I>
            string_type str_from_int(I convert) const noexcept;

        public:
            int sec;
            int min;
            int hour;
            int mday;
            int mon;
            int year;
            int wday;
    };

    template<typename C>
    time_info<C>::time_info(const std::tm* tm)
        : time_info(std::tm(*tm))
    {}

    template<typename C>
    time_info<C>::time_info(const std::tm& tm)
        : sec(tm.tm_sec), min(tm.tm_min), hour(tm.tm_hour), mday(tm.tm_mday), mon(tm.tm_mon + 1),
         year(tm.tm_year + 1900), wday(tm.tm_wday)
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

    template<typename C>
    typename time_info<C>::string_type time_info<C>::pretty_month(bool abbr) const
    {
        if(mon == 1) return abbr ? "Jan" : "January";
        else if(mon == 2) return abbr ? "Feb" : "February";
        else if(mon == 3) return abbr ? "Mar" : "March";
        else if(mon == 4) return abbr ? "Apr" : "April";
        else if(mon == 5) return "May";
        else if(mon == 6) return abbr ? "Jun" : "June";
        else if(mon == 7) return abbr ? "Jul" : "July";
        else if(mon == 8) return abbr ? "Aug" : "August";
        else if(mon == 9) return abbr ? "Sep" : "September";
        else if(mon == 10) return abbr ? "Oct" : "October";
        else if(mon == 11) return abbr ? "Nov" : " November";
        else return abbr ? "Dec" : "December";
    }
    
    template<typename C>
    typename time_info<C>::string_type time_info<C>::pretty_day(bool abbr) const
    {
        if(wday == 0) return abbr ? "Sun" : "Sunday";
        else if(wday == 1) return abbr ? "Mon" : "Monday";
        else if(wday == 2) return abbr ? "Tue" : "Tuesday";
        else if(wday == 3) return abbr ? "Wed" : "Wednesday";
        else if(wday == 4) return abbr ? "Thu" : "Thursday";
        else if(wday == 5) return abbr ? "Fri" : "Friday";
        else return abbr ? "Sat" : "Saturday";
    }

    template<typename T, typename C>
    class log
    {
        public:
            using event_type    = T;
            using encoding_type = C;
            using string_type   = std::conditional_t<std::is_same_v<encoding_type, char>, std::string, std::wstring>;
            using time_info     = time_info<encoding_type>;

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
        using event_type    = T;
        using encoding_type = C;
        using string_type   = std::conditional_t<std::is_same_v<encoding_type, char>, std::string, std::wstring>;
        using ofstream_type = std::conditional_t<std::is_same_v<encoding_type, char>, std::ofstream, std::wofstream>;
        using time_info     = time_info<encoding_type>;

    public:
        logger(const string_type& filename = "logs.txt", const string_type& directory = "output/", time_zone = time_zone::UTC);
        logger(const logger& other) = delete;
        logger(logger&& other) noexcept;
        ~logger();

        logger& operator=(const logger& other) = delete;
        logger& operator=(logger&& other); // add me

        void set_pattern(const string_type& new_pattern = "[{%Y}-{%M}-{%D} {%H}:{%N}:{%S}] [{%T}] [{%F}@{%L}] {%V}\n");
        void set_time(time_zone tz) noexcept;
        void set_filter(const std::vector<event_type>& toFilter, bool filterMode = true);
        void backup();

        template<typename... Args>
        void out(event_type type, const log<event_type, encoding_type>& msg, const std::experimental::source_location sl =
               std::experimental::source_location::current());

    private:
        std::mutex              m_mutex;
        ofstream_type           m_file;
        
        string_type             m_filename;
        string_type             m_directory;
        string_type             m_logpattern;
        string_type             m_realpattern;
        std::vector<event_type> m_tofilter;
        bool                    m_filterin; // 1 means filter IN, 0 means filter OUT
        time_zone               m_timezone;

        static std::unordered_map<C, string_type> s_flags;

    private:
        time_info get_time() const;
        string_type convert_pattern(string_type);
    };


    template<typename T, typename C>
    std::unordered_map<C, typename logger<T, C>::string_type> logger<T, C>::s_flags = {
        {'V',"0"},{'T',"1"},{'Y',"2"},{'M',"3"},{'m',"4"},{'b',"5"},{'D',"6"},{'d',"7"},
        {'B',"8"},{'H',"9"},{'N',"10"},{'S',"11"},{'t',"12"},{'L',"13"},{'F',"14"},{'s',"15"},
        {'%',"%"}
    };
    // {0}/{1}/{2} {3}:{4}:{5} [{6}] [{7}:{8}] [Thr {9}] | {10}\n

    template<typename T, typename C>
    logger<T, C>::logger(const string_type& filename, const string_type& directory, time_zone tz)
        :   m_mutex(), m_file(directory + filename, ofstream_type::out), m_filename(filename), m_directory(directory),
            m_logpattern("[{%Y}-{%M}-{%D} {%H}:{%N}:{%S}] [{%T}] [{%F}@{%L}] {%V}" ), m_realpattern("[{2}-{3}-{6} {9}:{10}:{11}] [{1}] [{14}@{13}] {0}"),
            m_tofilter(), m_filterin(), m_timezone(tz)
    {}

    template<typename T, typename C>
    logger<T, C>::logger(logger&& other) noexcept
        :   m_mutex(), m_file(std::move(other.m_file)),
            m_filename(std::move(other.m_filename)), m_directory(std::move(other.m_directory)),
            m_logpattern(std::move(other.m_logpattern)), m_realpattern(std::move(other.m_realpattern)),
            m_tofilter(std::move(other.m_tofilter)), m_filterin(other.m_filterin),m_timezone(other.m_timezone)
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
    void logger<T, C>::set_pattern(const string_type& new_pattern)
    {
        std::unique_lock lock(m_mutex);
        m_logpattern    = new_pattern;
        m_realpattern   = convert_pattern(m_logpattern);
    }

    template<typename T, typename C>
    void logger<T, C>::set_time(time_zone tz) noexcept
    {
        std::unique_lock lock(m_mutex);
        m_timezone = tz;
    }

    template<typename T, typename C>
    void logger<T, C>::set_filter(const std::vector<event_type>& toFilter, bool filterMode)
    {
        std::unique_lock lock(m_mutex);
        m_tofilter = toFilter;
        m_filterin = filterMode;
    }

    template<typename T, typename C>
    void logger<T, C>::backup()
    {
        std::unique_lock lock(m_mutex);
        static bool initialized = false;
        if(!initialized)
        {
            initialized = true;
            system((string_type("mkdir -p ") + m_directory + string_type("backup")).c_str());
        }
        m_file.close();
        time_info ti        = get_time();
        string_type year    = ti.str_from_int(ti.year);
        string_type month   = ti.str_from_int(ti.mon);
        string_type day     = ti.str_from_int(ti.mday);
        string_type hour    = ti.str_from_int(ti.hour);
        string_type minute  = ti.str_from_int(ti.min);
        string_type second  = ti.str_from_int(ti.sec);
        string_type backreturn = year +"-" + month + "-" + day + "_" + hour + ":" + minute + ":" + second;
        system((string_type("cp ") + m_directory + m_filename + string_type (" ") + m_directory
         + string_type("backup/") + backreturn + string_type("-") + m_filename ).c_str());
        m_file.open(m_directory + m_filename, ofstream_type::app);
    }

    template<typename T,typename C>
    template<typename... Args>
    void logger<T, C>::out(event_type _type, const log<event_type, encoding_type>& msg, 
    std::experimental::source_location sl)
    {
        std::unique_lock lock(m_mutex);
        time_info ti = get_time();
        const string_type& message      = msg.fmt();                    // flag: %V -> 0 
        std::string_view type           = magic_enum::enum_name(_type);  // flag: %T -> 1
        string_type years               = ti.str_from_int(ti.year);     // flag: %Y -> 2
        string_type months              = ti.str_from_int(ti.mon);      // flag: %M -> 3
        string_type pretty_full_month   = ti.pretty_month(false);       // flag: %m -> 4
        string_type pretty_abbr_month   = ti.pretty_month(true);        // flag: %b -> 5
        string_type days                = ti.str_from_int(ti.mday);     // flag: %D -> 6
        string_type pretty_full_day     = ti.pretty_day(false);         // flag: %d -> 7
        string_type pretty_abbr_day     = ti.pretty_day(true);          // flag: %B -> 8
        string_type hours               = ti.str_from_int(ti.hour);     // flag: %H -> 9
        string_type minutes             = ti.str_from_int(ti.min);      // flag: %N -> 10
        string_type seconds             = ti.str_from_int(ti.sec);      // flag: %S -> 11
        string_type thread              = ti.str_from_int(std::hash<std::thread::id>{}(std::this_thread::get_id())); // flag: %t -> 12
        string_type line                = ti.str_from_int(sl.line());   // flag: %L -> 13
        string_type function            = sl.function_name();           // flag: %F -> 14
        string_type source              = sl.file_name();               // flag: %s -> 15

        m_file << fmt::format(m_realpattern, message, type, years,
             months, pretty_full_month, pretty_abbr_month, days,
             pretty_full_day, pretty_abbr_day, hours, minutes,
             seconds, thread, line, function, source);

        // Check if the event_type has to be filtered out/in
        if(m_tofilter.size() > 0)
        {
            auto it = std::find(m_tofilter.begin(), m_tofilter.end(), _type);
           if(m_filterin)
           {
                if(it == m_tofilter.end())
                    return;
           }
           else
           {
                if(it != m_tofilter.end())
                    return;
           }
        }
        std::cout << fmt::format(m_realpattern, message, type, years,
             months, pretty_full_month, pretty_abbr_month, days,
             pretty_full_day, pretty_abbr_day, hours, minutes,
             seconds, thread, line, function, source);
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
    typename logger<T, C>::string_type logger<T, C>::convert_pattern(string_type logpattern)
    {
        int poz = 0;
        char aux;
        for(int i=0; i<logpattern.size(); ++i)
        {
            if(logpattern[i] == '{')
            {
                if(logpattern[i+1] == '%')
                {
                    aux = logpattern[i+2];
                    logpattern.erase(logpattern.begin()+i+1);
                    logpattern.erase(logpattern.begin()+i+1);
                    logpattern.insert(i+1, s_flags[aux]);
                }
            }
        }
        return logpattern;
    }

} // namespace kq

#endif // KQLOGGER_
