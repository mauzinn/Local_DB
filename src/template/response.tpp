#include "../../include/utils/response.hpp"

template <typename Data>
Response<Data>::Response(bool _success, Data _data) {
    Response::success = _success;
    Response::data = _data;
}