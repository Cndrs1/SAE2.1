#include "scores.h"
#include <fstream>
#include <iostream>

string Scores::getItsName() const
{
    return itsName;
}

int Scores::getItsTime() const
{
    return itsTime;
}

void Scores::saveToFile(const string& filename) const
{
    ofstream file(filename, ios::app);  // ouverture en ajout
    if (file.is_open())
    {
        file << itsName << " " << itsTime << endl;
        file.close();
    }
    else
    {
        cerr << "erreur : impossible d'ouvrir le fichier " << filename << endl;
    }
}
