#include<iostream>
#include<vector>
#include<deque>
#include<string>

// template template parameter
template<typename T, template<typename E, typename = std::allocator<E>> class Container>
class Stack {
public:
    Stack() = default;
    
    void push(const T& type) {
        cont.push_back(type);
    }
    void pop() {
        cont.pop_back();
    }
    
    T top() { return cont[cont.size()-1]; }
    
    bool empty() { return cont.empty(); }
    
private:
    Container<T> cont;// here its using template template parameter
};

int main() {
    // using template template parameter passes std::vector
    Stack<int, std::vector> stack;
    for(unsigned int i = 0; i < 100; ++i) stack.push(i*i);
    // using template template paramter passes std::deque
    Stack<float, std::deque> dstack;
    for(unsigned int i = 0; i < 100; ++i) dstack.push(i*i*0.1f);
    
    while(!stack.empty()) {
        int value = stack.top();
        stack.pop();
        std::cout << "value: " << value << "\n";
    }
    while(!dstack.empty()) {
        float value = dstack.top();
        dstack.pop();
        std::cout << "Value: " << value << "\n";
    }
    return 0;
}