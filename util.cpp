#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
//#include <boost/multiprecision/cpp_int.hpp>
#include <algorithm>
#include <math.h>
#include "util.hpp"
using namespace std;


vector<string> mergeVector(vector<string> a, vector<string> b) {
  vector<string> c = a;
  for (auto v : b) c.push_back(v);
  return c;
}

void printWordList(vector<string> list) {
    for (string word : list) {
      cout << word << endl;
  }
}

string toBinary(const int t, int len)
{
  string s = "";
  //int n = sizeof(long)*8;
  int n = len;
  for(int i=n-1; i>=0; i--) {
    s += (t & (1 << i))?"1":"0";
  }
  return s;
}

bool checkGap(string word, int gap, int windowsSize) {
  for (int i = 0; i < windowsSize && i + gap < word.length(); i++) {
    if (word[i] != word[i+gap]) return false;
  }
  return true;
}

bool checkContained(vector<string> list, string cand) {
  for(string st : list) if (cand.find(st) != std::string::npos) return true;
  return false;
}

vector<string> genString(string word, int bound) {
  vector <string> result;
  int wl = word.length();
  for(int gap = 1; gap < bound; gap++){
    string newWord = word;
    for (int i = wl - gap; i <= wl - 1; i++) newWord = newWord + word[i];
    if (checkGap(newWord, gap, wl) && !checkContained(result, newWord))  {
      result.push_back(newWord);
    }
  }
  return result;
}

vector<string> genWordList(int b, int k) {
  vector<string> model;
  // get word list
  for (int i = 0; i < pow(2, k); i++) {
    model.push_back(toBinary(i, k));
  }
  vector <string> forbiddenWords;
  vector <string> tmp;
  for (string word: model) {
    forbiddenWords = mergeVector(forbiddenWords, genString(word, b));
  }
  return forbiddenWords;
}

template <typename T>
T abss(T num) {if (num >= 0) return num; return -num;}

// std::ostream& operator << (std::ostream& dest, __int128_t value) {
//     std::ostream::sentry s(dest);
//     if (s) {
//         __uint128_t tmp = value<0?-value:value;
//         char buffer[128];
//         char* d = std::end(buffer);
//         do {
//             -- d;
//             *d = "0123456789"[tmp%10];
//             tmp/=10;
//         }while(tmp!=0);
//         if(value<0) {
//             --d;
//             *d = '-';
//         }
//         int len = std::end(buffer)-d;
//         if (dest.rdbuf()->sputn(d,len)!=len) {
//             dest.setstate(std::ios_base::badbit);
//         }
//     }
//     return dest;
// }

template <typename T>
void printPoli(vector<T> poli) {
  for (orderdt order = poli.size()-1; order >= 0; order --) {
    // print sign
    if (poli.at(order) == 0) continue;
    if (poli.at(order) < 0) cout << "-";
    else if (order != poli.size() - 1) cout << "+"; // poli.at(order) > 0
    // print coef
    if ((poli.at(order) != 1 && poli.at(order) != -1) || order == 0) cout << abss(poli.at(order));
    // print variable
    if (order > 0) cout << "x";
    if (order > 9) cout << "^" << order << "";
    else if (order > 1) cout << "^" << order;
  }
}

// polinomoal function
template <typename T>
orderdt minIndex(vector<T> vec) {
  for (orderdt i = 0; i < vec.size(); i++) {
    if (vec.at(i) != (T) 0) return i;
  }
  return -1;
}

template<typename T>
vector<T> trimZero(vector<T> vec) {
  // trim last elements if they are zeros
  if (vec.size() == 0) return {(T) 0};
  while(vec.size() > 1 && vec[vec.size()-1] == (T) 0) vec.pop_back();
  return vec;
}

template<typename T>
vector<T> poliMulti(vector<T> a, vector<T> b) {
  a = trimZero(a);
  b = trimZero(b);
  vector<T> c(a.size() + b.size() - 1, (T) 0);
  for (orderdt ord = 0; ord < c.size(); ord ++) {
    for (orderdt runOrd = 0; runOrd <= ord ; runOrd ++) {
      if (runOrd < a.size() && ord - runOrd < b.size())
        c[ord] += a[runOrd] * b[ord - runOrd];
    }
  }
  return c;
}

