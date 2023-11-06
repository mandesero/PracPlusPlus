#pragma once

#include <map>
#include <cmath>
#include <experimental/random>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "jobs.h"
#include "solution.h"

#define T_min 2

template <typename T>
class Mutation
{
public:
    T temp;
    int procs;
    Jobs jobs;

    Mutation(int p, Jobs jobs, double t) : procs(p), jobs(jobs)
    {
        temp = T(t);
    }

    auto distribution()
    {
        int i;
        std::map<int, std::vector<Job>> res;
        for (auto job : (this->jobs).jobs)
        {
            auto proc = std::experimental::randint(0, this->procs - 1);
            res[proc].push_back(Job(job.duration, job.num));
        }
        return res;
    }
    
    bool decreaseTemp() {
        this->temp.decrease();
        if (this->temp.curT <= T_min)
            return false;
        return true;
    }

    auto mutation(Solution &oldSol)
    {
        std::vector<int> procTimes;
        for (auto &kv : oldSol.solution)
        {
            int t = 0;
            for (auto &j: kv.second)
                t += j.duration;
            procTimes.push_back(t);
        }
        auto maxIt = std::max_element(procTimes.begin(), procTimes.end());
        auto minIt = std::min_element(procTimes.begin(), procTimes.end());

        size_t proc1 = std::distance(procTimes.begin(), maxIt);
        size_t proc2 = std::distance(procTimes.begin(), minIt);

        // while (proc1 == proc2)
        // {
        //     proc1 = std::experimental::randint(0, this->procs - 1);
        //     proc2 = std::experimental::randint(0, this->procs - 1);
        // }

        std::vector<Job> new_jobs_1;
        std::vector<Job> new_jobs_2;

        for (int i = 0; i < oldSol.solution[proc1].size(); ++i)
        {
            if (std::experimental::randint(0, 9) == 0)
                new_jobs_2.push_back(oldSol.solution[proc1][i]);
            else
                new_jobs_1.push_back(oldSol.solution[proc1][i]);
        }

        for (int i = 0; i < oldSol.solution[proc2].size(); ++i)
        {
            if (std::experimental::randint(0, 9) == 0)
                new_jobs_1.push_back(oldSol.solution[proc2][i]);
            else
                new_jobs_2.push_back(oldSol.solution[proc2][i]);
        }

        std::map<int, std::vector<Job>> tmp;
        tmp[proc1] = new_jobs_1;
        tmp[proc2] = new_jobs_2;
        for (int i = 0; i < this->procs; i++)
        {
            if (i != proc1 && i != proc2)
                tmp[i] = oldSol.solution[i];
        }

        auto newSol = Solution(tmp);

        std::srand(std::time(0));
        double r = static_cast<double>(std::rand()) / RAND_MAX;
        double t = exp(-static_cast<double>(newSol.K3 - oldSol.K3) / this->temp.curT);
        if (oldSol.K3 > newSol.K3)
            return newSol;
        if (r <= t)
            return newSol;

        return oldSol;
    }
};