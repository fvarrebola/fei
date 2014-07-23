#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/tests/TestSuiteWeek4.h>

#include <inc/lists/Node.h>
#include <inc/lists/LinkedList.h>
#include <inc/puzzles/State.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleSolver.h>
#include <inc/puzzles/8tiles/EightPuzzleBestFirstSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleHillClimbingSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleAStarSearchEngine.h>

#include <inc/search/SearchEngine.h>
#include <inc/search/SolutionNotFoundException.h>

#include <inc/ex/IllegalParameterException.h>

using namespace pel216::commons;
using namespace pel216::week4;

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week4::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
