#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <math.h>
#include <typeinfo>
#include <string>
#include <bitset>
#include "util.hpp"
#include "solver.hpp"

template <typename T>
bool vectorCompare(vector<T> a, vector<T> b);

bool vectorCompare(string a, string b);

template <typename T>
bool equationCompare(vector<vector<vector<T> > > formed, vector<vector<vector<T> > > desired);

void testEquasFormation();

