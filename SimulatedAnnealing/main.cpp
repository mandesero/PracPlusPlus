
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
}
