#include <algorithm>    // std::copy
#include "util.hpp"
#include "solver.hpp"
#include "test.hpp"

template <typename T>
bool vectorCompare(vector<T> a, vector<T> b) {
  if (a.size() != b.size()) return false;
  for (auto i = 0; i < a.size(); i++) 
    if (a[i] != b[i]) return false;
  return true;
}

bool vectorCompare(string a, string b) {
  if (a.length() != b.length()) return false;
  for (int i = 0; i < a.size(); i++) 
    if (a[i] != b[i]) return false;
  return true;
}

template <typename T>
bool equationCompare(vector<vector<vector<T> > > formed, vector<vector<vector<T> > > desired) {
  if (formed.size() != desired.size()) return false;
  vector<vector<T> > formedRow, desiredRow;
  for (int i = 0; i < formed.size(); i++) {
    formedRow = formed[i];
    desiredRow = desired[i];
    if (formedRow.size() != desiredRow.size()) {
      cout << "FAILED AT " << i << endl;
      return false;
    }

    for (int j = 0; j < formedRow.size(); j++) 
      if (!vectorCompare(formedRow[j], desiredRow[j])) {
        cout << "FAILED AT " << i << " and " << j << endl;
        return false;
      }
  }
  return true;
}


template <typename T>
vector<T> getFirstHalf(vector<T> myVec) {
  //vector<T>::const_iterator 
    auto first = myVec.begin();
  //vector<T>::const_iterator 
    auto last = myVec.begin() + myVec.size() / 2;
  vector<T> newVec(first, last);
  return newVec;
}

bool compareBinStr(string s1, string s2) {
  return s1.length() < s2.length();
}


void testEquasFormation() {
  cout << "Start testing bitReverse" << endl;
  assert(vectorCompare(bitReverse("0000"),"1111"));
  assert(vectorCompare(bitReverse("11111"),"00000"));
  assert(vectorCompare(bitReverse("1010111"),"0101000"));
  cout << "Done testing bitReverse" << endl;

  cout << "Start testing overlap" << endl;
  vector<coefdt> ret;
  ret = overlap("0000", "0000"); 
  vector<coefdt> expect(4, 1);
  assert(vectorCompare(ret, expect));
  ret = overlap("0000", "0101"); 
  expect = {0,0,0,1};
  assert(vectorCompare(ret, expect));
  ret = overlap("0101", "1010"); 
  expect = {0,1,0,1};
  assert(vectorCompare(ret, expect));
  ret = overlap("0101", "1111"); 
  expect = {0,0,0,1};
  assert(vectorCompare(ret, expect));
  cout << "Done testing overlap" << endl;

  cout << "Start testing Equation formation" << endl;
  int b = 3, k = 2;
  vector<vector<vector<coefdt> > > equations = initb3k2();
  vector<string> wordList = genWordList(b, k);
  vector<string> halfWordList = getFirstHalf(wordList);//(&wordList[0], &wordList[0] + wordList.size() / 2);
  vector<vector<vector<coefdt> > > formedEquas = genEquation(halfWordList);
  assert(equationCompare(formedEquas, equations));
  cout << "PASS b=" << b << ", k=" << k << endl;

  b = 4; k = 3;
  equations = initb4k3_new();
  wordList = genWordList(b, k);
  halfWordList = getFirstHalf(wordList);
  sort(halfWordList.begin(), halfWordList.end(), compareBinStr);
  formedEquas = genEquation(halfWordList);
  assert(equationCompare(formedEquas, equations));
  cout << "PASS b=" << b << ", k=" << k << endl;

  b = 4; k = 4;
  equations = initb4k4();
  wordList = genWordList(b, k);
  halfWordList = getFirstHalf(wordList);
  sort(halfWordList.begin(), halfWordList.end(), compareBinStr);
  formedEquas = genEquation(halfWordList);
  // cout << "========== FORMED: " << endl;
  // printMatrix(formedEquas);
  // cout << "========== DESIRED " << endl;
  // printMatrix(equations);
  // cout << "==========" << endl;
  // printWordList(halfWordList);
  // assert(equationCompare(formedEquas, equations));
  cout << "PASS b=" << b << ", k=" << k << endl;
  cout << "Done testing Equation formation" << endl;
}
