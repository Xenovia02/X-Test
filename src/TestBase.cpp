#include "TestBase.hpp"

namespace xtst
{
    template<typename T>
    bool test_f<T>(const T& left, const T& right)
    {
        return left == right;
    }

    unsigned int TestBase::idt = 0;

    std::vector<buffer_t> TestBase::bstack { };

    std::vector<TestBase*> TestBase::tests { };

    bool TestBase::run_tests()
    {
        bool pass;
        for (auto test : tests)
        {
            pass &= test->run();
        }
        return pass;
    }

    void TestBase::register_buffer(buffer_t buf)
    {
        bstack.push_back(buf);
    }

    void TestBase::print_stack(const std::string& str)
    {
        for (buffer_t buf : bstack)
        {
            std::iostream s(buf);
            s << str;
            s.flush();
        }
    }

    template<typename ...Args>
    void TestBase::print(std::string str, Args... args)
    {
        str.insert(0, idt, '\t');
        for (std::size_t j = 0, k = 0; (str.find("~", j + k)) < str.size(); k = 2)
        {
            j = str.find("~", j + k);
            k = 2;
            switch (str[j + 1])
            {
                case '+': idt++; break;
                case '-': idt--; break;
                case '~': break;
                default: k = 1;
            }
            str.replace(j, k, std::string(idt, '\t'));
        }
        int size_s = std::snprintf(nullptr, 0, str.c_str(), args...) + 1;
        auto size = static_cast<std::size_t>(size_s);
        auto cstr = new char[size];
        std::snprintf(cstr, size, str.c_str(), args...);
        str = std::string(cstr);
        print_stack(str);
        delete[] cstr;
    }

    template<typename>
    void TestBase::print(std::string str)
    {
        str.insert(0, idt, '\t');
        for (std::size_t j = 0, k = 0; (str.find("~", j + k)) < str.size(); k = 2)
        {
            j = str.find("~", j + k);
            k = 2;
            switch (str[j + 1])
            {
                case '+': idt++; break;
                case '-': idt--; break;
                case '~': break;
                default: k = 1;
            }
            str.replace(j, k, std::string(idt, '\t'));
        }
        print_stack(str);
    }
}