//
// Some Thoughts
// written by Jared Bruni
// http://lostsidedead.com

#include<iostream>
#include<string>

template<typename T>
class Thought {
public:
    Thought() = default;
    Thought(const T msg) : message {msg} {}
    const T &str() const { return message; }
private:
    T message;
};

template<typename T>
bool checkIfQuit(T t) {
    return false;
}

bool checkIfQuit(std::string t) {
    if(t=="quit") return true;
    return false;
}

template<typename T>
bool get(Thought<T> &t) {
    // process
    if(checkIfQuit(t.str()) == true) return false;
    return true;
}

template<typename T>
Thought<T> &give(Thought<T> &t) {
    T token;
    std::cin >> token;
    t = Thought<T>(token);
    return t;
}

template<typename T>
void change(Thought<T> &t) {
    std::cout << "Karma returns: " << t.str() << "\n";
}

int main(int argc, char **argv)
{
    Thought<std::string> thought;
    while (get(give(thought))) change(thought);
    return 0;
}

