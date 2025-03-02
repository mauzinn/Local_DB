#include <string>
#include <iostream>
#include <vector>
#include "../include/utils/objectKey.hpp"
#include "../include/core/object.hpp"

int Object::findKeyId(std::string _key) {
    for (int i = 0; i < Object::values.size(); i++) {
        if (Object::values[i].keyMatch(_key)) {
            return i;
        }
    }

    return -1;
}

void Object::setItem(std::string _key, std::string _value) {
    if (!Object::getExistenceBool(_key)) {
        Object::values.push_back({_key, _value});
    }
}

void Object::loadDatabaseItems(Object _header, std::string _line, char _delimiter) {
    std::vector<int> position_delimiters;
    position_delimiters.reserve(_header.getKeysCount());

    for (int i = 0; i < _line.size(); i++) {
        if (_line[i] == _delimiter) {
            position_delimiters.push_back(i);
        }
    }

    Object::setItem(_header.getKeyFromId(0), _line.substr(0, position_delimiters[0]));

    for (int i = 0; i < position_delimiters.size() - 1; i++) {
        std::string buffer_result = _line.substr(position_delimiters[i] + 1, position_delimiters[i + 1] - position_delimiters[i] - 1);
        std::string buffer_key = _header.getKeyFromId(i + 1);
        Object::setItem(buffer_key, buffer_result);
    }
}

void Object::updateItem(std::string _key, std::string _new_value) {
    if (Object::getExistenceBool(_key)) {
        Object::values[Object::findKeyId(_key)].value = _new_value;
    }
}

std::string Object::getValue(std::string _key) {
    if (Object::getExistenceBool(_key)) {
        return Object::values[Object::findKeyId(_key)].value;
    }
    return " ";
}

bool Object::getExistenceBool(std::string _key) {
    int result = Object::findKeyId(_key);

    if (result == -1) {
        return false;
    }

    return true;
}

int Object::getKeysCount() {
    return Object::values.size();
}

std::string Object::getKeyFromId(int _id) {
    return Object::values[_id].key;
}