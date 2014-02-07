#ifndef EXTRACTFROMBLOCKEXPLORER_H_
#define EXTRACTFROMBLOCKEXPLORER_H_

#include "CommonHeaders.h"
#include "FormatFile.h"

class ExtractFromBlockExplorer{
private:
	FormatFile format;
public:
	ExtractFromBlockExplorer(){

	}
	~ExtractFromBlockExplorer(){

	}
	void runExtractor();
	bool checkAllBlockFileExists(int from, int to);
};

#endif
