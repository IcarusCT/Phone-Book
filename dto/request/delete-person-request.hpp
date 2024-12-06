//
// Created by elif on 12/5/24.
//

#ifndef DELETE_PERSON_REQUEST_HPP
#define DELETE_PERSON_REQUEST_HPP
#include <string>
#include <crow.h>
#include <nlohmann/json.hpp>

class DeletePersonRequest {
public:
    std::string id;

    DeletePersonRequest() = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(DeletePersonRequest, id);
};


#endif //DELETE_PERSON_REQUEST_HPP
