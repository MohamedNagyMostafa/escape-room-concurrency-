//
// Created by mohamed-nagy on 17/12/23.
//

#ifndef TESTING_PERSON_H
#define TESTING_PERSON_H

#include <iostream>
#include <mutex>
#include <cmath>

class Person
{
public:
    Person(char name, Room* room, std::mutex* mutex): _name(std::move(name)), _room(room), _mutex(mutex){

        _currentPlace.x = rand() % room->Size().first;
        _currentPlace.y = rand() % room->Size().second;

    }
    ~Person() = default;

    bool isEscaped(){
        return _currentPlace == _room->Escape();
    };
    void findDirection();
    void move(Room::Place& place);
    char Name(){return _name;}
private:
    char _name;
    Room::Place _currentPlace;
    Room* _room;
    std::mutex* _mutex;
};

#endif //TESTING_PERSON_H
