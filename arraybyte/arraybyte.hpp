#ifndef __ARRAY_BYTE_H_
#define __ARRAY_BYTE_H_


template<typename T>
class ArrayByte {
public:
    ArrayByte() = default;
    
    ArrayByte(const T &type) {
        b.value = type;
    }
    
    ArrayByte(const ArrayByte<T> &a) {
        b = a.b;
    }
    
    ArrayByte(ArrayByte<T> &&) = delete;

    ArrayByte<T> &operator=(const ArrayByte<T> &a) {
        b = a.b;
        return *this;
    }
    
    ArrayByte<T> &operator=(const T &type) {
        b.value = type;
        return *this;
    }
    
    ArrayByte<T> operator=(ArrayByte<T> &&) = delete;
    
    unsigned char &operator[](unsigned int pos) {
        return b.bytes[pos];
    }
    
    unsigned int size() { return sizeof(T); }
    
protected:
    union {
        T value;
        unsigned char bytes[sizeof(T)];
    } b;
};



#endif
