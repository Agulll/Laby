  #include <iostream>
  #include <array>
  #include <vector>
  #include <algorithm>
  #include <time.h>
  #include <stdio.h>


  struct cell {
  bool visited = false;
  int x, y;
  bool t = false;
  bool r = false;
  bool l = false;
  bool b = false;
  };

    struct builder {
    int x, y;
    std::vector<cell> history;
  };

  void show (std::array<std::array<cell, 15>, 15> grid, builder b1)
   {
    for (std::size_t i = 0; i < grid.size(); i++) {
      for (std::size_t j = 0; j < grid[i].size(); j++) {
          if (!grid[i][j].visited){
            std::cout << "╳";
          }
          else if (grid[i][j].x == b1.x && grid[i][j].y == b1.y){
            std::cout << "░";
          }
          else
          if (grid[i][j].t)
            if (grid[i][j].r)
              if (grid[i][j].b)
                if (grid[i][j].l)
                  std::cout << "╋";
                else
                  std::cout << "┣";
              else
                if (grid[i][j].l)
                  std::cout << "┻";
                else
                  std::cout << "┗";
            else
              if (grid[i][j].b)
                if (grid[i][j].l)
                  std::cout << "┫";
                else
                  std::cout << "┃";
              else
                if (grid[i][j].l)
                  std::cout << "┛";
                else
                  std::cout << "╹";
          else
            if (grid[i][j].r)
              if (grid[i][j].b)
                if (grid[i][j].l)
                  std::cout << "┳";
                else
                  std::cout << "┏";
              else
                if (grid[i][j].l)
                  std::cout << "━";
                else
                  std::cout << "╺";
            else
              if (grid[i][j].b)
                if (grid[i][j].l)
                  std::cout << "┓";
                else
                  std::cout << "╻";
              else
                if (grid[i][j].l)
                  std::cout << "╸";
                else
                  std::cout << " ";
      }
      std::cout << '\n';
    }
  }

bool anyof (std::array<std::array<cell, 15>,15> grid){
  for (std::size_t i = 0; i < grid.size(); i++) {
    for (std::size_t j = 0; j < grid[i].size(); j++) {
      if (!grid[i][j].visited){
        return true;
      }
    }
  }
  return false;
}

  int main() {
    srand (time(NULL));
    builder b1;
    b1.x = 0;
    b1.y = 0;
    std::array<std::array<cell, 15>,15> grid;
    for (std::size_t i = 0; i < grid.size(); i++) {
      for (std::size_t j = 0; j < grid[i].size(); j++) {
        grid[i][j].x = i;
        grid[i][j].y = j;
      }
    }
    grid[14][14].r = true;
    grid[0][0].l = true;
    std::vector<cell> neighbors;
    //while (!std::any_of(grid.begin(), grid.end(), [](const auto&line){return std::any_of(line.begin(),line.end(),[](const auto&cell) {return cell.visited;});}))
    while (anyof(grid)){
    grid[b1.x][b1.y].visited = true;
    show(grid, b1);
    neighbors.clear();
    //top right bottom left
    if (b1.y > 0 && !grid[b1.x][b1.y - 1].visited){
      neighbors.push_back(grid[b1.x][b1.y - 1]);
    } if (b1.x < 15-1 && !grid[b1.x + 1][b1.y].visited){
      neighbors.push_back(grid[b1.x + 1][b1.y]);
    } if (b1.y < 15-1 && !grid[b1.x][b1.y + 1].visited){
      neighbors.push_back(grid[b1.x][b1.y + 1]);
    } if (b1.x > 0 && !grid[b1.x - 1][b1.y].visited){
      neighbors.push_back(grid[b1.x - 1][b1.y]);
    }
     if (neighbors.empty()){
      b1.history.pop_back();
      b1.x = (b1.history.back().x);
      b1.y = (b1.history.back().y);
    } if (!neighbors.empty())
    {int r = rand() % neighbors.size();
      if (b1.y - neighbors[r].y ==  1 && b1.x - neighbors[r].x == 0) {
        grid[b1.x][b1.y].l = true;
        grid[b1.x][b1.y - 1].r = true;
      } if (b1.x - neighbors[r].x == -1 && b1.y - neighbors[r].y == 0) {
        grid[b1.x][b1.y].b = true;
        grid[b1.x + 1][b1.y].t = true;
      } if (b1.y - neighbors[r].y == -1 && b1.x - neighbors[r].x == 0) {
        grid[b1.x][b1.y].r = true;
        grid[b1.x][b1.y + 1].l = true;
      } if (b1.x - neighbors[r].x ==  1 && b1.y - neighbors[r].y == 0) {
        grid[b1.x][b1.y].t = true;
        grid[b1.x - 1][b1.y].b = true;
      }
      b1.x = (neighbors[r].x);
      b1.y = (neighbors[r].y);
      b1.history.push_back(grid[b1.x][b1.y]);
    }
  }
}
