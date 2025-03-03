#include "my_list.h"
#include <iostream>
#include <list>
#include <print>



int main(int argc, char** argv)
{
    MyList<int> list;
    list.insert(list.end(), 2);

    for (const auto& x : list) std::println("{}", x);

    //  std::println("{}", lst.count_positive());
    //  std::list<int> list;

    // auto p = lst.split();

    // for (const auto& x : p.first) std::println("{}", x);
    // for (const auto& x : p.second) std::println("{}", x);




    // Тут надо сравнить работу своего контейнера со стандартным

    // Ещё можно проверять работоспособность методов, но для
    // каждого метода надо описать тест в проекте с тестами
}
