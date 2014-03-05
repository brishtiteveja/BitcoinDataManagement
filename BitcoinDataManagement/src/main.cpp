/*
 * main.c

 *
 *  Created on: Nov 2, 2013
 *      Author: zehadyzbdullahkhan
 */

#include "CommonHeaders.h"
#include "RichGetsRicher.h"
#include "ExtractFromBlockExplorer.h"
#include "CreateBitcoinGraph.h"
#include "ComputeOverBitcoinData.h"
#include "IdentifyBitcoinUser.h"
#include "IdentifyBitcoinUserEfficient.h"
#include "IdentifyBitcoinUserNew.h"
#include "FormatFile.h"
#include "ComputeTemporalBalance.h"


//Mac
//string MAC_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/Bitcoin_Data/";
//Windows path to save
string MAC_PATH ="D:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/";
//Mac
//string MAC_BITCOIN_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/";
//Windows
string MAC_BITCOIN_PATH ="D:/Users/ananda/Downloads/Bitcoin/Rich Gets Richer Data/";
//Mac
//string MAC_BLOCK_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/BitcoinBlocks/";
//Windows
string MAC_BLOCK_PATH ="D:/Users/ananda/Downloads/Bitcoin/Blocks/";
//Mac
//string BITCOINPROCESSEDPATH = "";
//Windows
string BITCOINPROCESSEDPATH = "D:/Users/ananda/Downloads/Bitcoin/BitcoinData/";


int main(){
//	numberOfAddressesOverWeeks();
//	run extractor for block explorer to create graph
//	CreateBitcoinGraph userGraph;
//	userGraph.createUserGraph();
//
//	ExtractFromBlockExplorer extractor;
//	extractor.runExtractor();
//
//	compute degree and balance
//	ComputeOverBitcoinData degBalance;
//	degBalance.compute();

	FormatFile f;
//	f.formatAddressFile();
//	f.formatTxOutFile();
	f.formatTxTimeFile();

//	IdentifyBitcoinUserEfficient userContractor;
//	userContractor.identifyBitcoinUser();


//	IdentifyBitcoinUserNew userContractor;
//	userContractor.IdentifyBTCUser();

//	ComputeTemporalBalance b;
//	b.compTemporalBalance();
}


