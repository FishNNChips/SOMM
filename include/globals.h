#pragma once
std::random_device R;
std::mt19937 device(R());
std::uniform_real_distribution<float> w(0, 1);
std::uniform_real_distribution<float> d(-10, 10);
std::uniform_int_distribution indices(10, 100);
struct out
{
    std::vector<std::string> buffers;
    bool mode;

    out(bool mode) : mode(mode) {}

    // void emplace_back(string &str) { buffers.emplace_back(str); }
    void emplace_back(std::string &&str) { buffers.emplace_back(str); }

    ~out() { flush_all(); }

private:
    void flush_all()
    {
        if (mode)
            for (const auto &buf : buffers)
                std::cout.write(buf.data(), buf.size());
        else
            for (const auto &buf : buffers)
                std::clog.write(buf.data(), buf.size());
    }

} STDout(true), STDerr(false);
// std::ofstream debug("debug.txt");
// //FILE *f1 = fopen("allocates.txt", "w");
// struct FileStream
// {
//     FileStream(std::ofstream &f) : file(f) {}
//     void emplace_back(std::string &&str) { buffers.emplace_back(str); }
//     ~FileStream() { flush_all(); }

// private:
//     std::ofstream &file;
//     std::vector<std::string> buffers;
//     void flush_all()
//     {
//         for (const auto &buf : buffers)
//             file.write(buf.data(), buf.size());
//         // fwrite(buf.data(), buf.size(), 1, f1);
//     }
// } F(debug);