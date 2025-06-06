#ifndef SCORES_H
#define SCORES_H

#include <iostream>

using namespace std;

class Scores
{
    string itsName;
    int itsTime;

public:
    Scores(string name, int time = 0) : itsName(name), itsTime(time) {}

    string getItsName() const;
    int getItsTime() const;
    void saveToFile(const string& filename) const;
};

#endif // SCORES_H
