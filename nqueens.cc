#include <string.h>
#include <chrono>
#include <iostream>
using namespace std::chrono;

/*
 *
 *     NQUEENS BACK TRACKING
 *
 */

int N;
bool** board;
#define OPTIMIZED

#ifdef OPTIMIZED
bool* ld;  // left_diagonals
bool* rd;  // right diagonals
bool* rc;  // row check
#endif

void help() {
  printf(
      "nqueens\n\noptions:\n  --size Size of checker board (works well for N < "
      "30\n");
}

void printCheckerBoard() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

#ifdef OPTIMIZED
bool isSafe(int row, int col) {
  if (ld[row - col + N - 1] || rd[row + col] || rc[row]) {
    return false;
  }
  return true;
}
#else
// isSafe method is actually a time taking approach. A more optimized way is to
// mark the diagonals which are already occupied by a queen
// this approach gives result is normal time only uptill N = 27. If N > 27 it
// will take lot of time to calculate the result
bool isSafe(int row, int col) {
  // check the left size of the row
  for (int i = 0; i < col; i++) {
    if (board[row][i]) {
      return false;
    }
  }

  // check upper diagonal
  int i = row - 1;
  int j = col - 1;
  while (i >= 0 && j >= 0) {
    if (board[i][j]) {
      return false;
    }
    i--;
    j--;
  }

  // check lower diagonal
  i = row + 1;
  j = col - 1;
  while (i < N && j >= 0) {
    if (board[i][j]) {
      return false;
    }
    i++;
    j--;
  }

  return true;
}
#endif

bool solveNQueens(int col) {
  if (col >= N) {
    return true;
  }
  for (int i = 0; i < N; i++) {
    if (isSafe(i, col)) {
      board[i][col] = true;
#ifdef OPTIMIZED
      ld[i - col + N - 1] = rd[i + col] = rc[i] = true;
#endif
      if (solveNQueens(col + 1)) {
        return true;
      }
      board[i][col] = false;
#ifdef OPTIMIZED
      ld[i - col + N - 1] = rd[i + col] = rc[i] = false;
#endif
    }
  }

  return false;
}

/*
N     normal(ms)   Optimized(ms)
5       0          0
10      0          0
15      0          0
20      116        27
25      40         7
30      72440      12313
*/

int main(int argc, char** argv) {
  auto start = high_resolution_clock::now();
  if (argc < 2) {
    printf("Invalid arguments\n\n");
    help();
    return -1;
  } else if (strcmp("--help", argv[1]) == 0) {
    help();
    return -1;
  } else if (strcmp("--size", argv[1]) == 0) {
    if (argc > 2) {
      N = std::stoi(argv[2]);
    } else {
      printf("Invalid arguments\n\n");
      help();
      return -1;
    }
  }

  board = new bool*[N];
  for (int i = 0; i < N; i++) {
    board[i] = new bool[N];
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      board[i][j] = false;
    }
  }

#ifdef OPTIMIZED
  ld = new bool[2 * N + 1];
  rd = new bool[2 * N + 1];
  rc = new bool[N];
  for (int i = 0; i < 2 * N + 1; i++) {
    ld[i] = false;
    rd[i] = false;
  }
  for (int i = 0; i < N; i++) {
    rc[i] = false;
  }
#endif

  if (solveNQueens(0)) {
    printCheckerBoard();
  } else {
    printf("No solution exists for Nqueens problems with size %d\n", N);
  }

  auto duration =
      duration_cast<milliseconds>(high_resolution_clock::now() - start).count();
  printf("time taken to solve : %d milliseconds\n", (int)duration);

  return 0;
}
