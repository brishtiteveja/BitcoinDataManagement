/*
 * CreateBitcoinGraph.h
 *
 *  Created on: Jan 1, 2014
 *      Author: zehadyzbdullahkhan
 */

#ifndef CREATEBITCOINGRAPH_H_
#define CREATEBITCOINGRAPH_H_

#include "CommonHeaders.h"

template<class K, class V>
typename multimap<K, V>::const_iterator find_pair(const multimap<K, V>& map, const pair<K, V>& pair);
template<class T1, class T2>
bool insert_if_pair_not_present(multimap<T1,T2> mmap,pair<T1,T2> pair);
void createGraph();

#endif /* CREATEBITCOINGRAPH_H_ */
