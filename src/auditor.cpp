#include "auditor.h"

bool Auditor::exist(const std::string& index){
    for(auto &i : audit){
        if(i  == index)
            return true;
    }
    return false;
}

void Auditor::addItem(Item& item){
    //Check if item already exists
    if(std::find(database.dataSave.begin(), database.dataSave.end(), ("`" + item.getIndex())) == std::end(database.dataSave)){
        //Find terminator
        auto it = std::find(database.dataSave.begin(), database.dataSave.end(), "`");
        std::deque<std::string>* temp;
        if(item.getContents(temp)){
            //Add index to temp
            temp->insert(temp->begin(), "`" + item.getIndex());
            temp->emplace_back("`");
            database.dataSave.erase(it);
            //Insert temp to database starting from terminator
            database.dataSave.insert(it, temp->begin(), temp->end());
            //Save database
            database.saveData(database.dataSave);
            //Add item to audit
            audit.emplace_back(item.getIndex());
            items.emplace_back(item);
        }
    }
}

bool Auditor::openItem(const std::string& index){
    Item temp{index};
    //Get item from database
    if(temp.readItem(temp.getIndex())){
        //Add captured item to audit 
        for(auto& i : audit){
            if(temp.getIndex() == i){
                std::cout << "Item already audited, no need to open\n";
                return true;
            }
        }
        items.emplace_back(temp);
        audit.emplace_back(index);
        return true;
    }
    else{
        //Error message
        std::cout << "The item \"" + index + "\" does not exist on the database\n";
        return false;
    }   
}

void Auditor::delItem(const std::string& index){
    //Get indexed item
    openItem(index);
    Item* temp;
    if(getItem(index, temp)){
        std::deque<std::string>* cont;
        if(temp->getContents(cont)){
            //Clear contents of item
            cont->clear();
            //Save empty item
            saveItem(*temp);
            for(long i = 0; i < database.dataSave.size(); ++i){
                //Find and delete empty index
                if(database.dataSave[i] == ("`" + index)){
                    database.dataSave.erase(database.dataSave.begin() + i);
                    //Save changes
                    database.saveData(database.dataSave);
                }
            }
        }
    }
}


void Auditor::saveItem(Item& item){
    long beg{0};
    long end{0};
    bool stopper = false;
    if(slib::fullOfSpace(item.getIndex())){
        return;
    }


    //index line number of item for next iterator
    for(long i = 0; i < database.dataSave.size();  ++i){
        //Check if index matches
        if((database.dataSave[i] == (std::string("`") + item.getIndex())) == 1){
            //Get beginning of contents
            //Add 1 to iterator to not include index to contents
            beg = (i + 1);
            for(++i; i < database.dataSave.size(); ++i){
                //Check if end of contents
                if(std::find(database.dataSave[i].begin(), database.dataSave[i].end(), '`') != database.dataSave[i].end()){
                    //Save to iterator end of contents
                    end = i;
                    stopper = true;
                    break;
                }
            }
        }
        else if(stopper)
            break;
    }
    //if successful erase old contents of item from database copy and insert new contents 
    //and save database copy to merge to data.txt
    if(stopper){
        std::deque<std::string>* temp;
        item.getContents(temp);
        database.dataSave.erase(database.dataSave.begin() + beg, database.dataSave.begin() + end);
        database.dataSave.insert(database.dataSave.begin() + beg, temp->begin(), temp->end());
        database.saveData(database.dataSave);
    }
}

void Auditor::loadAll(){
    for(long i; i < database.dataSave.size(); ++i){
        //Find if string is an index
        if(database.dataSave[i].find("`") != database.dataSave[i].npos){
            //Check if not terminator
            if(database.dataSave[i] != "`"){
                //add to audit
                openItem(database.dataSave[i].substr(1, std::string::npos));
            }
        }
    }
}

bool Auditor::getItem(const std::string& index, Item* &item){
    //loop through items list and check for index given and give pointer for item
    //return true if successful
    //return false if failed
    for(Item& i : items){
        if(i.getIndex() == index){
            item = &i;
            return true;
        };
    }
    return false;
}

bool Auditor::getAudit(std::deque<Item>*& audit){
    if(items.empty()){
        return false;
    }
    else{
        audit = &items;
        return true;
    }
}

Auditor& getAuditor(){
    static Auditor auditor;
    return auditor;
}