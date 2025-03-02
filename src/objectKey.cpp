#include <string>
#include "../include/utils/objectKey.hpp"

ObjectKey::ObjectKey(std::string _key, std::string _value) {
    ObjectKey::key = _key;
    ObjectKey::value = _value;
}

bool ObjectKey::keyMatch(std::string _other_key) {
    return ObjectKey::key == _other_key;
}