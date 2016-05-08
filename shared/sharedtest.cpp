#include<iostream>
#include<memory>
#include<cctype>
#include<vector>

// simple class to illustrate point
class Item {
public:
    Item(std::string text) : temp_text(text) {
    }
    ~Item() {
        std::cout << "Released: " << temp_text << "\n";
    }
    void lowerCase() {
        for(int i = 0; i < temp_text.length(); ++i)
            temp_text[i] = tolower(temp_text[i]);
    }
    std::string data() { return temp_text; }
private:
    std::string temp_text;
};

// uses shared_ptr
bool checkIfQuit(std::shared_ptr<Item> &item) {
    if(item->data() == "quit") return true;
    return false;
}


int main(int argc, char **argv) {
    // will autorelease Item on destructor using shared_ptr
    std::vector<std::shared_ptr<Item>> items;
    while(1) {
        std::string s;
        std::cout << "Enter string quit to exit loop: ";
        std::getline(std::cin, s);
        items.push_back(std::shared_ptr<Item>(new Item(s)));
        items[items.size()-1]->lowerCase();
        if(checkIfQuit(items[items.size()-1]) == true) break;
    }
    return 0;
}

