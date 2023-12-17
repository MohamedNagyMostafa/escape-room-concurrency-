#include <iostream>
#include <memory>
#include <future>

#include "classes/Room.h"
#include "classes/Person.h"


int main()
{
    bool termination = false;
    Room::Place escapeCell(4, 4);


    std::shared_ptr<Room> roomPtr(new Room(5, 5, std::move(escapeCell)));
    std::shared_ptr<std::mutex> mutexPtr(new std::mutex);

    std::vector<std::future<void>> persons;
    std::vector<std::string> winners;
    std::mutex  winnnerResMutex;

    for( int i = 0; i < 7; i++)
    {
        Person person( std::to_string(i)[0], roomPtr.get(), mutexPtr.get());

        persons.emplace_back(std::async(std::launch::async, [&winners, &winnnerResMutex, i](Person person){
            auto t_start = std::chrono::high_resolution_clock::now();
            while(!person.isEscaped())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200 + (30 * i)));

                person.findDirection();

            }
            auto t_end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start);

            std::lock_guard<std::mutex> winnerlock(winnnerResMutex);
            char name = person.Name();
            winners.emplace_back("Person("+ std::string(1,name) + ") escaped from the room within " + std::to_string(duration.count())+ "  microseconds");
        }, std::move(person)));
    }


    std::future<void>roomTh     = std::async(std::launch::async, [&termination](Room* room, std::mutex* mutex){
            while(!termination)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

                mutex->lock();
                room->show();
                mutex->unlock();

            }
        }, roomPtr.get(), mutexPtr.get());


    std::for_each(persons.begin(), persons.end(), [](std::future<void>& future){future.wait();});
    termination = true;
    roomTh.wait();

    std::cout<<"\n Escape Order"<<std::endl;
    std::for_each(winners.begin(), winners.end(), [](std::string& winner){std::cout <<winner<<std::endl;});
    return 0;

}


