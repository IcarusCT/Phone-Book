//
// Created by elif on 12/5/24.
//

#ifndef LIST_PERSONS_RESPONSE_HPP
#define LIST_PERSONS_RESPONSE_HPP
#include <crow/json.h>
#include <vector>
#include <iostream>
#include <crow/app.h>
#include "person/person.hpp"


class ListPersonsResponse {
public:
    ListPersonsResponse(const std::vector<Person>& persons) : persons(persons) {}

    crow::json::wvalue toJson() const {
        crow::json::wvalue result;


        crow::json::wvalue::list json_array;

        for (const auto& person : persons) {
            crow::json::wvalue person_obj = crow::json::wvalue::object();

            person_obj["name"] = person.name;
            person_obj["surname"] = person.surname;
            person_obj["phone"] = person.phone;
            person_obj["mail"] = person.mail;

            json_array.push_back(std::move(person_obj));
        }

        result["persons"] = std::move(json_array);

        return result;
    }

private:
    std::vector<Person> persons;

};


#endif //LIST_PERSONS_RESPONSE_HPP
