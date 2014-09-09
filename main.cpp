#include "function.hpp"
#include "bind.hpp"

class foo
{
public:
    void say()
    {
        std::cout << "foo say" << std::endl;
    }
};

int main()
{
    foo f1;
    cpptool::Function<void()> fun = cpptool::bind(&foo::say, &f1);
    fun();
    return 0;
}
