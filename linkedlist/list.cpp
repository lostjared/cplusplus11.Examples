// Been using C++ STL so long its about time I wrote a Linked List again.

#include<iostream>
#include<string>

template<typename T>
class Node {
public:
    T value;
    Node<T> *next;
    Node();
    Node(const T &value);
};

template<typename T>
Node<T>::Node() {
    next = 0;
    value = "";
}
template<typename T>
Node<T>::Node(const T &v) {
    value = v;
    next = 0;
}

template<typename T>
class List {
public:
    List();
    ~List();
    Node<T> first;
    void add(const T &value);
    bool remove(int index);
    void release(Node<T> *n);
    inline bool empty() const {
        return (first.next == 0) ? true : false;
    }
};

template<typename T>
List<T>::List() {
    
}

template<typename T>
List<T>::~List() {
    if(first.next != 0)
        release(first.next);
}
template<typename T>
void List<T>::release(Node<T> *n) {
    if(n->next != 0)
        release(n->next);
    
    delete n;
}

template<typename T>
void List<T>::add(const T &value) {
    Node<T> *n;
    for(n = &first; n->next != 0; n = n->next) {
        
    }
    n->next = new Node<T>(value);
}

template<typename T>
bool List<T>::remove(int index) {
    if(index == 0) {
        Node<T> *node;
        node = first.next;
        if(first.next != 0) {
            node = first.next;
            if(node->next != 0) {
            	first.next = node->next;
            	delete node;
                return true;
            } else {
                delete node;
                first.next = 0;
                return true;
            }
        }
    }
    int count = 0;
    Node<T> *n, *prev;
    Node<T> **lst = &first.next;
    prev = first.next;
    while((n = *lst) != 0) {
        if(count == index) {
            if(prev != 0) {
                prev->next = n->next;
                delete n;
                return true;
            }
        }
        prev = n;
        lst = &n->next;
        ++count;
    }
    return false;
}

template<typename T>
void echo_list(List<T> &list) {
    Node<std::string> *n = list.first.next;
    unsigned int index = 0;
    while(n != 0) {
        std::cout << "Index: " << index << " value: " << n->value << "\n";
        n = n->next;
        ++index;
    }
}

int main() {
    List<std::string> list;
    list.add("Hello");
    list.add("World");
    list.add("!");
    echo_list(list);
    list.remove(1);
    echo_list(list);
    List<std::string> list2;
    list2.add("Hey");
    list2.remove(0);
    echo_list(list2);
    return 0;
}
