/*
 * main.c

 *
 *  Created on: Nov 2, 2013
 *      Author: zehadyzbdullahkhan
 */
#include "RichGetsRicher.h"
#include "ExtractFromBlockExplorer.h"
#include "CreateBitcoinGraph.h"
#include "ComputeOverBitcoinData.h"
#include "IdentifyBitcoinUser.h"
#include "IdentifyBitcoinUserEfficient.h"
#include "CommonHeaders.h"


string MAC_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/Bitcoin_Data/";
string MAC_BITCOIN_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/";
string MAC_BLOCK_PATH ="/Users/zehadyzbdullahkhan/git/BitcoinDataManagement/BitcoinDataManagement/blocks/";
string WIN_PATH ="C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/";


int main(){
	//numberOfAddressesOverWeeks();
	//run extractor for block explorer to create graph
	//createGraph();
	//runExtractor();
	//compute();
	IdentifyBitcoinUserEfficient userContractor;
	userContractor.identifyBitcoinUser();
}


