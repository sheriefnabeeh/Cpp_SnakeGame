#include <algorithm> // for sort
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "snake.h"
#include "game.h"
#include "path.h"
using std::abs;
using std::cout;
using std::ifstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
/*
1.as input, take the Grid's data 
2.when calculating neighbors : obstacle is grid or snake ->using directional deltas
3.
*/

/**
 * Compare the F values of two cells.
 */
bool Compare(Node begin_node, Node end_node)
{
  return begin_node.g_value + begin_node.h_value > end_node.g_value + end_node.h_value;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<Node> &node_vector)
{
  sort(node_vector.begin(), node_vector.end(), Compare);
}

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
  return abs(x2 - x1) + abs(y2 - y1);
}

/** 
 * Check that a cell is valid: on the grid, not an obstacle, and clear. 
 */
bool CheckValidCell(int x, int y, vector<vector<State>> &grid)
{
/*
check here for body of snake whether it's an obstacle or not on the first move too.
*/

  bool on_grid_x = (x >= 0 && x < grid.size());
  bool on_grid_y = (y >= 0 && y < grid[0].size());
  if (on_grid_x && on_grid_y)
    return grid[x][y] == State::kEmpty;
  return false;
}

/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(Node &node, vector<Node> &openlist)
{
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(node);
  node.visited = true;
}

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const Node  &current, int goal[2], vector<Node> &openlist)
{
  // Get current node's data.
  int x = current.x;
  int y = current.y;
  int g = current.g_value;

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++)
  {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid))
    {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}

/** 
 * Implementation of A* search algorithm
 */
vector<Node> Path::Search(int init[2], int goal[2])
{
  // Create the vector of open nodes.
  //vector<Node> open{};

  // Initialize the starting node.
  Node node_init{init[0], init[1], false, 0, 0};
  int h_value = Heuristic(node_init.x, node_init.y, goal[0], goal[1]);

  AddToOpen(node_init, open);

  while (open.size() > 0)
  {
    // Get the next node
    CellSort(open);
    auto current = open.back();
    open.pop_back();

    // Check if we're done.
    if (current.x == goal[0] && current.y == goal[1])
    {
      return final_path;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal,open);
  }

  // We've run out of new nodes to explore and haven't found a path.
  cout << "No path found!"
       << "\n";
  return std::vector<Node>{};
}

//this is supposed to be implemented in the renderer
/*
void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}
*/

void Path::run(Game &game, std::size_t &kGridWidth, std::size_t &kGridHeight)
{
  int foodLocation[2]{game.GetFoodLocation().x, game.GetFoodLocation().y};
  int snakeHead[2]{game.GetSnake().head_x, game.GetSnake().head_y};
  int gridLimits[2]{kGridWidth, kGridHeight};
  auto solution = Search(foodLocation, snakeHead);
}

//what's needed here :
