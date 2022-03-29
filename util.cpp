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
  for (long i = 0; i < pow(2, k); i++) {
    model.push_back(toBinary(i, k));
  }
  vector <string> forbiddenWords;
  vector <string> tmp;
  for (string word: model) {
    forbiddenWords = mergeVector(forbiddenWords, genString(word, b));
  }
  return forbiddenWords;
}

 coefdt abss(coefdt num) {if (num >= 0) return num; return -num;}
void printPoli(vector<coefdt> poli) {
  for (expdt order = poli.size()-1; order >= 0; order --) {
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
expdt minIndex(vector<T> vec) {
  for (expdt i = 0; i < vec.size(); i++) {
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
vector<coefdt> poliMulti(vector<coefdt> a, vector<coefdt> b) {
  a = trimZero(a);
  b = trimZero(b);
  vector<coefdt> c(a.size() + b.size() - 1, 0);
  for (expdt ord = 0; ord < c.size(); ord ++) {
    for (expdt runOrd = 0; runOrd <= ord ; runOrd ++) {
      if (runOrd < a.size() && ord - runOrd < b.size())
        c[ord] += a[runOrd] * b[ord - runOrd];
    }
  }
  return c;
}

//template<typename T>
vector<coefdt> poliAdd(vector<coefdt> a, vector<coefdt> b) {
  vector<coefdt> c(max(a.size(), b.size()), 0);
  for (expdt ord = 0; ord < c.size(); ord ++) {
    if (ord < a.size()) c[ord] += a[ord];
    if (ord < b.size()) c[ord] += b[ord];
  }
  
  c = trimZero(c);
  return  c;
}

void printMatrix(vector<vector<vector<coefdt> > > matrix) {
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

vector<vector<vector<coefdt> > > subMatrix(vector<vector<vector<coefdt> > > matrix, int pos, bool removeFirst) {
  vector<vector<vector<coefdt> > > newMatrix;
  if (removeFirst) {
    matrix.erase(matrix.begin());
  }
  int maxr = matrix.size(),
      maxc = matrix[0].size();
  for (int r = 0; r < maxr; r++) {
    vector<vector<coefdt> > tmp;
    for (int c = 0; c < maxc; c++) {
      if (c != pos) tmp.push_back(matrix[r][c]);
    }
    newMatrix.push_back(tmp);
  }
  return newMatrix;
}

vector<coefdt> matrixDet(vector<vector<vector<coefdt> > > matrix, int size){
  if (size == 1) {
    vector<coefdt> elem = matrix[0][0];
    return elem;
  }
  vector<coefdt> det, coef, res;
  vector<coefdt> result = {0};
  vector<vector<vector<coefdt> > > subMat;
  vector<vector<coefdt> > firstRow = matrix[0];
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
vector<coefdt> getH(expdt step, expdt maxOrder) {
  vector<coefdt> result(maxOrder + 1, (coefdt) 0);
  for (expdt i = 0; maxOrder - step * i >= 0; i++) {
    result[maxOrder - step * i] = (coefdt) 1;
  }
  return result;
}

vector<coefdt> getG(expdt maxOrder) {
  vector<coefdt> result(maxOrder + 1, (coefdt) 0);
  for (expdt i = 0; maxOrder - i >= 0; i++) {
    result[maxOrder - i] = (coefdt) 1;
  }
  return result;
}

vector<coefdt> power(expdt order){
  vector<coefdt> result(order + 1, 0);
  result[order] = 1;
  return result;
}

string bitReverse(string str) {
  string out = str;
  int len = str.length();
  for (int i = 0; i < len; i++) out[i] = str[i] == '1' ? '0' : '1';
  out[len] = '\0';
  return out;
}

vector<coefdt> overlap(string first, string last) {
  int lenFirst = first.length(), lenLast = last.length();
  vector<coefdt> overl(lenFirst, 0);
  string subFirst, subLast;
  for (int i = lenFirst - 1; i >= 0 && lenFirst - 1 - i < lenLast; i--) {
    subFirst = first.substr(i, lenFirst - i);
    subLast  = last.substr(0, lenFirst - i);
    if (subFirst.compare(subLast) == 0) 
      overl.at(i) = (coefdt) 1;
  }
  return overl;
}


vector<vector<vector<coefdt> > > genEquation(vector<string> wordList) {
  vector<vector<vector<coefdt> > > ret;
  for (string word : wordList) {
    vector<vector<coefdt> > row = {};
    for (string wordV : wordList) {
      // original word
      vector<coefdt> o1 = overlap(word, wordV);
      // reversed word
      vector<coefdt> o2 = overlap(word, bitReverse(wordV));
      // combine two equation
      o1 = poliAdd(o1, o2);
      row.push_back(o1);
    }
    row.push_back(power((coefdt)word.length()));
    ret.push_back(row);
  }
  return ret;
}











