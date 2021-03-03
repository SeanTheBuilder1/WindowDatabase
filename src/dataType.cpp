#include "dataType.h"



bool Item::readItem(std::string index){
    std::deque<std::string> temp;
    //Loop database
    for(long i = 0; i < database.dataSave.size(); ++i){
        //If index is right
        if(database.dataSave[i] == (std::string("`") + index)){
            //Restart loop at i + 1
            for(++i; i < database.dataSave.size(); ++i){
                //If captured string is next index end loop
                if(std::find(database.dataSave[i].begin(), database.dataSave[i].end(), '`') != database.dataSave[i].end()){
                    contents = temp;
                    return true;
                }
                temp.emplace_back(database.dataSave[i]);
            }
            break;
        }
    }
    return false;
}

void Item::editItem(long index, const std::string& replacement){
    assert(index < contents.size());
    contents[index] = replacement;
}

bool Item::getContents(std::deque<std::string>*& data){
    //return true if successful and not nullptr
    //return false if failed
    if(&contents != nullptr){
        data = &contents;
        return true;
    }
    else{
        return false;
    }
}

void Item::sort(){
    std::sort(contents.begin(), contents.end());
}

void Item::sort(std::function<bool(std::string, std::string)> func){
    std::sort(contents.begin(), contents.end(), func);
}

void Item::sort(std::deque<std::string>::iterator x, std::deque<std::string>::iterator y){
    std::sort(x, y);
}
void Item::sort(std::deque<std::string>::iterator x, std::deque<std::string>::iterator y, std::function<bool(std::string, std::string)> func){
    std::sort(x, y, func);
}




std::string Item::getIndex(){
    return index;
}