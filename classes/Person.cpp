//
// Created by mohamed-nagy on 17/12/23.
//
#include "Room.h"
#include "Person.h"


void Person::findDirection()
{
    Room::Place nextPlace(0, 0);

    std::unique_lock<std::mutex>ulock(*_mutex);
    do{
        int nextMove = std::rand() % 9;

        if(nextMove % 3 == 0)
        {
            nextPlace.x = _currentPlace.x + (-1 + int(round(nextMove/3.)));
            nextPlace.y = _currentPlace.y -1;
        }
        else if(nextMove == 2 || nextMove == 5 || nextMove == 8)
        {

            nextPlace.x = _currentPlace.x + (-1 + int(round(nextMove/5.)));
            nextPlace.y = _currentPlace.y + 1;
        }
        else
        {

            nextPlace.x = _currentPlace.x + (-1 + int(round(nextMove/4.)));
            nextPlace.y = _currentPlace.y;
        }

    }while(_room->isOccupied(nextPlace));

    move(nextPlace);

    _currentPlace = nextPlace;

}


void Person::move(Room::Place &place)
{
    _room->placePerson(_currentPlace, place, _name);

}
