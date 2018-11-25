//
// Created by User on 11/21/2018.
//

#pragma once

#include <string>

using namespace std;
static int serial_num = 0;
class city {
public:
    city(int x, int y);
    city(const city& c);
    ~city();
    int getX() const;

    int getY() const;

    int getId() const;
    city& operator=(city A);
    friend bool operator==(const city &A, const city &B);
    friend bool operator!=(const city &A, const city &B);
    friend ostream &operator<<(ostream &os, const city &A);
    friend void swap(city& city1, city& city2);

private:
    int x;
    int y;
    int id;
};


