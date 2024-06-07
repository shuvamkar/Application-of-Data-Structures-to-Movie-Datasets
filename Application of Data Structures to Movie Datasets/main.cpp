// Winter'24
// Instructor: Diba Mirza
// Student name: Shuvam Kar
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <map>
#include <unordered_map>
using namespace std;

#include "utilities.h"
#include "movies.h"


bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    set<Movie> alphaMovies;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            Movie movie(movieName, movieRating);
            alphaMovies.insert(movie);
    }

    movieFile.close();

    if (argc == 2){
        for (const auto& movie1 : alphaMovies) {
            cout << movie1.getName() << ", " << movie1.getRating() << endl;
        }
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    prefixFile.close();

    vector<string> bestMoviesPrefixes;
    map <string, set<Movie, MovieComparator>> prefixMoviesMap;
    for(const auto& movie : alphaMovies) {
        for (const string& prefix : prefixes) {
            if(movie.getName().find(prefix) == 0) {
                prefixMoviesMap[prefix].insert(movie);
                break;
            }
        }
    }
    
    for (const string& prefix : prefixes) {
        if(prefixMoviesMap[prefix].empty()) {
            cout << "No movies found with prefix "<< prefix << endl;
        }
        else {
            for(const Movie& movie : prefixMoviesMap[prefix]) {
                cout << movie.getName() << ", " << movie.getRating() << endl;
            }
            bestMoviesPrefixes.push_back(prefix);
            cout << endl;
        } 
    }

    for(string prefix : bestMoviesPrefixes) {
        Movie bestMovie = *prefixMoviesMap[prefix].begin();
        cout << "Best movie with prefix " << prefix << " is: " << bestMovie.getName() << " with rating " << std::fixed << std::setprecision(1) << bestMovie.getRating() << endl;
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/*

Part 3a:
    Time Complexity Analysis:
        1.
            Line 77 - 84:
                In the outer loop, I iterate through n movies, resulting in a time complexity of O(n). 
                In the inner loop, I iterate through m prefixes, resulting in a time of O(m).
                Within each iteration of the inner loop, my code utilizes the find function to check if
                a prefix is found in the movie name, with a time complexity of O(l), where l is the max
                number of characters in a movie name. Also, within the inner loop, my code inserts a movie
                into a set for a specific prefix, which takes O(log k), where k is a max number of movies, 
                associated with each prefix. The overall time complexity two loops result in a time complexity
                of O(n * m * (l + log k)).

            Line 86 - 97:
                In the outer loop, I iterate through m prefixes, resulting in a time complexity of O(m).
                In the inner loop, if the set is not empty, iterating over each movie in the set takes 
                O(k) time. The overall time complexity is O(m * k).

            Line 99 - 102:
                In the loop, I iterate through m prefixes, resulting in O(m). 

            Taking the most dominant term,     
            the Overall Big-O Time Complexity Notation is:
                O(n * m * (l + log k))

        2. 
            Running Times:
                For "input_20_random.csv", the algorithm took 181ms.
                For "input_100_random.csv", the algorithm took 295ms.
                For "input_1000_random.csv", the algorithm took 499ms.
                For "input_76920_random.csv", the algorithm took 17107ms.

Part 3b:
    Space Complexity Analysis:
        Since we are assuming that all n movies are already stored and all m prefixes are stored,
        the space complexity for storing movies and prefixes is not considered separately in the analysis. 
        However, it contributes to the overall space complexity.

        The space complexity of the code stems from two primary data structures: a map and a vector.
        The map at most hold n movies so its space complexity would be O(n). The vector is made up of 
        at max m prefixes so its space complexity is O(m). The overall space complexity of Part 2 is O(n + m).

        The Big-O Space Complexity Notation is:
                O(n + m)

Part 3c:
    The algorithm was primarily designed with a focus on achieving low time complexity, but it also considered 
    maintaining a reasonable space complexity.
    
    1. Target: Low Time Complexity

        I was able to achieve a decently low time complexity, but initially, my code suffered from nested for loops, iterating through 
        every movie for each prefix. However, after restructuring the loops, I managed to significantly improve the runtime. By flipping
        the inner and outer loops, my code now iterated through all the prefixes for every movie, which proved more efficient, considering 
        there are typically fewer prefixes than movies, especially in large datasets. 
        
        Another major improvement was adding a break statement in my inner loop. This would stop the loop if a prefix was found for 
        a movie and both these changes helped me lower my code's average runtime from 6.9s to 1.5s. 
        
        In terms of space complexity, I maintained a good balance. I utilized a map to efficiently store prefixes and their corresponding 
        movies. Additionally, I employed a vector to hold prefixes with at least one associated movie. However, despite these efforts, 
        I struggled to find a better approach for printing the highest rated movie for each prefix at the end, which may have slightly increased 
        the space complexity.

*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}