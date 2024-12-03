//
// Created by elif on 12/2/24.
//

#ifndef PHONEBOOK_MANAGEMENT_SERVICE_HPP
#define PHONEBOOK_MANAGEMENT_SERVICE_HPP

#include <iostream>
#include <ostream>

#include "person/person-service.hpp"
#include "person/person-repository.hpp"

class PhonebookManagementService {
    PersonService& personService;


public:
    PhonebookManagementService(PersonService& service) : personService(service) {}

    void addPersonToPhonebook(int row, const std::string& name, const std::string& surname, const std::string& phone, const std::string& mail) {
        personService.addPerson(row, name, surname, phone, mail);
    }

    std::vector<Person> listPersonsByName(const std::string &name) {
        return personService.findPersonsByName(name);

    }
};

#endif // PHONEBOOK_MANAGEMENT_SERVICE_HPP


