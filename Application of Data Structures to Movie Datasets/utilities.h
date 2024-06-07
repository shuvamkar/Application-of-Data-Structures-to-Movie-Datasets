// utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include "movies.h"

class MovieComparator {
public:
    bool operator()(const Movie& movie1, const Movie& movie2) const;
};

#endif // UTILITIES_H