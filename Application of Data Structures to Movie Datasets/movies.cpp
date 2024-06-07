#include "movies.h"
#include <iostream>
#include <string>
using namespace std;

Movie::Movie(string nm, double rtg) {
    name = nm;
    rating = rtg;
}

string Movie::getName() const{
    return name;
}

double Movie::getRating() const{
    return rating;
}

bool Movie::operator<(const Movie& other) const{
    return name < other.name;
}