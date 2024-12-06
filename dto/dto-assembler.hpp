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
    static SearchPersonResponse toSearchPersonResponse(const Person &person) {
        return SearchPersonResponse(
            person.name,
            person.surname,
            person.phone,
            person.mail
        );
    }


    static ListPersonsResponse toListPersonsResponse(const std::vector<Person> &persons) {
        std::vector<ListPersonsResponse::Person> result;
        result.reserve(persons.size());
        for (const auto &person: persons) {
            result.emplace_back(ListPersonsResponse::Person{
                person._id,
                person.name,
                person.surname,
                person.phone,
                person.mail
            });
        }
        return ListPersonsResponse(result);
    }
};


#endif //DTO_ASSEMBLER_HPP
