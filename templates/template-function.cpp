/* function templates example
   Jared Bruni
*/

#include<iostream>
#include<string>
#include<vector>

template<typename T>
void GrabData(T &x) {
    std::cin >> x;
}

int echoes = 0;

template<typename T>
void EchoData(T const &x) {
    std::cout << x;
    ++echoes;
}

template<typename It>
void EchoVector(std::ostream &out, It start, It stop) {
    for(It i = start; i < stop; ++i) {
        out << *i;
    }
}

template<typename T>
std::ostream &operator<<(std::ostream &out, std::vector<T> &v) {
    EchoVector(out, v.begin(), v.end());
    return out;
}

int main()
{
    const int x = 10;
    
    EchoData("Hello world Value: ");
    EchoData(x);
    EchoData("\nValues\n");
    
    int grab = 0;
    
    GrabData(grab);
    EchoData("Entered value: ");
    EchoData(grab);
    EchoData("\n");
    
    std::cout << "Echoed data: " << echoes << " times.\n";
    std::vector<std::string> echo_all {"hello ", "world ", "!"};
    EchoVector(std::cout, echo_all.begin(), echo_all.end());
    std::cout << "\nWith overloaded opreator<< ";
    std::cout << echo_all << "\n";
    return 0;
}



