cmake_minimum_required(VERSION 3.30)
project(phoneBook)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "/usr/local/include/mongocxx"
        "/usr/local/include/bsoncxx")


find_package(mongocxx CONFIG REQUIRED)
find_package(bsoncxx CONFIG REQUIRED)

set(APPLICATION_SOURCES

        application/phonebook-management-service.hpp
)

set(DOMAIN_SOURCES

        domain/person/person.hpp
        domain/person/person-repository.hpp
        domain/person/person-service.hpp
        domain/person/person-factory.hpp
        dto/request/add-person-request.hpp
        dto/response/search-person-response.hpp
        dto/dto-assembler.hpp
)

add_executable(phoneBook1 main.cpp
        ${DOMAIN_SOURCES}
        ${APPLICATION_SOURCES}
)

target_link_libraries(phoneBook1 PRIVATE /usr/local/lib/libmongocxx.so /usr/local/lib/libbsoncxx.so )

target_include_directories(phoneBook1 PRIVATE

        "/usr/local/include/mongocxx/v_noabi"
        "/usr/local/include/bsoncxx/v_noabi"
        "/home/elif/Crow/include"
        "/usr/local/include/nlohmann"
        "bsoncxx/builder/stream/document.hpp"
        "${CMAKE_SOURCE_DIR}/domain"
        "${CMAKE_SOURCE_DIR}/application"
)