#ifndef RESPONSE_HPP
#define RESPONSE_HPP

template <typename Data>

struct Response {
    bool success;
    Data data;

    Response(bool _success, Data _data);
};

#include "../../src/template/response.tpp"

#endif