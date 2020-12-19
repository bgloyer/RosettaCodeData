#include <algorithm>
#include <array>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <string_view>
#include <tuple>

#include <any>
#include <variant>

using namespace std;

std::variant<int, double> c = 3.4;

std::variant<int, std::initializer_list<int>> a = 3;
std::initializer_list<std::any> b = {3, 3.6};
//auto cdd = {3, "ddd"};
//std::variant<int, const std::initializer_list<int>> bb = {3, 3};

void dddd(int d)
{
}

void constexpr printNestedData(int i)
{
  //  cout << i;
}

void constexpr printNestedData(auto tuple);

// auto l3 = [&os](Ts const&... tupleArgs)
//         {
//             os << '[';
//             std::size_t n{0};
//             ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
//             os << ']';
//         }

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{0};
            ((os << tupleArgs << (++n != sizeof...(Ts) ? ", " : "")), ...);
            os << ']';
        }, theTuple
    );
    return os;
}

// auto mt(void)
// {
//     return make_tuple();
// }

// auto mt(int index)
// {
//    return make_tuple(index);
// }

auto mt(tuple<int> t1)
{
   return t1;
}

template<typename... T>
auto mt(T ... tpl)
{
    if constexpr(sizeof...(T) == 0)
    {
        return make_tuple();
    }
     else if constexpr(sizeof...(T) == 1)
    {
        return make_tuple(42);
    }
    else
    {
//    tuple_cat(make_tuple(mt(tpl)) ...);
      return make_tuple(tpl ...);
    }
}


void pp(const std::vector<const char*> &payloads, int index)
{
    cout << payloads[index] << " ";
}

template<typename... T>
void pp(const std::vector<const char*> &payloads, std::tuple<T...> const& theTuple)
{
    std::apply
    (
        [payloads](T const&... tupleArgs)
        {
            cout << "{ ";
            (pp(payloads, tupleArgs), ...);
            cout << "}\n";
        }, theTuple
    );
}



// auto l3 = [](Ts const&... tupleArgs)
//         {
//            printNestedData(Ts);
//            printNestedData(tupleArgs);
//         }
        
        
//auto lb = [](auto ...x){std::make_tuple(dddd(x)...);};
auto sdfsdf = [](auto ...x){std::make_tuple(x.do_something()...);};
//void constexpr printNestedData(auto tuple)
//{
  //  std::apply(lb , tuple);
//}

tuple<int, tuple< tuple<int, int>, int>> fn()
{
    return {1, {{2, 3}, 5}};
}
 

int main()
{

    vector payloads {"Payload#0", "Payload#1", "Payload#2", "Payload#3", "Payload#4", "Payload#5", "Payload#6"};
    
    auto q1 = mt(1);
    auto q2 = mt();
    auto q = mt({1});
    
    auto z = fn();
    
    cout << z;
    
    pp(payloads, z);
    
  //  printNestedData(z);
    
    std::initializer_list<std::initializer_list<int>> t = 
      {{1, 2},
          {3, 4, 1}, 
          {5}};

//auto tpl = make_tuple(make_tuple(1, 2), make_tuple(3, 4, 1), 5);

          
          
// constexpr std::initializer_list<std::any> a =
//       {{1, 2},
//        {3, 4, 1}, 
//      5};

  std::cout << "\n";
  return 0;
}
