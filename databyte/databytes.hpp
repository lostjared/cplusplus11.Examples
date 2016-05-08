#ifndef __DATA_BYTES_H__
#define __DATA_BYTES_H__

#include<iostream>
#include<vector>

template<typename T>
class DataByte {
public:
    
    DataByte() = default;
    
    DataByte(const DataByte<T> &t) {
        bytes = t.bytes;
        size_ = t.size_;
    }
    
    DataByte(DataByte<T> &&t) {
        bytes = std::move(t.bytes);
        size_ = t.size_;
    }
    
    DataByte<T> &operator=(const DataByte<T> &t) {
        bytes = t.bytes;
        size_ = t.size_;
        return *this;
    }
    
    DataByte<T> &operator=(DataByte<T>&& t) {
        bytes = std::move(t.bytes);
        size_ = t.size_;
        return *this;
    }
    
    DataByte(const T& value) {
        setAsBytes(value);
    }
    
    DataByte<T> &operator=(const T& type) {
        setAsBytes(type);
        return *this;
    }
    
    void setAsBytes(const T& value) {
        
        if(!bytes.empty())
            bytes.erase(bytes.begin(), bytes.end());
        
        unsigned char *v = (unsigned char *)&value;
        
        for(unsigned int i = 0; i < sizeof(value); ++i) {
            bytes.push_back(v[i]);
        }
        
        size_ = sizeof(value);
    }
    
    unsigned char &operator[](unsigned int index) {
        return bytes[index];
    }
    
    unsigned int size() {
        return size_;
    }
    
    
protected:
    std::vector<unsigned char> bytes;
    unsigned int size_;
};




#endif
