
/*
 * Persist Data Template
 * Auto-read/write data to memory
 * (C) 2012 Jared Bruni
 * License: GPL
 */

#ifndef PERSIST_H_
#define PERSIST_H_

#include<iostream>
#include<vector>
#include<fstream>
#include<string>

template<typename T>
class persist {
    T value;
public:
    typedef void (*Proc)(T &t);
    Proc write_x, read_x;
    
    explicit persist(T initial, Proc readFunction, Proc writeFunction) {
        read_x = readFunction;
        write_x = writeFunction;
        value = initial;
        read_x(value);
    }
    persist(const persist<T> &p) {
        value = p.value;
        read_x = p.read_x;
        write_x = p.write_x;
        read_x(value);
    }
    persist<T> &operator=(const persist<T> &p) {
        value = p.value;
        read_x = p.read_x;
        write_x = p.write_x;
        read_x(value);
        return (*this);
    }
    
    void setValue(T &t) { value = t; }
    T &getValue() const { return value; }
    
    ~persist() {
        write_x(value);
    }
    void resetRW(Proc save, Proc restore) {
        write_x = save;
        read_x = restore;
    }
    T &operator*() { return value; }
    T &get() { return value; }

    void swap(persist<T> &valuex) {
        T temp(value);
        value = valuex.getValue();
        valuex.setValue(temp);
    }
    
};

#endif


