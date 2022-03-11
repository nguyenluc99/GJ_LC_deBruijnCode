#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
#include "solver.hpp"
#include "util.hpp"
using namespace std;

vector<vector<vector<long> > > init(int k) {
  vector<vector<long> > row1 = {
    getG(k), 
    power(k), 
    poliAdd(power(k), power(k-1)), 
    power(k), 
    power(k), 
    power(k+1)
  };
  // can use either row1 or row12
  vector<vector<long> > row12;
  for (vector<long> r : row1) {
    row12.push_back(poliMulti(r, {1, -1}));
  }

  vector<vector<long> > row2 = {
    power(k+1), 
    getH(2, k), 
    power(k+1), 
    poliAdd(power(k+1), power(k)), 
    poliAdd(power(k+1), power(k)),
    power(k+2)
  };
  vector<vector<long> > row3 = {
    power(k+2), 
    poliAdd(power(k+2), power(k+1)), 
    getH(3, k), 
    poliAdd(power(k+2), power(k+1)), 
    poliAdd(power(k+2), power(k+1)),
    power(k+3)
  };
  vector<vector<long> > row4 = { 
    power(k+2), 
    poliAdd(poliAdd(power(k+2), power(k+1)), power(k)), 
    power(k+2), 
    poliAdd(getH(3, k), power(k+2)), 
    poliAdd(power(k+2), power(k+1)), 
    power(k+3)
  };
  vector<vector<long> > row5 = {
    poliAdd(power(k+2), power(k+1)), 
    power(k+2), 
    poliAdd(power(k+2), power(k+1)), 
    power(k+2), 
    poliAdd(getH(3, k), power(k+2)), 
    power(k+3)
  };
  return {row1, row2, row3, row4, row5};
}

vector<long> getDeterminant(vector<vector<vector<long> > > matrix, int pos) {
  vector<vector<vector<long> > > subMat = subMatrix(matrix, pos, false);
  int sign = pow(-1, pos+1);
  return poliMulti({sign}, matrixDet(subMat,  subMat.size()));
}

// vector<long> solve(vector<vector<vector<long> > > matrix, int pos) {
void solve(vector<vector<vector<long> > > matrix, int pos) {
  cout << endl << "RUNNING" << endl;
  vector<long> det = getDeterminant(matrix, pos);
  printPoli(det);
  // vector<long>().swap(det);
}

//vector<long> solveb4(int k) {
void solveb4(int k) {
  const int b = 4;
  assert( b < pow(2, k));
  vector<vector<vector<long> > > matrix, mat;
  vector<long> det, sum, nume, deno;
  // forbidWords = genWordList(b, k);

  matrix = init(k);
  cout << matrix.size() << endl;

 //  mat = {
 //    { {1},  {2}, {3, 1}, {3, 2, 3, 4}, {0, 2, 3}, {1,2,3}},
 //    { {2},  {3, 2}, {10}, {2, 2, 10}, {1, 2, 3}, {0,0,1}},
 //    { {2, 1},  {3, 1}, {10, 1}, {1, 2}, {2, 3}, {2,0,0,1}},
 //    { {2, 2, 3, 4, 5},  {3, 1, 2, 3}, {10, 1}, {1, 2, 1}, {1, 2, 3}, {2}},
 //    { {2, 1, 3, 4, 5},  {3, 0, 2, 3}, {1, 1}, {2, 1}, {1, 2, 3}, {1}}
 //  };

  printMatrix(matrix);
  for (int pos = 0; pos < 4; pos++) {
    cout << "RUNNING: "  << pos << endl;
    det = getDeterminant(matrix, pos);
    sum = poliAdd(sum, poliMulti({-2}, det));
  }
  nume = getDeterminant(matrix, 4);
  cout << "SUM DET" << endl;
  printPoli(sum);
  deno = poliAdd(poliMulti({1, -2}, nume), sum);
  // shorten:
  int zeroNum = 0, zeroDen = 0;
  for (int num : nume) if (num == 0) zeroNum ++; else break;
  for (int num : deno) if (num == 0) zeroDen ++; else break;
  // zeroNum = minIndex(nume);
  // zeroDen = minIndex(deno);

  for (int i = 0; i < min(zeroNum, zeroDen); i++) {
    nume.erase(nume.begin());
    deno.erase(deno.begin());
  }
  cout << endl << "NUMERATOR" <<  endl;
  printPoli(nume);
  cout << endl << "DENOMIRATOR" <<  endl;
  printPoli(deno);

}
