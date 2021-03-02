#include "slib.h"

bool slib::isDigit(const std::string& word){
    for(char i : word){
        if(!isdigit(i)) 
            return false;
    }
    return true;
}

bool slib::isDigit(std::string_view view){
    for(char i : view){
        if(!isdigit(i))
            return false;
    }
    return true;
}

std::vector<std::string> slib::loadTxt(const std::string& filename){
    std::fstream file;
    std::vector<std::string> data;
	file.open(filename, std::fstream::in);
	std::string a;
	while (getline(file, a)) {
		data.push_back(a);
	}
	file.close();
	file.clear();
    return data;
}

bool slib::fullOfSpace(const std::string& str){
    for(auto& i : str){
        if(!(i == ' ' || i == '\t')){
            return false;
        }
    }
    return true;
}

std::string slib::removeSpace(const std::string& str){
    long firstchar{};
    for(long i = 0; i < str.size(); ++i){
        if(!(str[i] == ' ' || str[i] == '\t')){
            firstchar = i;
            break;
        }
    }
    if(firstchar){
        return str.substr(firstchar);
    }
    return str;
}

std::deque<std::string> slib::split_string_by_newline(const std::string& str){
    auto result = std::deque<std::string>{};
    auto ss = std::stringstream{str};

    for (std::string line; std::getline(ss, line, '\n');)
        if(!fullOfSpace(line))
            result.push_back(removeSpace(line));
    return result;
}
