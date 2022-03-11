#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
using namespace std;


vector<string> mergeVector(vector<string> a, vector<string> b);

void printWordList(vector<string> list);

string toBinary(const int t, int len);

bool checkGap(string word, int gap, int windowsSize);

bool checkContained(vector<string> list, string cand);

vector<string> genString(string word, int bound);

vector<string> genWordList(int, int);

// polinomial function 
void printPoli(vector<long>);

template <typename T>
int minIndex(vector<T>);

vector<long> poliMulti(vector<long>, vector<long>);

vector<long> poliAdd(vector<long>, vector<long>);

// matrix function
void printMatrix(vector<vector<vector<long> > >);

vector<vector<vector<long> > > subMatrix(vector<vector<vector<long> > >, int, bool);

vector<long> matrixDet(vector<vector<vector<long> > >, int size);

vector<long> getH(int step, int maxOrder);

vector<long> getG(int maxOrder);

vector<long> power(int order);



