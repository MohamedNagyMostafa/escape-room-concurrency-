//
// Created by mohamed-nagy on 17/12/23.
//

#ifndef TESTING_ROOM_H
#define TESTING_ROOM_H

#include <iostream>
#include <malloc.h>
#include <algorithm>


class Room
{
public:
    struct Place
    {
        int x;
        int y;

        Place() = default;
        Place(int _x, int _y): x(_x), y(_y){};

        bool operator==(const Place& source) const
        {
            return (x == source.x) && (y == source.y);
        }
    };

    Room(int&& x, int&& y, Place&& escape);

    // Copy, deep copy
    Room(const Room& source);

    Room& operator=(const Room& room);

    // Move
    Room(Room&& source);

    Room& operator=(Room&& room);

    ~Room();

    void init();

    void placePerson(const Place& currPlace, const Place& newPlace, const char& name);

    int decode(const Place& place);

    std::pair<int, int> Size()const { return _size;}
    Room::Place Escape() const{return _escape;}

    bool isOccupied(Place& place);

    void show();

private:
    std::pair<int, int> _size;
    char* _map;
    Room::Place _escape;
};

#endif //TESTING_ROOM_H
