#include <vector>
#include <iostream>
#include "../include/core/object.hpp"
#include "../include/managers/table.hpp"
#include "../include/managers/file.hpp"

Table::Table(std::string _name) : file(_name + ".txt") {
    Table::name = _name;
    Table::file.readArchive();
}

int Table::findByKey(std::string _key, std::string _value) {
    for (int i = 0; i < Table::body.size(); i++) {
        if (Table::body[i].getExistenceBool(_key)) {
            if (Table::body[i].getValue(_key) == _value) {
                return i;
            }
        }
    }
    return -1;
}

void Table::setColumn(std::string _key, std::string _value) {
    Table::header.setItem(_key, _value);
}

void Table::setObject(Object _object) {
    if (_object.getExistenceBool("id")) {
        _object.updateItem("id", std::to_string(Table::body.size()));
    }
    Table::body.push_back(_object);
}

std::string Table::getName() {
    return Table::name;
}

Response<Object> Table::getObject(std::string _key, std::string _value) {
    for (int i = 0; i < Table::body.size(); i++) {
        if (Table::body[i].getExistenceBool(_key)) {
            if (Table::body[i].getValue(_key) == _value) {
                return Response(true, Table::body[i]);
            }
        }
    }
    return Response(false, Object());
}

bool Table::haveHeader() {
    return Table::file.getLine(0) != "" && Table::file.getLine(0) != " ";
}

void Table::print() {
    for (int i = 0; i < Table::header.getKeysCount(); i++) {
        std::string buffer_key = Table::header.getKeyFromId(i);
        std::cout << buffer_key << ' ';
    }
    std::cout << std::endl;

    for (int i = 0; i < Table::body.size(); i++) {
        for (int j = 0; j < Table::body[i].getKeysCount(); j++) {
            std::string buffer_key = Table::body[i].getKeyFromId(j);
            std::cout << buffer_key << ": " << Table::body[i].getValue(buffer_key) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Table::save() {
    std::string buffer_line;
    Table::file.clearLines();

    for (int i = 0; i < Table::header.getKeysCount(); i++) {
        std::string buffer_key = Table::header.getKeyFromId(i);
        buffer_line.append(Table::header.getValue(buffer_key));
        buffer_line.append(";");
        buffer_line.append(buffer_key);
        buffer_line.append(";");
    }
    Table::file.setLine(buffer_line);
    buffer_line.clear();

    for (int i = 0; i < Table::body.size(); i++) {
        for (int j = 0; j < Table::body[i].getKeysCount(); j++) {
            std::string buffer_key = Table::body[i].getKeyFromId(j);
            buffer_line.append(Table::body[i].getValue(buffer_key));
            buffer_line.append(";");
        }
        if (i < Table::body.size() - 1) {
            buffer_line.append("\n");
        }
    }
    Table::file.setLine(buffer_line);
}

void Table::load() {
    for (int i = 1; i < Table::file.getLinesCount(); i++) {
        Object buffer_object;
        buffer_object.loadDatabaseItems(Table::header, Table::file.getLine(i), ';');
        Table::setObject(buffer_object);
    }
}

void Table::loadDatabaseHeader() {
    std::string line = Table::file.getLine(0);
    if (!(line.empty() || line == " ")) {
        std::vector<int> buffer_delimeters;
        buffer_delimeters.reserve(Table::header.getKeysCount());
        std::string buffer_value;
        std::string buffer_key;

        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ';') {
                int buffer_pos = buffer_delimeters.size();
                buffer_delimeters.push_back(i);
            };
        }

        if (buffer_delimeters.size() >= 2) {
            buffer_key = line.substr(buffer_delimeters[0] + 1, buffer_delimeters[1] - buffer_delimeters[0] - 1);
            buffer_value = line.substr(0, buffer_delimeters[0]);
            Table::setColumn(buffer_key, buffer_value);
            buffer_value.clear();
            buffer_key.clear();
        }

        for (int i = 1; i < buffer_delimeters.size() - 1; i++) {
            if ((i + 1) < buffer_delimeters.size()) {
                if (buffer_value.empty()) {
                    buffer_value = line.substr(buffer_delimeters[i] + 1, buffer_delimeters[i + 1] - buffer_delimeters[i] - 1);
                } else {
                    buffer_key = line.substr(buffer_delimeters[i] + 1, buffer_delimeters[i + 1] - buffer_delimeters[i] - 1);
                    Table::setColumn(buffer_key, buffer_value);
                    buffer_value.clear();
                    buffer_key.clear();
                }
            }
        }
    }
}