#ifndef OBJECTKEY_HPP
#define OBJECTKEY_HPP

#include <string>

struct ObjectKey {
    std::string key, value;

    ObjectKey(std::string _key, std::string _value);
    bool keyMatch(std::string _other_key);
};

#endif