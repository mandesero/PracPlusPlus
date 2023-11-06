#pragma once

#include <iostream>
#include "temperature.h"
#include "solution.h"
#include "mutation.h"
#include "output.h"
#include "file.h"
#include "chrono"

template <typename T>
class SimulatedAnnealing
{
public:
    double time;
    SimulatedAnnealing(const std::string filename)
    {
        std::chrono::high_resolution_clock::time_point start_time, end_time;
        start_time = std::chrono::high_resolution_clock::now();

        FileData data = parseFile(filename);
        int procs = data.numProcessors;
        int tasks = data.numJobs;
        std::vector<int> jobDurs = data.jobDurations;

        auto jobs = Jobs(jobDurs);
        auto mut = Mutation<T>(procs, jobs, jobs.mean);
        auto bestSol = Solution(mut.distribution());

        int count = 0;
        int K3 = bestSol.K3;

        do
        {
            while (count != 100)
            {
                bestSol = mut.mutation(bestSol);
                if (bestSol.K3 == K3)
                    count++;
                else
                {
                    K3 = bestSol.K3;
                    count = 0;
                }
            }
        } while (mut.decreaseTemp());

        end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "Time exec: " << (double)duration.count() / 1e6 << std::endl;
        this->time = (double)duration.count() / 1e6;
        std::ofstream outputFile("result");
        outputFile << "proc: number_of_tasks" << std::endl;
        for (auto &kv: bestSol.solution)
        {
            outputFile << kv.first << " : ";
            for (auto &job: kv.second)
                outputFile << job.num << ",";
            outputFile << std::endl;
        }
        outputFile << "K_3: " << bestSol.K3 << std::endl;
        outputFile.close();
    }
};