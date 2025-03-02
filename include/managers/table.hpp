#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <iostream>
#include "../core/object.hpp"
#include "./file.hpp"
#include "../utils/response.hpp"

class Table {
    private:
    std::string name;
    File file;
    Object header;
    std::vector<Object> body;

    public:
    Table(std::string _name);
    
    int findByKey(std::string _key, std::string _value);

    void setColumn(std::string _key, std::string _value);
    void setObject(Object _object);

    std::string getName();
    Response<Object> getObject(std::string _key, std::string _value);
    bool haveHeader();

    void print();
    void save();
    void load();
    void loadDatabaseHeader();
};

#endif