// // #include "CppUnitTest.h"
// #include "my_list.h"
// #include <list>
// #include <vector>


// namespace ListTests
// {
// class SimpleElem;
// }
// namespace ListTests
// {
// class NoCopyElem;
// }

// ;
// // ____________________________ ВАЖНО !!!____________________________;
// //  Для того, чтобы выполнить тестирование одного из указанных контейнеров
// //  (std::list или MyList), должна быть раскомментирована одна из следующих
// //  строк:
// template<typename T> using ContainerTemplate = std::list<T>;
// // template<typename T> using ContainerTemplate = MyList<T>;

// //; ____________________________ ТОЖЕ ВАЖНО!!! ____________________________;
// // Для проверки бонусного задания необходимо заменить SimpleElem на
// NoCopyElem using Elem = ListTests::SimpleElem;
// // using Elem = ListTests::NoCopyElem;


// using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// namespace ListTests
// {
// class SimpleElem
// {
//     uint32_t watch;
//     int data;
//     static size_t elem_counter;
//     void check() const
//     {
//         Assert::IsTrue(watch == 0xDEADBEEF,
//                        L"Повреждение памяти!! (Обращение к "
//                        L"неинициализированному экземпляру класса
//                        SimpleElem)");
//     }

// public:
//     SimpleElem(const SimpleElem& e) : data(e.data), watch(e.watch)
//     {
//         e.check();
//         ++elem_counter;
//     }
//     SimpleElem& operator=(const SimpleElem& e)
//     {
//         e.check();
//         data = e.data;
//         watch = e.watch;
//     }
//     explicit SimpleElem(int value) : data(value), watch(0xDEADBEEF)
//     {
//         ++elem_counter;
//     }
//     SimpleElem(SimpleElem&& e) noexcept
//     {
//         e.check();
//         data = e.data;
//         watch = e.watch;
//         ++elem_counter;
//     }
//     SimpleElem& operator=(SimpleElem&& e) noexcept
//     {
//         check();
//         e.check();
//         data = e.data;
//         watch = e.watch;
//     }
//     bool operator==(const SimpleElem& e) const
//     {
//         check();
//         e.check();
//         return data == e.data;
//     }
//     ~SimpleElem()
//     {
//         check();
//         watch = 0;
//         --elem_counter;
//     }
//     static size_t count() { return elem_counter; }
// };
// size_t SimpleElem::elem_counter = 0;

// class NoCopyElem
// {
//     uint32_t watch;
//     int data;
//     static size_t elem_counter;
//     void check() const
//     {
//         Assert::IsTrue(watch == 0xDEADDEAD,
//                        L"Повреждение памяти!! (Обращение к "
//                        L"неинициализированному экземпляру класса
//                        NoCopyElem)");
//     }

// public:
//     NoCopyElem(const NoCopyElem& e) = delete;
//     NoCopyElem& operator=(const NoCopyElem& e) = delete;
//     explicit NoCopyElem(int value) : data(value), watch(0xDEADDEAD)
//     {
//         ++elem_counter;
//     }
//     NoCopyElem(NoCopyElem&& e) noexcept
//     {
//         e.check();
//         data = e.data;
//         watch = e.watch;
//         ++elem_counter;
//     }
//     NoCopyElem& operator=(NoCopyElem&& e) noexcept
//     {
//         check();
//         e.check();
//         data = e.data;
//         watch = e.watch;
//     }
//     bool operator==(const NoCopyElem& e) const
//     {
//         check();
//         e.check();
//         return data == e.data;
//     }
//     ~NoCopyElem()
//     {
//         check();
//         watch = 0;
//         --elem_counter;
//     }
//     static size_t count() { return elem_counter; }
// };
// size_t NoCopyElem::elem_counter = 0;


// TEST_CLASS(ComplexTypeTests){

//     public :

//         TEST_METHOD(IteratorTests){
//             ContainerTemplate<int> list{3, 4, 8, 5, 2, 13, 20};
// list.push_back(10);
// Assert::IsTrue(list.end() == ++--list.end(),
//                L"++--list.end() должен возвращать list.end()");
// Assert::AreEqual(10, *(--list.end()),
//                  L"--list.end() должен возвращать последний элемент");
// } // namespace ListTests