template<typename T>
vector<T> poliAdd(vector<T> a, vector<T> b) {
  vector<T> c(max(a.size(), b.size()), 0);
  for (unsigned long long ord = 0; ord < c.size(); ord ++) {
    if (ord < a.size()) c[ord] += a[ord];
    if (ord < b.size()) c[ord] += b[ord];
  }
  
  c = trimZero(c);
  return  c;
}

template<typename T>
void printMatrix(vector<vector<vector<T> > > matrix) {
  // only up to 5 row, 6 column by now
  int row = matrix.size();
  for (int r = 0; r < row; r++) {
    int col = matrix[r].size();
    for (int c = 0; c < col; c++) {
      printPoli(matrix[r][c]);
      cout << ",\t";
    }
    cout << endl;
  }
}

template<typename T>
vector<vector<vector<T> > > subMatrix(vector<vector<vector<T> > > matrix, int pos, bool removeFirst) {
  vector<vector<vector<T> > > newMatrix;
  if (removeFirst) {
    matrix.erase(matrix.begin());
  }
  int maxr = matrix.size(),
      maxc = matrix[0].size();
  for (int r = 0; r < maxr; r++) {
    vector<vector<T> > tmp;
    for (int c = 0; c < maxc; c++) {
      if (c != pos) tmp.push_back(matrix[r][c]);
    }
    newMatrix.push_back(tmp);
  }
  return newMatrix;
}

template<typename T>
vector<T> matrixDet(vector<vector<vector<T> > > matrix, int size){
  if (size == 1) {
    vector<T> elem = matrix[0][0];
    return elem;
  }
  vector<T> det, coef, res;
  vector<T> result = {(T)0};
  vector<vector<vector<T> > > subMat;
  vector<vector<T> > firstRow = matrix[0];
  int sign = 1;
  for(int i = 0; i < size; i++) {
    subMat = subMatrix(matrix, i, true);
    det = matrixDet(subMat, size-1);
    coef = firstRow[i];
    res = poliMulti(poliMulti({sign}, coef), det);
    result = poliAdd(result, res);
    sign *= -1;
  }
  return result;
}

// mathematics fulction
template<typename T>
vector<T> getH(int step, int maxOrder, T datatype) {
  vector<T> result(maxOrder + 1, (T) 0);
  for (orderdt i = 0; maxOrder - step * i >= 0; i++) {
    result[maxOrder - step * i] = (T) 1;
  }
  return result;
}

template<typename T>
vector<T> getG(int maxOrder, T datatype) {
  //return poliAdd({1}, getH(1, maxOrder));
  // return (vector<T>) getH(1, maxOrder);
  vector<T> result(maxOrder + 1, (T) 0);
  for (orderdt i = 0; maxOrder - i >= 0; i++) {
    result[maxOrder - i] = (T) 1;
  }
  return result;
}

template <typename T>
vector<T> power(orderdt order, T datatype){
  vector<T> result(order + 1, 0);
  result[order] = (T) 1;
  return result;
}

template <typename T>
orderdt minOrder(vector<T> poli) {
  for (orderdt i = 0; i < poli.size(); i++) {
    if (poli.at(i) != 0) return i;
  }
  return (orderdt) poli.size();
}

template <typename T>
void macclauExpand(vector<T> nume, vector<T> deno, orderdt order) {
  assert(order >= 0);
  orderdt minPowerDeno = minOrder(deno);
  T quot;
  int count = 0;

  for (orderdt i = 0; i <= order; i++) {
    orderdt minPowerNume = minOrder(nume);
    quot = nume.at(minPowerNume) / deno.at(minPowerDeno);
    if (i >= (count + 1) * order / 10) {
      cout << "quot: " << quot << " at i = " << i  << "rate is: " << log(quot) / log(2) / i << endl;
      count ++;
    }
      //<< ", nume: " << nume.at(minPowerNume)
      //<< ", deno: " << deno.at(minPowerDeno) << endl;
    //printPoli(nume);
    nume = poliAdd(nume, poliMulti(deno, poliMulti({-quot}, power(minPowerNume - minPowerDeno, quot))));
  }
}


