#ifndef PATH_H
#define PATH_H
#include "snake.h"
#include "SDL.h"
#include <vector>
#include <iostream>

class Path_A
{
public:
    Path_A();
    ~Path_A();
    Path_A(const Path_A &);
    Path_A &operator=(const Path_A &);
    Path_A &operator=(Path_A &&);
    void run(Snake snake,const SDL_Point &food, std::size_t , std::size_t ); //A*
    //void SetFinalPath();
    struct Node
    {
        int x;
        int y;
        bool visited;
        int g_value;
        int h_value;
    };
    
    std::vector<Path_A::Node> GetFinalPath();

private:
    std::vector<Node> final_path;
    std::vector<Node> *open;
    std::vector<Node> *visited;
    void AddToOpen(Node &node);
    std::vector<Node> Search(int *, int *, Snake &);
    int CalculateHValue();
    void AddNeighbors();
    void ExpandNeighbors(const Node &current, int goal[2], Snake &);
    bool CheckValidCell(int x, int y, Snake &snake);
    std::size_t pGridWidth;
    std::size_t pGridHeight;
};

#endif