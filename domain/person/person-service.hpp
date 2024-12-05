//
// Created by elif on 12/2/24.
//

#ifndef PERSON_SERVICE_HPP
#define PERSON_SERVICE_HPP
#include "person-factory.hpp"

class PersonService {
    PersonRepository &personRepository;
    PersonFactory &personFactory;

public:
    PersonService(PersonRepository& repository, PersonFactory& factory) : personRepository(repository), personFactory(factory) {
    }


    void addPerson(const std::string &name, const std::string &surname, const std::string &phone,
                   const std::string &mail) {
        const auto person = personFactory.createDocumentForDB(name, surname, phone, mail);
        personRepository.add(person);
    }

    void updatePerson(const std::string &id, const std::string &name, const std::string &surname, const std::string &phone,
                      const std::string &mail) {
        const auto updatedDocument = personFactory.createUpdatedDocumentForDB(id, name, phone, mail);
        personRepository.update(id, updatedDocument);
    }

    void removePerson(const std::string &id) {
        personRepository.remove(id);

    }

    Person findPersonsById(const std::string &id) {
        return personRepository.findById(id);
    }

    std::vector<Person> listALl() {
        auto cursor = personRepository.listAll();
        return cursor;
    }
};

#endif //PERSON_SERVICE_HPP
