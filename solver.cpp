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


// vector<vector<vector<long> > > initb4k3() {
//   vector<vector<long> > row1 = {
//     getG(3),
//     power(3),
//     poliAdd(power(3), power(2)),
//     power(3),
//     power(3),
//     power(4)
//   };
//   vector<vector<long> > row2 = {
//     power(4),
//     getG(4),
//     power(4),
//     poliAdd(poliAdd(power(4), power(3)), power(2)),
//     poliAdd(power(4), power(3)),
//     power(5)
//   };
//   vector<vector<long> > row3 = {
//     power(5),
//     poliAdd(power(5), power(4)),
//     poliAdd(poliAdd(power(5), power(3)), {(long)1}),
//     poliAdd(poliAdd(power(5), power(4)), power(1)),
//     poliAdd(poliAdd(power(5), power(4)), power(2)),
//     power(6)
//   };
//   vector<vector<long> > row4 = {
//     power(5),
//     poliAdd(poliAdd(power(5), power(4)), power(2)),
//     poliAdd(power(5), power(2)),
//     poliAdd(poliAdd(poliAdd(power(5), power(4)), power(3)), power(0)),
//     poliAdd(poliAdd(power(5), power(4)), power(1)),
//     power(6)
//   };
//   vector<vector<long> > row4 = {
// 
//   };
//   vector<vector<long> > row5 = {
// 
//   };
// }


vector<vector<vector<long> > > initb4k4(){
  vector<vector<long> > row1 = {
    {1,1,1,1,1},
    {0,0,0,0,1},
    {0,0,0,1,1},
    {0,0,0,0,1},
    {0,0,0,0,1},
    {0,0,0,0,0,1}
  };
  vector<vector<long> > row2 = {
    {0,0,0,0,0,1},
    {1,1,1,1,1,1},
    {0,0,0,0,0,1},
    {0,0,0,1,1,1},
    {0,0,0,0,1,1},
    {0,0,0,0,0,0,1}
  };
  vector<vector<long> > row3 = {
    {0,0,0,0,0,0,1},
    {0,0,0,0,1,1,1},
    {1,0,0,1,0,0,1},
    {0,1,0,0,1,1,1},
    {0,0,1,0,0,1,1},
    {0,0,0,0,0,0,1}
  };
  vector<vector<long> > row4 = {
    {0,0,0,0,0,1,1},
    {0,0,0,0,0,0,1},
    {0,0,1,0,0,1,1},
    {1,0,0,1,0,0,1},
    {0,0,0,0,1,0,1},
    {0,0,0,0,0,0,0,1}
  };
  vector<vector<long> > row5 = {
    {0,0,0,0,0,0,1},
    {0,0,0,0,0,1,1},
    {0,1,0,0,1,0,1},
    {0,0,0,0,0,1,1},
    {1,0,0,1,0,1,1},
    {0,0,0,0,0,0,0,1}
  };
  return {row1, row2, row3, row4, row5};
}

vector<vector<vector<long> > > initb4k3_new() {
  vector<vector<long> > row1 = {
    {1,1,1,1},
    {0,0,0,1},
    {0,0,1,1},
    {0,0,0,1},
    {0,0,0,1},
    {0,0,0,0,1}
  };
  vector<vector<long> > row2 = {
    {0,0,0,0,1},
    {1,1,1,1,1},
    {0,0,0,0,1},
    {0,0,1,1,1},
    {0,0,0,1,1},
    {0,0,0,0,0,1}
  };
  vector<vector<long> > row3 = {
    {0,0,0,0,0,1},
    {0,0,0,0,1,1},
    {1,0,0,1,0,1},
    {0,1,0,0,1,1},
    {0,0,1,0,1,1},
    {0,0,0,0,0,0,1}
  };
  vector<vector<long> > row4 = {
    {0,0,0,0,0,1},
    {0,0,0,1,1,1},
    {0,0,1,0,0,1},
    {1,0,0,1,1,1},
    {0,1,0,0,1,1},
    {0,0,0,0,0,0,1}
  };
  vector<vector<long> > row5 = {
    {0,0,0,0,1,1},
    {0,0,0,0,0,1},
    {0,1,0,0,1,1},
    {0,0,1,0,0,1},
    {1,0,0,1,0,1},
    {0,0,0,0,0,0,1}
  };
  return {row1, row2, row3, row4, row5};
}


vector<long> getDeterminant(vector<vector<vector<long> > > matrix, int pos) {
  vector<vector<vector<long> > > subMat = subMatrix(matrix, pos, false);
  int sign = pow(-1, pos);
  return poliMulti({sign}, matrixDet(subMat,  subMat.size()));
}

// vector<long> solve(vector<vector<vector<long> > > matrix, int pos) {
void solve(vector<vector<vector<long> > > matrix, int pos) {
  cout << endl << "RUNNING" << endl;
  vector<long> det = getDeterminant(matrix, pos);
  printPoli(det);
  // vector<long>().swap(det);
}
vector<vector<vector<long> > > initb3k2(){
  vector<vector<long> > row1 = {
    {1,1,1},
    {0,0,1},
    {0,0,0,1}
  };
  vector<vector<long> > row2 = {
    {0,0,0,1},
    {1,1,1,1},
    {0,0,0,0,1}
  };
  return {row1, row2};
}

void solvebk(int b, int k) {
  vector<vector<vector<long> > > matrix, mat;
  vector<long> det, sum, nume, deno;
  sum = {0,0};
  if (b == 4 && k == 3) {
    matrix = initb4k3_new();
  } else if (b == 4 && k == 4) {
    matrix = initb4k4();
  } else if (b == 3 && k == 2) {
    matrix = initb3k2();
  } else return;
  cout << endl << "SOLVE FOR b=" << b << ", k=" << k << endl;
  for (int pos = 0; pos < matrix.size(); pos++) {
    det = getDeterminant(matrix, pos);
    cout << "RUNNING: "  << pos << " == " ;
    printPoli(det);
    cout << endl;
    sum = poliAdd(sum, poliMulti({-2}, det));
  }
  nume = getDeterminant(matrix, matrix.size());
  cout << endl << "NUMERATOR WEIGHT" <<  endl;
  printPoli(sum);
  cout << endl << "DENOMIRATOR WEIGHT" <<  endl;
  printPoli(nume);

  deno = poliAdd(poliMulti({1, -2}, nume), sum);

  int zeroNum = 0, zeroDen = 0;
  for (int num : nume) if (num == 0) zeroNum ++; else break;
  for (int num : deno) if (num == 0) zeroDen ++; else break;

  for (int i = 0; i < min(zeroNum, zeroDen); i++) {
    nume.erase(nume.begin());
    deno.erase(deno.begin());
  }
  cout << endl << "NUMERATOR GF" <<  endl;
  printPoli(nume);
  cout << endl << "DENOMIRATOR GF" <<  endl;
  printPoli(deno);

}

