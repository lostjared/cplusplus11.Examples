#ifndef __MXL__H__
#define __MXL__H__
/*
    MXL (MasterX Level)
    written by Jared Bruni (2015)
*/

#include "lexer.hpp"
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>

namespace mxl {
    
    using SortedVector = std::vector<std::pair<std::string, std::string>>;
    using Tags = std::unordered_map<std::string, std::string>;
    using namespace lex;
    
    class Parser_Error {
    public:
        Parser_Error(std::string text) {
            error = text;
        }
        
        void printError(std::ostream &out) {
            out << "Parser Error: " << error << "\n";
        }
        
        std::string getError() { return error; }
    protected:
        std::string error;
    };
    
    class MXLParser {
    public:
        MXLParser() = delete;
        MXLParser(std::istream &text, std::unordered_map<std::string, std::string> &map) : scan(text), pos(0), the_map{map} {}
        MXLParser(std::istream *text, std::unordered_map<std::string, std::string> &map
                  ) : scan(text), pos(0), the_map{map} {}
        
        void procTokens() {
            for(unsigned int i = 0; i < size(); ++i) {
                if(token_list[i].getTokenType() == TOKEN_CHAR && token_list[i].getToken() == "tag") {
                    pos = i;
                    total_text = at(i+1).getToken();
                    pos = procToken();
                    i = pos;
                }
            }
        }
        
        lex::Token &at(unsigned int i) {
            if(i < size()) {
                return token_list[i];
            }
            else
                throw Scanner_EOF();
            
        }
        
        unsigned int procToken() {
            
            ++pos;
            if(at(pos).getTokenType() != TOKEN_STRING) {
                throw Parser_Error("Looking for type string instead");
            }
            
            ++pos;
            
            if(at(pos).getTokenType() != TOKEN_OPERATOR) {
                throw Parser_Error("Looking for Opening {");
            }
            
            ++pos;
            
            while(at(pos).getToken() != "}") {
                std::string id, value;
                id =at(pos).getToken();
                if(id == "tag") {
                    total_text += "."+at(pos+1).getToken();
                    pos = procToken();
                    continue;
                }
                ++pos;
                if(pos > size() && at(pos).getToken() != "=") {
                    throw Parser_Error("Looking for = ");
                }
                ++pos;
                value=at(pos).getToken();
                ++pos;
                std::string addvalue=total_text+"."+id;
                if(id.find(".") == -1) {
                    the_map[addvalue] = value;
                } else {
                    the_map[id] = value;
                }
            }
            return pos;
        }
        
        unsigned int size() {
            return token_list.size();
        }
        
        void scanSource() {
            Token token;
            while(scan.valid()) {
                scan >> token;
                token_list.push_back(token);
            }
        }
        
        void outputTokens(std::ostream &out) {
            for(auto &i : the_map) {
                std::cout << i.first << " = " << i.second << "\n";
            }
        }
        
    protected:
        lex::Scanner scan;
        unsigned int pos;
        std::vector<Token> token_list;
        std::string total_text;
        std::unordered_map<std::string, std::string> &the_map;
        
    };
    
    bool parseSource(const std::string &filename, Tags &map) {
        std::fstream file;
        file.open(filename, std::ios::in);
        if(!file.is_open()) {
            std::cerr << "Error: file " << filename << " could not be found.\n";
            return false;
        }
        MXLParser parser(file, map);
        try {
            parser.scanSource();
            parser.procTokens();
        } catch(lex::Scanner_EOF) {
            
        } catch(Parser_Error &e) {
            file.close();
            e.printError(std::cerr);
            return false;
        }
        file.close();
        return true;
    }
    
    SortedVector createListFromMap(Tags &map) {
        SortedVector v;
        for(auto &i : map) {
            v.push_back(std::make_pair(i.first, i.second));
        }
        std::sort(v.begin(), v.end());
        return v;
    }
    
    bool tagExisits(const Tags &tags, const std::string &text) {
        for(auto &i : tags) {
            if(i.first == text) return true;
        }
        return false;
    }
    
    bool outputTagsToFile (const std::string &name, Tags &tag) {
        std::fstream file;
        file.open(name, std::ios::out);
        if(!file.is_open()) {
            std::cerr << "Could not open file:" <<name <<"\n";
            return false;
        }
        SortedVector v = createListFromMap(tag);
        for(auto &i : v) {
            int pos = i.first.rfind(".");
            if(pos != -1) {
                std::string tag = i.first.substr(0, pos);
                file << "tag \"" << tag << "\" { ";
                pos = i.first.rfind(".");
                if(pos != -1) {
                    std::string id = i.first.substr(pos+1, i.first.length()-pos);
                    file << "\"" << id << "\" = \"" << i.second << "\" }\n";
                }
            }
        }
        file.close();
        return true;
    }
    
    void addTag(Tags &tags, const std::string &tag_name, const std::string &text,const std::string &value) {
        tags[tag_name+"."+text] = value;
    }
    
    bool getTag(Tags &tag, const std::string &tag_name, const std::string &text, std::string &value) {
        std::string tag_n = tag_name+"."+text;
        if(tagExisits(tag, tag_n) == true) {
            value = tag[tag_n];
            return true;
        }
        return false;
    }
    
    class MXL_File_Error {
    public:
        MXL_File_Error(const std::string &text) : reason(text) {}
        void printError(std::ostream &out) {
            out << reason << "\n";
        }
        
        std::string getError() { return reason; }
    private:
        std::string reason;
    };
    
    class MXLFile {
    public:
        
        MXLFile() = default;
        
        MXLFile(const MXLFile &f) {
            tags = f.tags;
            filename_ = f.filename_;
        }
        
        MXLFile(MXLFile &&f) {
            tags = std::move(f.tags);
            filename_ = std::move(f.filename_);
        }
        
        MXLFile &operator=(const MXLFile &f) {
            tags = f.tags;
            filename_ = f.filename_;
            return *this;
        }
        
        MXLFile &operator=(MXLFile &&f) {
            tags = std::move(f.tags);
            filename_ = std::move(f.filename_);
            return *this;
        }
        
        MXLFile(const std::string &filename) : filename_(filename) {}
        
        bool parse() {
            if(filename_ != "")
                return parse(filename_);
            
            return false;
        }
        
        bool parse(const std::string &filename) {
            filename_ = filename;
            if(parseSource(filename, tags) != true) {
                throw MXL_File_Error("File "+filename_+": error");
                return false;
            }
            return true;
        }
        
        std::string &operator[](const std::string &text) {
            return tags[text];
        }
        
        std::string &operator()(const std::string &tag_name, const std::string &text) {
            return tags[tag_name+"."+text];
        }
        
        Tags::iterator begin() { return tags.begin(); }
        Tags::iterator end() { return tags.end(); }
        
        
        bool tag_Get(const std::string &tag_name,const std::string &text, std::string &value) {
            return getTag(tags, tag_name, text, value);
        }
        
        void tag_Set(const std::string &tag_name, const std::string &text, const std::string &value) {
            addTag(tags, tag_name, text, value);
        }
        
        bool tag_Exisits(const std::string &text) {
            return tagExisits(tags, text);
        }
        
        bool outputTags(const std::string &filename) {
            return outputTagsToFile(filename, tags);
        }
        
        void printTags(std::ostream &out) {
            for(auto &i : tags) {
                out << "Tag: \"" << i.first << "\" value = \"" << i.second << "\"\n";
            }
        }
        
        std::string fileName() { return filename_; }
        
    private:
        Tags tags;
        std::string filename_;
    };
}

#endif
