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
  //assert(overlap("0000", "0101") == {0});
  //assert(overlap("1111", "0101") == {0,0,0,1});

  cout << "Done testing overlap" << endl;
}
