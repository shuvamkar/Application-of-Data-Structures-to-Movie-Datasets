#ifndef MOVIES_H
#define MOVIES_H


#include <iostream>
#include <string>
using namespace std;

class Movie {
    private:
        string name;
        double rating;
    
    public:
        Movie(string nm, double rtg);
        string getName() const;
        double getRating() const;
        bool operator<(const Movie& other) const;
};

#endif // MOVIES_H