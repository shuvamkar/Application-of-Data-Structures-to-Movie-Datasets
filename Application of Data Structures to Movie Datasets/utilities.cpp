#include "utilities.h"

bool MovieComparator::operator()(const Movie& movie1, const Movie& movie2) const {
    if (movie1.getRating() != movie2.getRating()) {
        return movie1.getRating() > movie2.getRating();
    }
    return movie1.getName() < movie2.getName();
}
