#ifndef __MEM_FILE_H__
#define __MEM_FILE_H__

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

namespace mem {

    
    bool binOutputArray(const std::string &filename, const void *buf, unsigned long len) {
        std::fstream file;
        file.open(filename, std::ios::out | std::ios::binary);
        if(!file.is_open()) return false;
        file.write((char*)buf, len);
        file.close();
        return true;
    }
    
    
    class MemFile {
    public:
        MemFile() = default;
        MemFile(const MemFile &f) = delete;
        MemFile &operator=(const MemFile &f) = delete;
        MemFile &operator=(MemFile &&f) = delete;
        MemFile(MemFile &&f) = delete;
        
        bool open(const std::string &filename) {
            mode = 0;
            _memory = nullptr;
            _size = 0;
            _open = false;
            file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
            if(!file.is_open())
                return false;
        
            file.seekg(0, std::ios::end);
            _size = file.tellg();
            file.seekg(0, std::ios::beg);
            
            _open = true;
            offset = 0;
            return true;
        }
        
        bool is_open() const { return _open; }
       
        bool eof() {
            if(mode == 0) return file.eof();
            return (offset > _size);
        }
        
        bool open(void *mem, unsigned long size) {
            mode = 1;
            _memory = mem;
            _size = size;
            _open = true;
            offset = 0;
            return true;
        }
        
        unsigned long read(void *buf, unsigned long size) {
            if(mode == 0) {
                file.read((char*)buf, size);
                return file.gcount();
            } else {
                memcpy(buf, ((char*)_memory+offset), size);
                offset += size;
                return size;
            }
            return 0;
        }
        
        void write(void *buf, unsigned long size) {
            if(mode == 0) {
                file.write((char*)buf, size);
            } else {
                memcpy(((char*)_memory+offset), buf, size);
                offset += size;
            }
        }
        
        void seek_beg(unsigned long offset_) {
            if(mode == 1) offset = offset_;
            else
            file.seekg(offset, std::ios::beg);
        }
        
        void seek_cur(unsigned long offset_) {
            if(mode == 1) offset += offset_;
            else
                file.seekg(offset, std::ios::cur);
        }
        
        void rewind() {
            if(mode == 1)offset = 0;
            else file.seekg(0, std::ios::beg);
        }
        
        void close() {
            if(mode == 0) {
                file.close();
                _open = false;
            }
            else if(mode == 1) {
                _memory = nullptr;
                _size = 0;
                _open = false;
            }
        }
    protected:
        void *_memory;
        unsigned long _size,offset;
        std::fstream file;
        bool _open;
        int mode;
    };
}

#endif
