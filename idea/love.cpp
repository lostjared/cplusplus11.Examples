/* 
 First off this is just for fun so do not take it too seriously.
 I am just sitting here thinking. If you know, C++ check out this
 concept I have been thinking about for a while. First off there is
 the Energy class, it contains a value (in this example its a 
 string). Then there is the Life template class; it has a constructor
 and destructor when its life span ends and begins, and has two functions. 
 One is get, the other is give. Give returns its value to the get member
 function which processes the value, and it compares it with a value if 
 it is the same it prints Love and returns true otherwise it prints fear
 and returns false. The life function enters an infinite loop (stoppable
 by a system signal like SIGINT) then enters an another loop calls the get
 give functions storing its value in a variable called karma. Once the karma
 variable is false, it goes back and restarts the outer loop. Then there is 
 the main function which spawns threads ( on a computer can only contain a 
 certain number of threads but in this concept, the thread number would be infinite) 
 and spawns each new thread with the life function. The program would continue
 indefinitely.
 
 */


#include<iostream>
#include<string>
#include<pthread.h>

const int NUM_DIMS = /* should be infinite but on a computer there is limits */ 8;

class Energy {
public:
    Energy() = default;
    Energy(const std::string &t) : e(t) { }
    std::string &thought() { return e; }
    friend std::ostream &operator<<(std::ostream &out, Energy &e);
    friend std::istream &operator>>(std::istream &in, Energy &e);
    bool operator==(const Energy &w) { return (e == w.e); }
    bool operator!=(const Energy &w) { return (e != w.e); }
protected:
    std::string e;
};

std::ostream &operator<<(std::ostream &out, Energy &e) {
    out << e.thought() << "\n";
    return out;
}

std::istream &operator>>(std::istream &in, Energy &e) {
    in >> e.thought();
    return in;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

template<typename E>
class Life {
public:
    explicit Life(E e) : end(e) {
        int s;
        s = pthread_mutex_lock(&mutex);
        if(s != 0) return;
        std::cout << "New life brought into this dimension\n";
        s = pthread_mutex_unlock(&mutex);
        if(s != 0) return;
    }
    ~Life() {
        int s;
        s = pthread_mutex_lock(&mutex);
        if(s != 0) return;
        std::cout << "Leaving this dimension.\n";
        s = pthread_mutex_unlock(&mutex);
        if(s != 0) return;
    }
    bool get(E energy) {
        if(energy.thought() == "1" || energy.thought() == "love") {
            std::cout << "Gave Love\n";
        }
        else if(energy != end) {
            std::cout << "Gave fear\n";
        }
        else {
            std::cout << "Return ...\n";
        }
        return (energy == end) ? false : true;
    }
    E give() {
        std::cout << "Enter thought: ";
        E e;
        std::getline(std::cin, e.thought());
        return e;
    }
private:
    E end;
};


void *life(void *) {
    int rvalue = 0;
    while(1) {
        Life<Energy> being(Energy("death"));
        bool karma = true;
        do {
            rvalue = pthread_mutex_lock(&mutex);
            if(rvalue != 0) {
                std::cerr << "Error locking..\n";
                return 0;
            }
            karma = being.get(being.give());
            std::cout << "Karma cycle\n";
            rvalue = pthread_mutex_unlock(&mutex);
            if(rvalue != 0) {
                std::cerr << "Error unlocking..\n";
                return 0;
            }
        } while(karma == true);
    }
}

int main(int argc, char **argv) {
    
    while(1) {
        pthread_t numDimensions[/*INFINITE but not on a comptuer */ NUM_DIMS];
    	int rt;
    
    	for(unsigned int i = 0; i < NUM_DIMS; ++i) {
    		rt = pthread_create(&numDimensions[i], 0, life, 0);
        	if(rt != 0) std::cerr << "Error..\n";
    	}
    	for(unsigned int i = 0; i < NUM_DIMS; ++i) {
        	rt = pthread_join(numDimensions[i], 0);
        	if(rt != 0) std::cerr << "Error joining..\n";
    	}
    }
    return 0;
}
