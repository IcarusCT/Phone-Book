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


    void addPerson(const int row, const std::string &name, const std::string &surname, const std::string &phone,
                   const std::string &mail) {
        Person person(row, name, surname, phone, mail);
        personRepository.add(person);
    }

    void updatePerson(int row, const std::string &name, const std::string &surname, const std::string &phone,
                      const std::string &mail) {
        Person person(row, name, surname, phone, mail);
        personRepository.update(row, person);
    }

    void removePerson(int row) {
        personRepository.remove(row);
    }

    std::vector<Person> findPersonsByName(const std::string &name) {
            auto persons = personRepository.findPersonsByName(name);

            if (persons.empty()) {
                std::cout << "Bu isimle eşleşen kişi bulunamadı." << std::endl;
            }
            return (persons);
    }

    Person findPersonsByRow(const int row) {
        return personRepository.findByRow(row);
    }


    std::vector<Person> listALl() {
        std::vector<Person> persons = personRepository.listAll();
        return persons;
    }
};

#endif //PERSON_SERVICE_HPP
