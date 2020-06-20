#ifndef PATH_H
#define PATH_H
#include "snake.h"
#include "game.h"
#include <vector>
#include <iostream>

class Path_A
{
public:
    Path_A();
    void run(Game &game, std::size_t,std::size_t); //A*
    struct Node
    {
        int x;
        int y;
        bool visited;
        int g_value;
        int h_value;
    };

    std::vector<Node> Search(int *, int *, Game &);
    int CalculateHValue();
    void AddNeighbors();

    //CompareNodes
    //NextNode
    //ConstructFinalPath
    //Snake snake_path;

private:
    std::vector<Node> final_path;
    std::vector<Node> open;
    std::vector<Node> visited;
    void AddToOpen(Node &node);
    void ExpandNeighbors(const Node &current, int goal[2], Game &);
    bool CheckValidCell(int x, int y, Game &game);
    std::size_t pGridWidth;
    std::size_t pGridHeight;
};

#endif