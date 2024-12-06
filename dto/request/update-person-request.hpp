//
// Created by elif on 12/5/24.
//

#ifndef UPDATE_PERSON_REQUEST_HPP
#define UPDATE_PERSON_REQUEST_HPP
#include <string>
#include <crow.h>
#include <nlohmann/json.hpp>

class UpdatePersonRequest {
public:
    std::string id;
    std::string name;
    std::string surname;
    std::string phone;
    std::string mail;

    UpdatePersonRequest() = default;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(UpdatePersonRequest, id, name, surname, phone, mail);
};


#endif //UPDATE_PERSON_REQUEST_HPP
