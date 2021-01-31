#include <iostream>
#include <map>
#include <utility>

using namespace std;

template<typename T>
class FixedMap : private T
{
    // Two standard maps are used to implement FixedMap.  One as a private
    // base class which will allow the values (but not the keys) to be modified.
    // Members of a private base class are not exposed to the derived class which will
    // prevent keys from being added or deleted. Another map will hold copies of
    // the initial values.
    T m_defaultValues;
    
public:
    FixedMap(T map)
    : T(map), m_defaultValues(move(map)){}
    
    // Expose members of the base class that are not able to add or remove keys so 
    // that FixedMap will behave like a standard container.
    using T::begin;
    using T::cbegin;
    using T::end;
    using T::cend;
    using T::at;
    using T::empty;
    using T::find;
    using T::size;
    
    // The [] operator will normally add a new key if the key is not already in the
    // map.  Instead, throw an error if the key is missing.
    auto& operator[](typename T::key_type key)
    {
        auto iterator = this->find(key);
        if(iterator == this->end()) throw out_of_range("key not found");
        return iterator->second;
    }
    
    // Reset the value of key to its initial value.  Thows an error
    // if the key is missing.
    void reset(typename T::key_type key)
    {
        T::operator[](key) = m_defaultValues.at(key);
    }
};

// Print the contents of a map
auto PrintMap = [](const auto &map)
{
    for(auto &[key, value] : map)
    {
        cout << "{" << key << " : " << value << "} ";
    }
    cout << "\n";
};

int main(void) 
{
    // Create a fixed map based on the standard map
    FixedMap<map<const char *, int>> fixedMap ({
        {"a", 1},
        {"b", 2}});
    PrintMap(fixedMap);
    
    // Change the values of the keys
    fixedMap["a"] = 55;
    fixedMap["b"] = 56;
    PrintMap(fixedMap);
    
    // Reset a key
    fixedMap.reset("a");
    PrintMap(fixedMap);
    
    try
    {
        // Adding or retrieving a missing key is a run time error
        fixedMap["newKey"] = 99;
    }
    catch (exception &ex)
    {
        cout << "error: " << ex.what();
    }
}
