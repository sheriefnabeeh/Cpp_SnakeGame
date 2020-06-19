#ifndef PATH_H
#define PATH_H
#include "snake.h"
#include "game.h"
#include <vector>
#include <iostream>

class Path{
    public:
    Path();
    ~Path();
    std::vector<Node> Search(int*, int*);
    int CalculateHValue(); 
    void AddNeighbors();
    //CompareNodes
    //NextNode
    //ConstructFinalPath
    void run(Game&,std::size_t&,std::size_t&); //A*
    private:
    std::vector<Node> final_path;
    std::vector<Node> open;


};
struct Node{
     int x;
     int y;
     bool visited;
     int g_value;
     int h_value;
};

#endif