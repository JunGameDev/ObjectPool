// Main.cpp
#include <iostream>
#include "ObjectPool.hpp"


void* operator new(const size_t size)
{
    void* ptr = malloc(size);
    std::cout << "Allocating size: " << size << " bytes ";
    std::cout << "at: 0x" << std::hex << (size_t)ptr << std::endl;
    return ptr;
}

void operator delete(void* ptr)
{
    std::cout << "Deleting ptr at: 0x" << std::hex << (size_t)ptr << std::endl;
    free(ptr);
}

int main()
{
    ObjectPool pool(16);

    pool.AddGameObject("Cat",    { 10, 11, 12 },        { 13, 14 });
    pool.AddGameObject("Dog",    { 100, 110, 120 },     { 130, 140 });
    pool.AddGameObject("Rat",    { 1000, 1100, 1200 },  { 1300, 1400 });
    pool.AddGameObject("Rabbit", { 1200, 100, 3200 },   { 3300, 3400 });


    pool.PrintGameObjects();

    pool.DestroyGameObject(1);  // dog should be gone
    pool.PrintGameObjects();

    pool.AddGameObject("Bird", { 10000, 11000, 12000 }, { 13000, 14000 });
    pool.PrintGameObjects();

    system("pause");
    return 0;
}
