//
// Created by elif on 12/2/24.
//

#ifndef PERSON_SERVICE_HPP
#define PERSON_SERVICE_HPP


class PersonService {
    PersonRepository &personRepository;

public:
    explicit PersonService(PersonRepository &repository) : personRepository(repository) {
    }


    void addPerson(const std::string &name, const std::string &surname, const std::string &phone,
                   const std::string &mail) {
        Person person(name, surname, phone, mail);
        personRepository.add(person);
    }

    void updatePerson(const std::string &id, const std::string &name, const std::string &surname, const std::string &phone,
                      const std::string &mail) {
        Person person(name, surname, phone, mail);
        personRepository.update(id, person);
    }

    void removePerson(const std::string &id) {
        personRepository.remove(id);

    }

    Person findPersonsById(const std::string &id) {
        return personRepository.findById(id);
    }

    std::vector<Person> listALl() {
        std::vector<Person> persons = personRepository.listAll();
        return persons;
    }
};

#endif //PERSON_SERVICE_HPP
