//
// Created by mohamed-nagy on 17/12/23.
//
#include "Room.h"


Room::Room(int&& x, int&& y, Place&& escape): _escape(escape)
{
    _size.first     = x;
    _size.second    = y;
    _map = (char*) std::malloc(sizeof (char) * (_size.first * _size.second));

    init();
}

Room::~Room()
{
    delete[] _map;
}

Room::Room(const Room &source): _escape(source._escape), _size(source._size)
{
    _map    = (char*) std::malloc(sizeof (char) * (_size.first * _size.second));

    for(size_t i = 0; i < _size.first * _size.second; i++)
    {
        _map[i] = source._map[i];
    }
}

Room& Room::operator=(const Room &source) {
    _size   = source._size;
    _map    = (char*) std::malloc(sizeof (char) * (_size.first * _size.second));
    _escape = source._escape;

    for(size_t i = 0; i < _size.first * _size.second; i++)
    {
        _map[i] = source._map[i];
    }

    return *this;
}

Room::Room( Room &&source): _size(source._size), _map(source._map), _escape(source._escape)
{

    source._map = nullptr;
}

Room& Room::operator=( Room &&source) {
    _size   = source._size;
    _map    = source._map;
    _escape = source._escape;


    source._map = nullptr;

    return *this;
}

int Room::decode(const Place& place)
{
    return ((place.x >= 0 && place.x < _size.first) && (place.y >= 0 && place.y < _size.second))?place.y + (place.x * _size.second): -1;
}

void Room::init()
{
    for(size_t i = 0; i < _size.first * _size.second; i++)
        _map[i] = '_';
    _map[decode(_escape)] = 'X';
}

bool Room::isOccupied(Place &currPlace)
{
    int && value = decode(currPlace);
    if(value == -1 || _map[value] != '_')
    {
        if(_map[value] == 'X')
            return false;
        return true;
    }
    else{
        return false;
    }
}

void Room::placePerson(const Place& currPlace, const Place& newPlace, const char& name)
{
    _map[decode(currPlace)] = '_';
    if(!(newPlace == _escape))
        _map[decode(newPlace)] = name;

}

void Room::show()
{

    for(size_t i = 0; i < _size.first * _size.second; i++)
    {
        if(i != 0 && i % _size.second == 0)
            std::cout<<std::endl;
        std::cout << "|" << _map[i];
    }
    std::cout<< "\n=========================\n";
}
