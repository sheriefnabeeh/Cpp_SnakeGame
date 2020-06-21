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

Path_A::Path_A()
{
  cout << "Constructor called"
       << "\n";
  open = new std::vector<Node>();
  visited = new std::vector<Node>();
}
Path_A::~Path_A()
{
  cout << "Destructor called"
       << "\n";
  delete open;
  delete visited;
}

Path_A::Path_A(const Path_A &path_a)
{
  //perform a deep copy of the Destructor
  open = new std::vector<Node>();
  visited = new std::vector<Node>();
  final_path = path_a.final_path;
  *open = *path_a.open;
  *visited = *path_a.visited;
  pGridHeight = path_a.pGridHeight;
  pGridWidth = path_a.pGridWidth;
}
Path_A &Path_A::operator=(const Path_A &path_a)
{
  if (this == &path_a)
    return *this;
  delete open;
  delete visited;
  final_path.clear();
  final_path = path_a.final_path;
  visited = path_a.visited;
  open = path_a.open;
  pGridHeight = path_a.pGridHeight;
  pGridWidth = path_a.pGridWidth;
}
Path_A &Path_A::operator=(Path_A &&path_a)
{
  if (this == &path_a)
    return *this;
  delete open;
  delete visited;
  final_path.clear();
  final_path = path_a.final_path;
  visited = path_a.visited;
  open = path_a.open;
  pGridHeight = path_a.pGridHeight;
  pGridWidth = path_a.pGridWidth;
  path_a.open = nullptr;
  path_a.visited = nullptr;
}
std::vector<Path_A::Node> Path_A::GetFinalPath()
{
  return final_path;
}

bool Comparethis(Path_A::Node begin_node, Path_A::Node end_node)
{
  if (begin_node.g_value + begin_node.h_value == end_node.g_value + end_node.h_value)
  {
    return begin_node.h_value > end_node.h_value;
  }
  return begin_node.g_value + begin_node.h_value > end_node.g_value + end_node.h_value;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<Path_A::Node> *node_vector)
{
  std::sort(node_vector->begin(), node_vector->end(), Comparethis);
}

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2)
{
  return abs(x2 - x1) + abs(y2 - y1);
}

/** 
 * Check that a cell is valid: on the grid, not an obstacle, and clear. 
 */
bool Path_A::CheckValidCell(int x, int y, Snake &snake)
{
  bool clear_cell = true;
  if (snake.SnakeCell(x, y))
  {
    clear_cell = false;
  }

  bool on_grid_x = (clear_cell && x > 0 && x <= pGridWidth);
  bool on_grid_y = (clear_cell && y > 0 && y <= pGridWidth);
  if (on_grid_x && on_grid_y)
  {
    for (Node n : *visited)
    {
      if (n.x == x && n.y == y)
        clear_cell = false;
    }
  }

  return clear_cell;
}

void Path_A::AddToOpen(Node &node)
{
  // Add node to open vector, and mark grid cell as closed.
  open->push_back(node);
  node.visited = true;
  visited->push_back(node);
}

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */
void Path_A::ExpandNeighbors(const Node &current, int goal[2], Snake &snake)
{
  // Get current node's data.
  int x = current.x;
  int y = current.y;
  int g = current.g_value;

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++)
  {
    Node neighbor;
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (Path_A::CheckValidCell(x2, y2, snake))
    {
      // Increment g value and add neighbor to open list.
      neighbor.g_value = g + 1;
      neighbor.x = x2;
      neighbor.y = y2;
      neighbor.h_value = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(neighbor);
      if (i == 3)
        break;
    }
  }
}

vector<Path_A::Node> Path_A::Search(int init[2], int goal[2], Snake &snake)
{

  // Initialize the starting node.
  Node node_init{init[0], init[1], false, 0, 0};

  AddToOpen(node_init);
  ExpandNeighbors(node_init, goal, snake);

  while (open->size() > 0)
  {
    // Get the next node
    CellSort(open);

    auto current = open->back();
    open->pop_back();
    final_path.push_back(current);

    // Check if we're done.
    if (current.x == goal[0] && current.y == goal[1])
    {
      return final_path;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current, goal, snake);
  }

  // We've run out of new nodes to explore and haven't found a path.
  cout << "No path found!"
       << "\n";
  return std::vector<Node>{};
}

void Path_A::run(Snake &snake, SDL_Point food, std::size_t kGridWidth, std::size_t kGridHeight)
{
  final_path.clear();
  open->clear();
  visited->clear();
  // food.x = (7 , 15)  snake.x = 29 and snake.y = 5 :: failure case
  //food.x = (24 , 22)  snake.x = 3 and snake.y = 12
  Path_A::pGridHeight = kGridHeight;
  Path_A::pGridWidth = kGridWidth;
  int foodLocation[2]{food.x, food.y};
  int snakeHead[2]{static_cast<int>(snake.head_x), static_cast<int>(snake.head_y)};
  long gridLimits[2]{static_cast<int>(kGridWidth), static_cast<int>(kGridHeight)};
  auto solution = Search(snakeHead, foodLocation, snake);
}
