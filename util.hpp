//#ifndef __UTIL_H__
//#define __UTIL_H__
#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
//#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

typedef int coefdt;
typedef int orderdt; // normally integer

vector<string> mergeVector(vector<string> a, vector<string> b);

void printWordList(vector<string> list);

string toBinary(const int t, int len);

bool checkGap(string word, int gap, int windowsSize);

bool checkContained(vector<string> list, string cand);

vector<string> genString(string word, int bound);

vector<string> genWordList(int, int);

// polinomial function 
template <typename T>
T abss(T num) ;

template <typename T>
void printPoli(vector<T>);

template <typename T>
orderdt minIndex(vector<T>);

template <typename T>
vector<T> poliMulti(vector<T>, vector<T>);

template <typename T>
vector<T> poliAdd(vector<T>, vector<T>);

// matrix function
template<typename T>
void printMatrix(vector<vector<vector<T> > >);

template<typename T>
vector<vector<vector<T> > > subMatrix(vector<vector<vector<T> > >, int, bool);

template<typename T>
vector<T> matrixDet(vector<vector<vector<T> > >, int size);

template<typename T>
vector<T> getH(orderdt step, orderdt maxOrder, T);

template<typename T>
vector<T> getG(orderdt maxOrder, T);

template <typename T>
vector<T> power(orderdt order, T);

//template <typename T>
// template <typename T>
// orderdt minPower(vector<T> poli);

//template <typename T>
template <typename T>
void macclauExpand(vector<T>, vector<T>, orderdt order);

//#endif
