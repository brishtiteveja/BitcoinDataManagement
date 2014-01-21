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
#include "IdentifyBitcoinUserNew.h"
#include "FormatFile.h"
#include "CommonHeaders.h"


//Mac
//string PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/Bitcoin_Data/";
//Windows path to save
string MAC_PATH ="D:/Users/ananda/Downloads/Bitcoin/BitcoinDataNewNew/";
//Mac
//string BITCOIN_PATH ="/Users/zehadyzbdullahkhan/Documents/workspace/Research/Thesis/Bitcoin/";
//Windows
string MAC_BITCOIN_PATH ="D:/Users/ananda/Downloads/Bitcoin/Rich Gets Richer Data/";

string BITCOINPROCESSEDPATH="D:/Users/ananda/Downloads/Bitcoin/BitcoinDataNewNew/";
//Mac
//string BLOCK_PATH ="/Users/zehadyzbdullahkhan/git/BitcoinDataManagement/BitcoinDataManagement/blocks/";
//Windows
string MAC_BLOCK_PATH ="D:/Users/ananda/Downloads/Bitcoin/Blocks/";
//Mac
//string PATH ="C:/Users/ananda/Downloads/Bitcoin/BitcoinDataNew/";
//Windows
//string PATH ="";

int main(){
	//numberOfAddressesOverWeeks();

	//FormatFile f;
	//f.formatAddressFile();
	//f.formatTxOutFile();

	//run extractor for block explorer to create graph
	//ExtractFromBlockExplorer extractor;
	//extractor.runExtractor();

//	ComputeOverBitcoinData degBalance;
//	degBalance.compute();

	IdentifyBitcoinUserNew userContractor;
	userContractor.IdentifyBTCUser();

	//CreateBitcoinGraph usergraph;
	//usergraph.createGraph();

}


