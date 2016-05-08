/*
 
 delete and default
 
 */

#include<iostream>
#include<string>
#include<cstdlib>

namespace driver {
    class StringValue {
    public:
        StringValue() = default;
        StringValue(std::string text) : value{text} {
            std::cout << "String Value Created.\n";
        }
        StringValue(const StringValue &) = default;
        StringValue &operator=(const StringValue &) = delete;
        StringValue &operator=(StringValue &) = delete;
        const int integer() const { return atoi(value.c_str()); }
        void *operator new(size_t size) = delete;
    protected:
        std::string value;
        friend std::ostream &operator<<(std::ostream &, const StringValue &);
    };
            
    std::ostream &operator<<(std::ostream &out, const StringValue &val) {
        out << val.value << ": as Integer: " << val.integer() << " ";
        return out;
    }
    template<typename T>
    void output(T t) {
        std::cout << "output: " << t << "\n";
    }
            
    // will cause a error if T is const char *
    void output(const char *) = delete;
        
}
int main(int argc, char **argv) {
    using namespace driver;

    // uncomment and see it will error
    // output("test ");
    
    output<std::string>(std::string("hello world")); //ok
    output<int>(10); //ok
    output<StringValue>(StringValue("Hello world"));
    output<StringValue>(StringValue("30"));
    
    // explicitly deleted
    // output<StringValue*>(new StringValue("30"));
    
    return 0;
}