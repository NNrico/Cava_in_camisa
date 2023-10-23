#include <algorithm>  
#include <string>  
#include <iostream>  
#include <vector>
  
using namespace std;  
   
int main()  
{  
    std::vector<int> s = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,8,8,8,8,9,9,9,9,10,10,10,10};
    sort(s.begin(), s.end());  

    
        std::cout << s.size() << std::endl;

    next_permutation(s.begin(), s.end());  

    s = {3,4,5};
    next_permutation(s.begin(), s.end());

    for (auto e : s) {
            std::cout << e << std::endl;
        }
        std::cout << "\n" << std::endl;
      
    return 0;  
}  