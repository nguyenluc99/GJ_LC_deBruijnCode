#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
using namespace std;


typedef long long coefdt;
typedef long long expdt;

vector<string> mergeVector(vector<string> a, vector<string> b);

void printWordList(vector<string> list);

string toBinary(const int t, int len);

bool checkGap(string word, int gap, int windowsSize);

bool checkContained(vector<string> list, string cand);

vector<string> genString(string word, int bound);

vector<string> genWordList(int, int);

// polinomial function 
void printPoli(vector<coefdt>);

template <typename T>
expdt minIndex(vector<T>);

vector<coefdt> poliMulti(vector<coefdt>, vector<coefdt>);

vector<coefdt> poliAdd(vector<coefdt>, vector<coefdt>);

// matrix function
void printMatrix(vector<vector<vector<coefdt> > >);

vector<vector<vector<coefdt> > > subMatrix(vector<vector<vector<coefdt> > >, int, bool);

vector<coefdt> matrixDet(vector<vector<vector<coefdt> > >, int size);

vector<coefdt> getH(expdt step, expdt maxOrder);

vector<coefdt> getG(expdt maxOrder);

vector<coefdt> power(expdt order);

string bitReverse(string);

vector<coefdt> overlap(string, string);

vector<vector<vector<coefdt> > > genEquation(vector<string> wordList);

