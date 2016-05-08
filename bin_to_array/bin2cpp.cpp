#include<iostream>
#include<string>
#include<fstream>
#include<cctype>

std::string convertFilename(const std::string &text) {
    std::string temp;
    for(unsigned int i = 0; i < text.length(); ++i) {
        if(text[i] == '.' || temp[i] == ' ')
            temp += '_';
        else if(isalpha(text[i]) || isdigit(text[i]))
            temp += text[i];
    }
    return temp;
}

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error requires one argument.\n" << argv[0] << " binarysource\n";
        return 0;
    }
    std::fstream file;
    file.open(argv[1], std::ios::in | std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 0;
    }
    std::string filename=argv[1];
    filename += ".h";
    
    std::fstream outfile;
    outfile.open(filename, std::ios::out);
    if(!outfile.is_open()) {
        std::cerr << "Could not open file: " << filename << "\n";
        file.close();
        return 0;
    }
    std::string filen = convertFilename(argv[1]);
    outfile << "#ifndef " << filen << "__H\n";
    outfile << "#define " << filen << "__H\n\n";
    outfile << "extern \"C\" {\n\n";
    outfile << "extern unsigned char " << filen << "[];\n";
    outfile << "\n}\n";
    outfile << "\n\n#endif\n";
    std::string filename_;
    filename_= argv[1];
    filename_+= ".cpp";
    outfile.close();
    outfile.open(filename_, std::ios::out);
    if(!outfile.is_open()) {
        std::cerr << "could not open file: " << filename_ << "\n";
        exit(0);
    }
    outfile << "#include\"" << filename << "\"\n\n";
    outfile << "\nunsigned char " << filen << "[] = {\n";
    file.seekg(0, std::ios::end);
    size_t len = file.tellg();
    file.seekg(0, std::ios::beg);
    char *buf = new char [len+1];
    file.read((char*)buf, len);
    file.close();
    for(unsigned int i = 0; i < len-1; ++i) {
        outfile << "0x" << std::hex << (unsigned int)(unsigned char)buf[i] << ", \n";
    }
    outfile << "0x" << std::hex << (unsigned int)(unsigned char)buf[len-1] << "};\n\n";
    outfile.close();
    delete [] buf;
    std::cout << "Variable name: " << filen << "\n";
    std::cout << "Outputed: " << filename << " and " << filename_ << "\n";
    return 0;
}

