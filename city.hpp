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

    int getX() const;

    int getY() const;

    int getId() const;

    friend bool operator==(const city &A, const city &B);
    friend bool operator!=(const city &A, const city &B);
    friend ostream &operator<<(ostream &os, const city &A);

private:
    int x;
    int y;
    int id;
};


