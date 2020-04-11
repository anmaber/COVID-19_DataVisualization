#include "filereader.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <QDebug>

FileReader::FileReader(const std::string &fileToReadName)
    : fileName(fileToReadName)
{}

void FileReader::read()
{
    std::ifstream fin(fileName);
    if(!fin) qDebug() << "Cos nie halo - brak pliku/nie można odczytac";

    for (std::string line; std::getline(fin, line); )
    {
        std::replace(line.begin(), line.end(), ' ', '-');
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream in(line);
        values.push_back(
                    std::vector<std::string>(std::istream_iterator<std::string>(in),
                                             std::istream_iterator<std::string>()));
    }
}
