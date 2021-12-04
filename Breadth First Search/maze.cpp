/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {


   int rows, cols;
   char** mymaze=NULL;

   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }

   mymaze = read_maze(argv[1], &rows, &cols);


   if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
   }

   int result = maze_search(mymaze, rows, cols); // <--- TASK: CHANGE THIS


   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // deleting all memory that read_maze allocated

   for (int i = 0; i < rows; i++){
     delete[] mymaze[i];
   }
   delete[] mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
  // finding the start/finish coordinates and checking maze validity
  Location start, end, backtrace;
  bool found=false;
  int startNum = 0;
  int endNum = 0;

  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      if (maze[i][j] != 'S' && maze[i][j] != 'F' && maze[i][j] != '#' && maze[i][j] != '.'){
        cout << "Error, input format incorrect." << endl;
        return -1;
      }
      if (maze[i][j] == 'S'){
        start.row = i; start.col = j; startNum++;
      } else if (maze[i][j] == 'F'){
        end.row = i; end.col = j; endNum++;
      }
    }
  }
  if (startNum != 1 || endNum != 1) {
    return -1;
  }

  // setup and initialize queue, predecessor
  Queue q(rows * cols);
  Location** pre = new Location*[rows];
  for(int i=0;i<rows;i++){
    pre[i] = new Location[cols];
  }

  char** crumbs = new char*[rows];
  for(int i=0;i<rows;i++){
    crumbs[i] = new char[cols];
  }
  // initializing crumbs (the visited 2d array)
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      crumbs[i][j] = maze[i][j];
    }
  }

  q.add_to_back(start);
  while (!(q.is_empty()) && !found){
    Location temp = q.remove_from_front();

    // directions in the order of north, west, south, east
    Location directions[4];
    // establishing the 4 direction coordinates to search
    directions[0].row = temp.row - 1; directions[0].col = temp.col;
    directions[1].row = temp.row; directions[1].col = temp.col - 1;
    directions[2].row = temp.row + 1; directions[2].col = temp.col;
    directions[3].row = temp.row; directions[3].col = temp.col + 1;

    for (int i = 0; i < 4; i++){
      if (directions[i].row >= 0 && directions[i].row < rows
         && directions[i].col >= 0 && directions[i].col < cols
         && crumbs[directions[i].row][directions[i].col] == '.'){

        q.add_to_back(directions[i]);
        crumbs[directions[i].row][directions[i].col] = 'x';
        pre[(directions[i]).row][(directions[i]).col] = temp;

      } else if (directions[i].row >= 0 && directions[i].row < rows
         && directions[i].col >= 0 && directions[i].col < cols
         && crumbs[directions[i].row][directions[i].col] == 'F') {
        pre[(directions[i]).row][(directions[i]).col] = temp;
        found = true;
        backtrace.row = end.row;
        backtrace.col = end.col;
        break;

      }
    }
  }

  if (found){
    while(!(backtrace.row == start.row && backtrace.col == start.col)){
      if (maze[backtrace.row][backtrace.col] == '.'){
        maze[backtrace.row][backtrace.col] = '*';
      }
      int temprow = backtrace.row;
      backtrace.row = (pre[backtrace.row][backtrace.col]).row;
      backtrace.col = (pre[temprow][backtrace.col]).col;
    }

    // deallocating memory
    for (int i = 0; i < rows; i++){
      delete[] crumbs[i];
      delete[] pre[i];
    }
    delete[] crumbs;
    delete[] pre;

    return 1;
  } else { // path not found, return 0 and deallocate
    for (int i = 0; i < rows; i++){
      delete[] crumbs[i];
      delete[] pre[i];
    }
    delete[] crumbs;
    delete[] pre;
    
    return 0;
  }
}
