#pragma once
std::ofstream f1("allocates.txt");
std::ofstream f2("deallocates.txt");
void *operator new(std::size_t size)
{
    void *p = std::malloc(size);
    // auto st = std::stacktrace::current(3);
    f1 << "Allocating " << size << " bytes of memory at " << p << " in function " << __func__ << '\n';
    // F.emplace_back(format("Allocating {} bytes of memory at location {}\n", size, p));
    return p;
}
void operator delete(void *p) noexcept
{
    f2 << "Deallocating memory at " << p << '\n';
    std::free(p);
}
// void *operator new[](size_t size)
// {
//     // std::cout << "Allocating " << size << " bytes of memory" << std::endl;
//     void *ptr = malloc(size);
//     f1 << "Allocating " << size << " bytes of memory at " << ptr << " using new[]\n";
//     if (!ptr)
//         throw std::bad_alloc(); // Handle error if allocation fails
//     return ptr;
// }
// void operator delete[](void *p) throw()
// {
//     std::cout << "Deallocating array at " << p << std::endl;
//     std::free(p);
// }