// TEST_METHOD(StringTests)
// {
//     ContainerTemplate<std::string> list{"123", "AAAAAAAA", "abc", "cde"};
//     std::vector<std::string> expected1{"123", "AAAAAAAA", "abc", "cde"};

//     Assert::AreEqual(std::size_t(4), list.size(),
//                      L"Неправильно считается количество строковых
//                      элементов");
//     Assert::IsTrue(std::equal(list.begin(), list.end(), expected1.begin(),
//                               expected1.end()),
//                    L"Неправильный порядок строковых элементов");
//     Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected1.rbegin(),
//                               expected1.rend()),
//                    L"Неправильный порядок строковых элементов");

//     for (const auto& str : expected1)
//         list.erase(std::find(list.begin(), list.end(), str));

//     Assert::AreEqual(std::size_t(0), list.size(),
//                      L"Список не пуст после удаления всех элементов");
//     for (const auto& elem : list)
//         Assert::Fail(L"Что-то лежит в списке после удаления всех элементов");

//     list.push_back("test-1");
//     list.push_back("test-2");
//     list.push_back("test-4");
//     std::vector<std::string> expected2{"test-1", "test-2", "test-4"};
//     Assert::IsTrue(std::equal(list.begin(), list.end(), expected2.begin(),
//                               expected2.end()),
//                    L"Неправильный порядок строковых элементов");
//     Assert::IsTrue(std::equal(list.rbegin(), list.rend(), expected2.rbegin(),
//                               expected2.rend()),
//                    L"Неправильный порядок строковых элементов");
// }

// TEST_METHOD(ElemTests)
// {
//     size_t init_count = Elem::count();
//     {
//         ContainerTemplate<Elem> list;
//         Assert::AreEqual(std::size_t(0), Elem::count() - init_count,
//                          L"Создан лишний экземпляр класса Elem");

//         for (const auto& elem : list)
//             Assert::Fail(L"Что-то лежит в пустом списке");

//         list.push_back(Elem(40));
//         list.push_back(Elem(75));
//         list.push_front(Elem(50));
//         list.push_back(Elem(23));
//         list.push_back(Elem(87));
//         Assert::IsTrue(Elem::count() - init_count == 5,
//                        L"Создан лишний экземпляр класса Elem");

//         auto find_result = std::find(list.begin(), list.end(), Elem(75));
//         Assert::IsTrue(find_result != list.end(),
//                        L"Не найден элемент со значением 75");
//         Assert::IsTrue(*find_result == Elem(75),
//                        L"Неправильно найден элемент со значением 75");

//         list.erase(find_result);
//         Assert::IsTrue(Elem::count() - init_count == 4,
//                        L"Неправильно работает удаление элементов списка");
//     }
//     Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");
// }

// TEST_METHOD(CopyElemTests)
// {
//     size_t init_count = Elem::count();
//     {
//         ContainerTemplate<Elem> list;
//         {
//             ContainerTemplate<Elem> list1;
//             ContainerTemplate<Elem> list2(std::move(list1));
//             for (const auto& elem : list2)
//                 Assert::Fail(L"Что-то лежит в пустом списке после
//                 копирования");

//             list2.push_back(Elem(40));
//             list2.push_front(Elem(50));
//             list2.push_back(Elem(23));
//             list2.push_back(Elem(87));
//             Assert::IsTrue(Elem::count() - init_count == 4,
//                            L"Неправильно работает удаление элементов
//                            списка");
//             list = std::move(list2);
//         }
//         Assert::IsTrue(list.back() == Elem(87),
//                        L"Некправильно работает копирование списка");
//         Assert::IsTrue(Elem::count() - init_count == 4,
//                        L"Неправильно работает удаление элементов списка");
//     }
//     Assert::IsTrue(Elem::count() - init_count == 0, L"Утечка памяти!!");
// }

// // TODO: добавить тесты для всех реализованных методов
// }
// ;
// }
