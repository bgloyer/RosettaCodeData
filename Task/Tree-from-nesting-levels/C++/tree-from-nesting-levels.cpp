#include <any>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

vector<any> MakeTree(input_iterator auto first, input_iterator auto last, int depth = 1)
{
    vector<any> tree;
    while (first < last && depth <= *first)
    {
        if(*first == depth)
        {
            tree.push_back(*first);
            ++first;
        }
        else // (depth < *b)
        {
            tree.push_back(MakeTree(first, last, depth + 1));
            first = find(first + 1, last, depth); 
        }
    }
        
    return tree;
}


void PrintTree(input_iterator auto first, input_iterator auto last)
{
    cout << "[";
    for(auto it = first; it != last; ++it)
    {
        if(it != first) cout << ", ";
        if(it->type() == typeid(unsigned int))
        {
            cout << any_cast<unsigned int>(*it);
        }
        else
        {
            const auto& subTree = any_cast<vector<any>>(*it);
            PrintTree(subTree.begin(), subTree.end());
        }
    }
    cout << "]";
}

int main(void) 
{

    auto execises = vector<vector<unsigned int>> {
        {},
        {1},
        {1, 1},
        {2},
        {2, 2},
        {3},
        {1, 2, 4},
        {3, 1, 3, 1},
        {1, 2, 3, 1},
        {3, 2, 1, 3},
        {3, 3, 3, 1, 1, 3, 3, 3},
        };
    
    for(const auto& e : execises)
    {
        auto tree = MakeTree(e.begin(), e.end());
        PrintTree(tree.begin(), tree.end());
        cout << "\n";
    }
    
}
