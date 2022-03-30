#include <string>
#include <iostream>
#include <climits>
#include <map>
#include "Direction.hpp"

using namespace std;

namespace ariel
{
    class Notebook
    {
    private:
        map<int,map<int,string>> myNotebook;
        // int page, row, column;
       

    public:
        Notebook() {};
        void write( int page, int row,  int column, Direction direction, string message);
        string read(int page, int row,  int column, Direction direction, int length);
        void erase(int page, int row,  int column, Direction direction, int length);
        static void show(int page);
        ~Notebook() {};
    };
}