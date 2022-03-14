#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
#include "util.hpp"
#include "solver.hpp"
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Insert b, k " << endl;
    exit(1);
  }
  int b = (int) atoi(argv[1]);
  int k = (int) atoi(argv[2]);
  cout << "b = " << b << ", k = " << k << endl;
  assert( b < pow(2, k));

  solvebk(4,3);
  solvebk(3,2);
  return 0;

}