#pragma once
class Time
{
public:
    Time(const char *func) : func(func)
    {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();
    }
    ~Time()
    {
        stop();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
    void stop()
    {
        auto start = std::chrono::time_point_cast<std::chrono::duration<long double, std::milli>>(m_StartTimePoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::duration<long double, std::milli>>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();

        auto dur = end - start;
        // string &&time = format("Function {}:- {}ms\n", func, dur);
        // clog.write(time.data(), time.size());
        STDerr.emplace_back(std::format("Function {}:- {:.5f}ms\n", func, dur));
    }
    const char *func;
};