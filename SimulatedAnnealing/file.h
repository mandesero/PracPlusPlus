#pragma once

#include <iostream>
#include <experimental/random>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

void generateFile(std::string filename, int numProcessors, int numJobs, int minDuration, int maxDuration)
{
    std::ofstream outputFile(filename);

    outputFile << numProcessors << std::endl;

    outputFile << numJobs << std::endl;

    for (int i = 0; i < numJobs; i++)
    {
        int duration = std::experimental::randint(minDuration, maxDuration);
        outputFile << duration;

        if (i != numJobs - 1)
        {
            outputFile << ",";
        }
    }

    outputFile.close();
}

struct FileData
{
    int numProcessors;
    int numJobs;
    std::vector<int> jobDurations;
};

FileData parseFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    FileData fileData;

    if (inputFile.is_open())
    {
        std::string line;
        std::getline(inputFile, line);
        fileData.numProcessors = std::stoi(line);

        std::getline(inputFile, line);
        fileData.numJobs = std::stoi(line);

        std::getline(inputFile, line);
        std::stringstream ss(line);
        std::string durationStr;
        while (std::getline(ss, durationStr, ','))
        {
            fileData.jobDurations.push_back(std::stoi(durationStr));
        }

        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

    return fileData;
}