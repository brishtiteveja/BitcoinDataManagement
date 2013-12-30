/*
 * CommonHeaders.h
 *
 *  Created on: Nov 2, 2013
 *      Author: zehadyzbdullahkhan
 */

#ifndef COMMONHEADERS_H_
#define COMMONHEADERS_H_
#endif /* COMMONHEADERS_H_ */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <boost/regex.hpp>


using namespace std;
using namespace boost;

typedef vector<int> vi;
typedef pair<string,int> si;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef pair<ii,int> iii;
typedef vector<iii> viii;
typedef pair<iii,int> iiii;
typedef vector<iiii> viiii;
typedef vector<si> vsi;
typedef vector<string> vs;

typedef map<string,int> msi;
typedef map<int,int> mii;
typedef map<int,double> mid;
typedef multimap<int, int> mmii;

#define tr(C,it) for(typeof(C.begin()) it = C.begin(); it != C.end();it++)
