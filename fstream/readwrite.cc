/* 
 
 Example for reading/writing to a file in binary mode
 
 run the application with the following arguments
 
 ./readwrite-test -o fileoutput.txt
 
 enter variables, and it will write to file
 
 ./readwrite-test -r fileoputut.txt
 
 will output the variables written to the file
 
 
 http://objective-c.info
 
 */

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>

// a example struct to read/write in binary mode
typedef struct writeStruct {
    int x,y,z;
    char value[256];
    writeStruct() = default;
    writeStruct(int cx, int cy, int cz, const char *cvalue) {
        x = cx, y = cy, z = cz;
        strncpy(value, cvalue, 255);
    }
} theStruct;

int main(int argc, char **argv) {
    
    // write to binary file
    if(argc == 3 && std::string(argv[1]) == "-o") {
    
        int cx = 0,cy = 0,cz = 0;
        std::string value;
        
        std::cout << "enter x y z: ";
        std::cin >> cx >> cy >> cz;
        std::cout << "enter string: ";
        std::cin >> value;
        
        theStruct s(cx,cy,cz,value.c_str());
        
        std::fstream file;
        file.open(argv[2], std::ios::out | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error could not open file.\n";
            return -1;
        }
        
        file.write(reinterpret_cast<char*>(&s), sizeof(s));
        file.close();
        std::cout << "Wrote to file " << argv[2] << " as binary.\n";
        return 0;
    }
    
    // read from binary file
    if(argc == 3 && std::string(argv[1]) == "-r") {
        theStruct s;
        std::fstream file;
        file.open(argv[2], std::ios::in | std::ios::binary);
        if(!file.is_open()) {
            std::cerr << "Error could not open file.\n";
            return -1;
        }
        file.read(reinterpret_cast<char*>(&s), sizeof(s));
        file.close();
        std::cout << "Read from file: \n";
        std::cout << s.x << " " << s.y << " " << s.z << "\n";
        std::cout << "string: " << s.value << "\n";
        return 0;
    }
    
    std::cout << "Enter " << argv[0] << "\n -o to output file\n -r to read file.\n";
    
    return 0;
}

