#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <vector>
#include "../utils/objectKey.hpp"

class Object {
    private:
    std::vector<ObjectKey> values;

    int findKeyId(std::string _key);
    public:
    void loadDatabaseItems(Object _header, std::string _line, char _delimiter);
    
    void setItem(std::string _key, std::string _value);
    void updateItem(std::string _key, std::string _value);

    std::string getValue(std::string _key);
    bool getExistenceBool(std::string _key);
    int getKeysCount();
    std::string getKeyFromId(int _id);
};

#endif