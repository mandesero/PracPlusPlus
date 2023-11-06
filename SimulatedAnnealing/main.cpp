
#include "main.h"

int main()
{
    std::string filename;
    int gen;
    std::cout << "Выберите:\n1: Генерация файла\n2: Существующий файл\n";
    std::cin >> gen;
    int procs, jobs, lim_min, lim_max;

    if (gen == 1)
    {
        std::cout << "Введите имя файла (пример: out.csv)\n";
        std::cin >> filename;
        std::cout << "Введите количество процессоров, задач, мин и макс границу длительности (пример: 2 3 1 5)\n";
        std::cin >> procs >> jobs >> lim_min >> lim_max;
        generateFile(filename, procs, jobs, lim_min, lim_max);
    }
    else if (gen == 2)
    {
        std::cout << "Введите имя файла (пример: out.csv)\n";
        std::cin >> filename;
    }
    else
    {
        std::cout << "Ошибка :(" << std::endl;
        return 0;
    }

    int mode;
    std::cout << "Закон температуры:\n1: Cauchy\n2: LogDiv\n3: Boltzmann\n";
    std::cin >> mode;

    if (mode == 1)
    {
        SimulatedAnnealing<Cauchy> s(filename);
    }
    else if (mode == 2)
    {
        SimulatedAnnealing<LogDiv> s(filename);
    }
    else if (mode == 3)
    {
        SimulatedAnnealing<Boltzmann> s(filename);
    }
    else
    {
        std::cout << "Ошибка :(" << std::endl;
        return 0;
    }
    return 0;
    // std::string filename = "out_0.csv";
    // for (int procs=10; procs <= 500; procs = procs + 10)
    // {  
    //     for (int jobs=1000; jobs < 10000; jobs = jobs + 200)
    //     {   
    //         double t = 0;
    //         std::cout << procs << " " << jobs << std::endl;
    //         generateFile(filename, procs, jobs, 10, 100);
    //         SimulatedAnnealing<Cauchy> k(filename);
    //         t += k.time;
    //         SimulatedAnnealing<Cauchy> k1(filename);
    //         t += k1.time;
    //         SimulatedAnnealing<Cauchy> k2(filename);
    //         t += k2.time;
    //         SimulatedAnnealing<Cauchy> k3(filename);
    //         t += k3.time;
    //         SimulatedAnnealing<Cauchy> k4(filename);
    //         t += k4.time;
    //         std::cout << t / 5 << std::endl;
    //     }
    // }

    // std::string filename = "out_1.csv";
    // for (int procs=10; procs <= 500; procs = procs + 10)
    // {  
    //     for (int jobs=1000; jobs < 10000; jobs = jobs + 200)
    //     {   
    //         double t = 0;
    //         std::cout << procs << " " << jobs << std::endl;
    //         generateFile(filename, procs, jobs, 10, 100);
    //         SimulatedAnnealing<LogDiv> k(filename);
    //         t += k.time;
    //         SimulatedAnnealing<LogDiv> k1(filename);
    //         t += k1.time;
    //         SimulatedAnnealing<LogDiv> k2(filename);
    //         t += k2.time;
    //         SimulatedAnnealing<LogDiv> k3(filename);
    //         t += k3.time;
    //         SimulatedAnnealing<LogDiv> k4(filename);
    //         t += k4.time;
    //         std::cout << t / 5 << std::endl;
    //     }
    // }

    // std::string filename = "out_2.csv";
    // for (int procs=10; procs <= 100; procs = procs + 10)
    // {  
    //     for (int jobs=200; jobs < 1000; jobs = jobs + 100)
    //     {   
    //         double t = 0;
    //         std::cout << procs << " " << jobs << std::endl;
    //         generateFile(filename, procs, jobs, 10, 100);
    //         SimulatedAnnealing<Boltzmann> k(filename);
    //         t += k.time;
    //         SimulatedAnnealing<Boltzmann> k1(filename);
    //         t += k1.time;
    //         SimulatedAnnealing<Boltzmann> k2(filename);
    //         t += k2.time;
    //         SimulatedAnnealing<Boltzmann> k3(filename);
    //         t += k3.time;
    //         SimulatedAnnealing<Boltzmann> k4(filename);
    //         t += k4.time;
    //         std::cout << t / 5 << std::endl;
    //     }
    // }

}
