#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cstdlib>
#include <random>
#include <chrono>

////// parameters //////
const int inTask = 2; // Number of tasks
const std::vector<double> vlearning(0.8,0.5); // Learning rate task 1 and 2
const std::vector<double> vforgetting(0.3,0.5); // Forgetting rate task 1 and 2


//////// create class ////////
class Individual{
public:
    Individual();
    void performTask(int j);
    double reportPreference(int i){return taskPref[i];}

private:
    std::vector<double> taskPref{inTask,0.0};
};

Individual::Individual(){
    std::cout << "testindiv" << "\n";
    for(int i = 0; i < inTask; ++i)
    {
        std::cout << i << "\n";
        taskPref[i] = vlearning[i]/(inTask * vforgetting[i]);
        std::cout << i << "\n";
    }    
}

void Individual::performTask(int j)
{
    taskPref[j] = (1-vforgetting[j])*taskPref[j] + vlearning[j];
    for(int i = 0;i < inTask; ++i)
    {
        if(i==j) continue;
        taskPref[i] = (1-vforgetting[i])*taskPref[i];
    }
}



int main()
{
    std::cout << "Test0\n";
    Individual ind1;
    std::cout << "Test1\n";
    //std::vector<double> pref(ind1.reportPreference());
    for(int i = 0;i < inTask; ++i) 
    {
        std::cout << "Pref task " << i << " = " << ind1.reportPreference(i) << "\n";
    }
    ind1.performTask(1);
    std::cout << "Test2\n";
    for(int i = 0;i < inTask;++i) std::cout << "Pref task " 
        << i << " = " << ind1.reportPreference(i) << "\n";
    std::cout << "Test3\n";
    return 0;
}