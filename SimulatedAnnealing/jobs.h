#pragma once

#include <vector>

class Job
{
public:
    int duration;
    int num;
    Job(int dur, int num): duration(dur), num(num) {}

    friend std::ostream& operator<<(std::ostream& os, const Job &job)
    {
        os << job.duration;
        return os;
    }
};

class Jobs
{
public:
    int mean;
    std::vector<Job> jobs;

    Jobs(std::vector<int> &jt)
    {
        int i = 0;
        int s = 0;
        for (auto t: jt)
        {
            jobs.push_back(Job(t, i++));
            s += t;
        }
        this->mean = s / i;
    }

};