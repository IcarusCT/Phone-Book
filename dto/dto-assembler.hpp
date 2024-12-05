//
// Created by elif on 12/5/24.
//

#ifndef DTO_ASSEMBLER_HPP
#define DTO_ASSEMBLER_HPP
#include <crow/json.h>

#include "person/person.hpp"
#include "request/add-person-request.hpp"
#include "request/delete-person-request.hpp"
#include "response/search-person-response.hpp"
#include "request/update-person-request.hpp"
#include "response/list-persons-response.hpp"

class DtoAssembler {
public:
    static AddPersonRequest toAddPersonRequest(const crow::json::rvalue &json) {
        return AddPersonRequest(
            json["name"].s(),
            json["surname"].s(),
            json["phone"].s(),
            json["mail"].s()
        );
    }

    static SearchPersonResponse toSearchPersonResponse(const Person &person) {
        return SearchPersonResponse(
            person.name,
            person.surname,
            person.phone,
            person.mail
        );
    }

    static UpdatePersonRequest toUpdatePersonRequest(const crow::json::rvalue &json) {
        return UpdatePersonRequest(
            json["id"].s(),
            json["name"].s(),
            json["surname"].s(),
            json["phone"].s(),
            json["mail"].s()
        );
    }

    static DeletePersonRequest toDeletePersonRequest(const crow::json::rvalue &json) {
        return DeletePersonRequest(json["id"].s());
    }


    static ListPersonsResponse toListPersonsResponse(const std::vector<Person> &persons) {
            return ListPersonsResponse(persons);

    }
};


#endif //DTO_ASSEMBLER_HPP
