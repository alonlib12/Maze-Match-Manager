#include "FileUtilities.h"
#include "GameManager.h"
#include "MatchManager.h"
#include "InputMazeParser.h"
#include "AbstractAlgorithm.h"
#include "AlgorithmRegistrar.h"
#include "AlgorithmRegistration.h"
#include "ArgumentParser.h"
#include "ArgumentParser.h"
#include "MazeOutput.h"




using namespace std;

static const int SUCCESS = 0;
static const int FAILURE = 1;

int main(int argc, const char* argv[]) {

	ArgumentParser argParser(argc,argv);
	if (!argParser.isValid())
		return FAILURE;
	AlgorithmRegistrar& registrar = AlgorithmRegistrar::getInstance();
	registrar.loadAlgorithms(argParser.getAlgorithmPath() ,argParser.getAlgorithmFileNames() );
	auto algorithmFactories = registrar.getAlgorithmFactories();
	list<string> algorithmNames = registrar.getAlgorithmNames();
	MatchManager match(algorithmFactories, algorithmNames, argParser.getMazeFileNames(), argParser.getMazePath(), argParser.getOutputPath(),argParser.getNumOfThreads());
	match.play();
	return SUCCESS;
}
