#include <iostream>
#include <crow/app.h>
#include <asio.hpp>
#include <mongocxx/client.hpp>
#include "person/person-repository.hpp"
#include "person/person.hpp"
#include <mongocxx/exception/exception.hpp>
#include "person/person-service.hpp"
#include "person/person-factory.hpp"
#include <bsoncxx/document/value.hpp>
#include "phonebook-management-service.hpp"


void print_info(const Person &person){
    std::cout << "Row: " << person.row << std::endl;
    std::cout << "Name: " << person.name << std::endl;
    std::cout << "Surname: " << person.surname << std::endl;
    std::cout << "Phone: " << person.phone << std::endl;
    std::cout << "Mail: " << person.mail << std::endl;
    std::cout << "------------------------------" << std::endl;

}

int main() {


    PersonRepository repository;
    PersonService service(repository);
    PhonebookManagementService phonebookService(service);
    std::string name, surname, phone, mail, option;
    int row;

    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};

    auto db = client["phonebook"];
    auto collection = db["contacts"];


    std::cout << "Yapmak istediğiniz işlemi seçin: " << std::endl;
    std::cout << "1- Kişi ekle" << std::endl;
    std::cout << "2- Kişi bul" << std::endl;
    std::cout << "3- Kişi güncelle" << std::endl;
    std::cout << "4- Kişi sil" << std::endl;
    std::cout << "5- Rehberi görüntüle" << std::endl;
    std::getline(std::cin, option);

    if (option == "1") {
        std::cout << "name:";
        std::getline(std::cin, name);
        std::cout << "surname:";
        std::getline(std::cin, surname);
        std::cout << "number:";
        std::getline(std::cin, phone);
        std::cout << "mail:";
        std::getline(std::cin, mail);

        Person person(row, name, surname, phone, mail);

        try {
            phonebookService.addPersonToPhonebook(row, name, surname, phone, mail);
            std::cout << "Kişi başarıyla kaydedildi." << std::endl;

        } catch (const mongocxx::exception &e) {
            std::cerr << "Hata " << e.what() << std::endl;
        }
    }
    else if (option == "2") {
        std::cout << "İsim:";
        std::getline(std::cin, name);
        auto persons = phonebookService.listPersonsByName(name);
        for (const auto &person : persons) {
            print_info(person);
        }

    }
    else if (option == "3") {
        std::cout << "İsim: ";
        std::getline(std::cin, name);
        auto persons = phonebookService.listPersonsByName(name);
        for (const auto &person : persons) {
            print_info(person);
        }


        try {
            std::cout << "Güncellemek istediğiniz kişinin sıra numarasını girin: ";
            std::cin >> row;
            std::cin.ignore();

            std::string newName, newSurname, newPhone, newMail;
            std::cout << "Yeni isim: ";
            std::getline(std::cin, newName);
            std::cout << "Yeni soyisim: ";
            std::getline(std::cin, newSurname);
            std::cout << "Yeni telefon: ";
            std::getline(std::cin, newPhone);
            std::cout << "Yeni mail: ";
            std::getline(std::cin, newMail);

            if (!newName.empty()) name = newName;
            if (!newSurname.empty()) surname = newSurname;
            if (!newPhone.empty()) phone = newPhone;
            if (!newMail.empty()) mail = newMail;

            phonebookService.addPersonToPhonebook(row, name, surname, phone, newMail);

            std::cout << "Kişi başarıyla güncellendi." << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Hata " << e.what() << std::endl;
        }
    }
    else if (option == "4") {
        std::cout << "İsim: ";
        std::getline(std::cin, name);
        auto persons = phonebookService.listPersonsByName(name);
        for (const auto &person : persons) {
            print_info(person);
        }

        try {
            std::cout << "Silmek istediğiniz kişinin sıra numarasını girin: ";
            std::cin >> row;

            phonebookService.deletePerson(row);
            std::cout << "Kişi başarıyla silindi." << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Hata " << e.what() << std::endl;
        }
    }
    else if (option == "5") {
        auto persons = phonebookService.listAllPersons();
        for (const auto &person : persons) {
            print_info(person);
        }
    }

}
