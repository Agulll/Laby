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
      if (grid[i][j].visited == true){
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
    std::vector<cell> Neighbors;
    int nb = 0;
    std::string debug;
    std::cout << "starting.\n";
    //while (!std::any_of(grid.begin(), grid.end(), [](const auto&line){return std::any_of(line.begin(),line.end(),[](const auto&cell) {return cell.visited;});}))
    //while (anyof(grid)){
    for (int i = 0; i < 1001; i++)
    {
    grid[b1.x][b1.y].visited = true;
    show(grid, b1);
    Neighbors.clear();
    //top right bottom left
    if (b1.y > 0 && !grid[b1.x][b1.y - 1].visited){
      Neighbors.push_back(grid[b1.x][b1.y - 1]);
      std::cout << "push " << (grid[b1.x][b1.y - 1].x) << ',' << (grid[b1.x][b1.y - 1].y) << " - ";
    } if (b1.x < 15-1 && !grid[b1.x + 1][b1.y].visited){
      Neighbors.push_back(grid[b1.x + 1][b1.y]);
      std::cout << "push " << (grid[b1.x + 1][b1.y].x) << ',' << (grid[b1.x + 1][b1.y].y) << " - ";
    } if (b1.y < 15-1 && !grid[b1.x][b1.y + 1].visited){
      Neighbors.push_back(grid[b1.x][b1.y + 1]);
      std::cout << "push " << (grid[b1.x][b1.y + 1].x) << ',' << (grid[b1.x][b1.y + 1].y) << " - ";
    } if (b1.x < 0 && !grid[b1.x - 1][b1.y].visited){
      Neighbors.push_back(grid[b1.x - 1][b1.y]);
      std::cout << "push " << (grid[b1.x - 1][b1.y].x) << ',' << (grid[b1.x - 1][b1.y].y) << " - ";
    }
    std::cout << '\n';
     if (Neighbors.empty()){
      debug = "Back_tracking";
      b1.history.pop_back();
      b1.x = (b1.history.back().x);
      b1.y = (b1.history.back().y);
    } else {
      debug = "Foward_traking";
    }
    if (!Neighbors.empty())
    {int r = rand() % Neighbors.size();
      std::cout << "r = " << (r) << '\n';
      if (b1.y - Neighbors[r].y ==  1 && b1.x - Neighbors[r].x == 0) {
        grid[b1.x][b1.y].l = true;
        grid[b1.x][b1.y - 1].r = true;
      } if (b1.x - Neighbors[r].x == -1 && b1.y - Neighbors[r].y == 0) {
        grid[b1.x][b1.y].b = true;
        grid[b1.x + 1][b1.y].t = true;
      } if (b1.y - Neighbors[r].y == -1 && b1.x - Neighbors[r].x == 0) {
        grid[b1.x][b1.y].r = true;
        grid[b1.x][b1.y + 1].l = true;
      } if (b1.x - Neighbors[r].x ==  1 && b1.y - Neighbors[r].y == 0) {
        grid[b1.x][b1.y].t = true;
        grid[b1.x - 1][b1.y].b = true;
      }
      b1.x = (Neighbors[r].x);
      b1.y = (Neighbors[r].y);
      b1.history.push_back(grid[b1.x][b1.y]);
    }
    nb ++;
    std::cout << "size = " << Neighbors.size() << '\n';
    std::cout << "N° " << (nb) << "\n I did some " << (debug) << '\n';
  }
}


//problème sur le random
