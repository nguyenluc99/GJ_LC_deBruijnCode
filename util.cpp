#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
#include <algorithm>
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

long abss(long num) {if (num >= 0) return num; return -num;}
void printPoli(vector<long> poli) {
  for (int order = poli.size()-1; order >= 0; order --) {
    // print sign
    if (poli.at(order) == 0) continue;
    if (poli.at(order) < 0) cout << "-";
    else if (order != poli.size() - 1) cout << "+"; // poli.at(order) > 0
    // print coef
    if ((poli.at(order) != 1 && poli.at(order) != -1) || order == 0) cout << abss(poli.at(order));
    // print variable
    if (order > 0) cout << "x";
    if (order > 9) cout << "^{" << order << "}";
    else if (order > 1) cout << "^" << order;
  }
}

// polinomoal function
template <typename T>
int minIndex(vector<T> vec) {
  for (int i = 0; i < vec.size(); i++) {
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

//template<typename T>
vector<long> poliMulti(vector<long> a, vector<long> b) {
  a = trimZero(a);
  b = trimZero(b);
  vector<long> c(a.size() + b.size() - 1, 0);
  for (int ord = 0; ord < c.size(); ord ++) {
    for (int runOrd = 0; runOrd <= ord ; runOrd ++) {
      if (runOrd < a.size() && ord - runOrd < b.size())
        c[ord] += a[runOrd] * b[ord - runOrd];
    }
  }
  return c;
}

//template<typename T>
vector<long> poliAdd(vector<long> a, vector<long> b) {
  vector<long> c(max(a.size(), b.size()), 0);
  for (int ord = 0; ord < c.size(); ord ++) {
    if (ord < a.size()) c[ord] += a[ord];
    if (ord < b.size()) c[ord] += b[ord];
  }
  
  c = trimZero(c);
  return  c;
}

void printMatrix(vector<vector<vector<long> > > matrix) {
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

vector<vector<vector<long> > > subMatrix(vector<vector<vector<long> > > matrix, int pos, bool removeFirst) {
  vector<vector<vector<long> > > newMatrix;
  if (removeFirst) {
    matrix.erase(matrix.begin());
  }
  int maxr = matrix.size(),
      maxc = matrix[0].size();
  for (int r = 0; r < maxr; r++) {
    vector<vector<long> > tmp;
    for (int c = 0; c < maxc; c++) {
      if (c != pos) tmp.push_back(matrix[r][c]);
    }
    newMatrix.push_back(tmp);
  }
  return newMatrix;
}

vector<long> matrixDet(vector<vector<vector<long> > > matrix, int size){
  if (size == 1) {
    vector<long> elem = matrix[0][0];
    return elem;
  }
  vector<long> det, coef, res;
  vector<long> result = {0};
  vector<vector<vector<long> > > subMat;
  vector<vector<long> > firstRow = matrix[0];
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
vector<long> getH(int step, int maxOrder) {
  vector<long> result(maxOrder + 1, (long) 0);
  for (int i = 0; maxOrder - step * i >= 0; i++) {
    result[maxOrder - step * i] = (long) 1;
  }
  return result;
}

vector<long> getG(int maxOrder) {
  //return poliAdd({1}, getH(1, maxOrder));
  // return (vector<long>) getH(1, maxOrder);
  vector<long> result(maxOrder + 1, (long) 0);
  for (int i = 0; maxOrder - i >= 0; i++) {
    result[maxOrder - i] = (long) 1;
  }
  return result;
}

vector<long> power(int order){
  vector<long> result(order + 1, 0);
  result[order] = 1;
  return result;
}


