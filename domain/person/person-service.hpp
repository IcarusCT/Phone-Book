//
// Created by elif on 12/2/24.
//

#ifndef PERSON_SERVICE_HPP
#define PERSON_SERVICE_HPP

class PersonService {
PersonRepository& personRepository;

public:
    explicit PersonService(PersonRepository& repository) : personRepository(repository){}

    static void print_info(const Person& person) {
        std::cout << "Row: " << person.row << std::endl;
        std::cout << "Name: " << person.name << std::endl;
        std::cout << "Surname: " << person.surname << std::endl;
        std::cout << "Phone: " << person.phone << std::endl;
        std::cout << "Mail: " << person.mail << std::endl;
    }

    void addPerson(const int row, const std::string& name, const std::string& surname, const std::string& phone, const std::string& mail) {
        Person person(row, name, surname, phone, mail);
        personRepository.add(person);
    }

    void updatePerson(int row, const std::string& name, const std::string& surname, const std::string& phone, const std::string& mail) {
        Person person(row, name, surname, phone, mail);
        personRepository.update(row, person);
    }

    void removePerson(int row) {
        personRepository.remove(row);
    }

    std::vector<Person> findPersonsByName(const std::string &name) {

        if (name.empty()) {
            std::cerr << "İsim boş olamaz." << std::endl;

        }
        try {

            auto persons = personRepository.findPersonsByName(name);

            if (persons.empty()) {
                std::cout << "Bu isimle eşleşen kişi bulunamadı." << std::endl;
            } else {

                for (const auto& person : persons) {
                    print_info(person);
                }
            }
            return (persons);
        } catch (const std::exception& e) {
            std::cerr << "Hata: " << e.what() << std::endl;
        }

    }

    void findPersonsByRow(const int row) {
        personRepository.findByRow(row);
    }


    void listALl() {
        personRepository.listAll();
        }


};

#endif //PERSON_SERVICE_HPP
