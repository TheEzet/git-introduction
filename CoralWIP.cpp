#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cstdlib>
#include <random>
#include <chrono>

// Global variables (add to external file? or use in another way?)
const int igridSize = 150;// size of the grid

int main()
{
    try
    {
        std::vector<int>vColumn(igridSize,0);
        vColumn[igridSize]=2;
        std::vector<std::vector<int> > vGrid(igridSize,vColumn);
        // open data file
        std::ofstream ofs("coral.csv");
        if(!ofs.is_open())
            throw std::runtime_error("unable to open file.\n");
        for(int i = 0;i < vGrid.size(); ++i)
        {
            for(int j = 0;j < vColumn.size(); ++j)
            {
                ofs << vGrid[j][i] << '\t';
                std::cout << vGrid[j][i] << ',';
            }
            ofs << '\n';
            std::cout << '\n';
        }            
    }
    catch(std::exception &error) 
    {
        std::cerr << error.what();
        exit(EXIT_FAILURE);
    }

    return 0;
}