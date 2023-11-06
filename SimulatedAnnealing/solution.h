#pragma once

#include "jobs.h"
#include <map>
#include <vector>
#include <algorithm>

class Solution
{
public:
    std::map<int, std::vector<Job>> solution;
    int K3;

    Solution(std::map<int, std::vector<Job>> sol): solution(sol)
    {
        calculateK3();
    }

    void calculateK3()
    {
        std::vector<int> procTimes;
        for (auto &kv : solution)
        {
            int t = 0;
            for (auto &j: kv.second)
                t += j.duration;
            procTimes.push_back(t);
        }

        auto maxT = *std::max_element(procTimes.begin(), procTimes.end());
        auto minT = *std::min_element(procTimes.begin(), procTimes.end());
        this->K3 = maxT - minT;
    }
};