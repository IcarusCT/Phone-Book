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
    PersonService &personService;

public:
    PhonebookManagementService(PersonService &service) : personService(service) {
    }

    void addPersonToPhonebook(const std::string &name, const std::string &surname, const std::string &phone,
                              const std::string &mail) {
        personService.addPerson(name, surname, phone, mail);
    }

    Person findPersonsById(const std::string &id) {
        return personService.findPersonsById(id);
    }

    std::vector<Person> listAllPersons() {
        return personService.listALl();
    }

    std::vector<Person> updatePerson(const std::string &id, const std::string &name, const std::string &surname, const std::string &phone,
                      const std::string &mail) {
        personService.updatePerson(id, name, surname, phone, mail);
        return personService.listALl();
    }

    void deletePerson(const std::string &id) {
        return personService.removePerson(id);
    }
};

#endif // PHONEBOOK_MANAGEMENT_SERVICE_HPP
