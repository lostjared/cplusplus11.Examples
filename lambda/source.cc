
// a very basic stack, with std::vector 

#include<iostream>
#include<exception>
#include<memory>
#include<vector>

class BoundsException : public std::exception {
public:
    virtual const char *what() const noexcept {
        return "Index is Out of bounds";
    }
};

template<typename T>
class Stack {
public:
    ~Stack() {
    }
    Stack(unsigned int size);
    Stack(Stack & s) = delete;
    void operator=(Stack &s) = delete;
    void push(T t);
    T &operator[](unsigned int pos);
    template<typename Type>
    void perform_operation(Type t) {
        for(unsigned int ii=0; ii<index; ++ii) {
            std::cout << "what is: " << buffer[ii] << "\n";
            std::cout << "proc value: " << t(buffer[ii]) << "\n";
        }
    }
    
private:
    std::vector<T> buffer;
    unsigned int size, index;
    
};

template<typename T>
Stack<T>::Stack(unsigned int sizex) : buffer(sizex) {
    size = sizex;
    index = 0;
}

template<typename T>
void Stack<T>::push(T t) {
    buffer.push_back(t);
    size = buffer.size();
    index = buffer.size();
}

template<typename T>
T &Stack<T>::operator[](unsigned int pos) {
    if(pos >= 0 && pos < index)
        return buffer[pos];
    else
        throw BoundsException();
}

int main(int argc, char **argv) {

    Stack<unsigned int> stack1(10);
    try {
        for(int i = 0; i < 10; ++i) {
            stack1.push(rand()%255);
        }
       
        // so point of this is the lambda 
        
        // one way
        stack1.perform_operation( [](unsigned int value) { 
            return value+5;
        });
        
        
        // another way to define it is:
        auto proc = [](unsigned int value) -> unsigned int {
            if(value > 0 && value <= 255)
            {
                std::cout << std::hex << value << "\n";
                return value%255;
            }
            return value;
        };
        stack1.perform_operation(proc);
        
        // so the basic point is add some items,
        // then each item is passed to a lambda 
        
        
    } catch (BoundsException &bounds ) {
        std::cerr << "Out of bounds exception: " << bounds.what() << "!\n";
        
    } catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Unknown Error\n";
    }


	return 0;
}

