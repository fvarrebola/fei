#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/tests/TestSuiteWeek3.h>

#include <inc/lists/Node.h>
#include <inc/lists/LinkedList.h>
#include <inc/puzzles/State.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleSolver.h>
#include <inc/puzzles/8tiles/EightPuzzleBFSSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleDFSSearchEngine.h>

#include <inc/search/SearchEngine.h>
#include <inc/search/SolutionNotFoundException.h>

#include <inc/ex/IllegalParameterException.h>

using namespace pel216::commons;
using namespace pel216::week3;


PRIVATE void pel216::week3::TestSuite::testLinkedList() {

	LinkedList<EightPuzzleNode> *list = new LinkedList<EightPuzzleNode>();

	EightPuzzleState s0(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));
	EightPuzzleState s1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 2, 3, 4, 5, 0, 7, 8, 1));
	EightPuzzleState s2(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 0, 3, 4, 5, 6, 7, 8, 2));
	EightPuzzleState s3(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 0, 4, 5, 6, 7, 8, 3));
	EightPuzzleState s4(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 0, 5, 6, 7, 8, 4));
	EightPuzzleState s5(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 0, 6, 7, 8, 5));

	list->push_back(new EightPuzzleNode(&s0));
	list->push_back(new EightPuzzleNode(&s1));
	list->push_back(new EightPuzzleNode(&s2));

	list->push_front(new EightPuzzleNode(&s3));
	list->push_front(new EightPuzzleNode(&s4));
	list->push_front(new EightPuzzleNode(&s5));
	assert(!list->isEmpty() && (list->size() == 6));

	EightPuzzleNode *b = list->pop_back();
	assert(pel216::commons::Utils::isValidHandle(b));
	assert(list->size() == 5);
	assert(b->getState()->getData()[8] == 2);

	EightPuzzleNode *f = list->pop_front();
	assert(pel216::commons::Utils::isValidHandle(f));
	assert(list->size() == 4);
	assert(f->getState()->getData()[8] == 5);

	b = list->pop_back();
	assert(pel216::commons::Utils::isValidHandle(b));
	assert(list->size() == 3);
	assert(b->getState()->getData()[8] == 1);

	b = list->pop_back();
	assert(pel216::commons::Utils::isValidHandle(b));
	assert(list->size() == 2);
	assert(b->getState()->getData()[8] == 0);

	f = list->pop_front();
	assert(pel216::commons::Utils::isValidHandle(f));
	assert(list->size() == 1);
	assert(f->getState()->getData()[8] == 4);

	f = list->pop_front();
	assert(pel216::commons::Utils::isValidHandle(f));
	assert(list->isEmpty() && (list->size() == 0));
	assert(f->getState()->getData()[8] == 3);

	f = list->pop_front();
	assert(pel216::commons::Utils::isInvalidHandle(f));
}


PRIVATE void pel216::week3::TestSuite::test8PuzzleStateClass() {

	Logger::log("Testando classe pel216::week3::EightPuzzleState...\n");

	std::vector<int> v0(pel216::week3::EIGHT_PUZZLE_STATE_LENGTH);
	EightPuzzleState *valid = new EightPuzzleState(v0);
	delete valid;

	bool hasException_1 = false;
	try {
		std::vector<int> v1(pel216::week3::EIGHT_PUZZLE_STATE_LENGTH - 1);
		new EightPuzzleState(v1);
	} catch (pel216::commons::IllegalParameterException *ex) {
		assert(pel216::commons::Utils::isValidHandle(ex));
		hasException_1 = true;
	}
	assert(hasException_1);

	bool hasException_2 = false;
	try {
		std::vector<int> v2(pel216::week3::EIGHT_PUZZLE_STATE_LENGTH + 1);
		new EightPuzzleState(v2);
	} catch (pel216::commons::IllegalParameterException *ex) {
		assert(pel216::commons::Utils::isValidHandle(ex));
		hasException_2 = true;
	}
	assert(hasException_2);

}

PRIVATE void pel216::week3::TestSuite::test8PuzzleSearchEngine(
	EightPuzzleState *s,
	EightPuzzleState *g,
	SearchEngine<EightPuzzleNode> *e,
	bool hasSolution = true,
	size_t expandedNodesExpectation = -1,
	size_t solutionDepthExpectation = -1) {

	Logger::log("\n");
	Logger::log("Testando busca com  pel216::week3::EightPuzzleDFSSearchEngine...\n");
	EightPuzzleSolver solver(e, s, g);

	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		assert(pel216::commons::Utils::isValidHandle(ex));
	}

	if (hasSolution) {

		Logger::log("Determinando se a solucao foi encontrada...\n");
		assert(e->hasFoundSolution());

		std::vector<EightPuzzleNode*> *nodePath = e->getSolutionPath();
		size_t solutionPathLen = nodePath->size();

		Logger::log("Imprimindo movimentos...\n");
		for (size_t idx = 0; idx < solutionPathLen; idx++) {
			Logger::log("> Movimento #%d {%s}\n", (idx + 1), nodePath->at(idx)->getState()->toString().c_str());
		}

	}

	if (expandedNodesExpectation > -1) {
		Logger::log("Determinando se a quantidade de nos expandidos eh %d...\n", e->getExpandedNodesCount());
		assert(e->getExpandedNodesCount() == expandedNodesExpectation);
	}

	if (solutionDepthExpectation > -1) {
		Logger::log("Determinando se a quantidade movimentos ate a solucao eh %d...\n", e->getSolutionDepth());
		assert(e->getSolutionDepth() == solutionDepthExpectation);
	}

}


PRIVATE void pel216::week3::TestSuite::test8PuzzleSolverClass() {

	Logger::log("Testando classe pel216::week3::EightPuzzleSolver...\n");
	
	// teste #1
	EightPuzzleBFSSearchEngine bfs1(-1);
	EightPuzzleDFSSearchEngine dfs1(-1);
	EightPuzzleState g1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&g1, &g1, &bfs1);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&g1, &g1, &dfs1);

	// teste #2
	EightPuzzleBFSSearchEngine bfs2(-1);
	EightPuzzleDFSSearchEngine dfs2(-1);
	EightPuzzleState s1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s1, &g1, &bfs2);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s1, &g1, &dfs2);

	// teste #3
	EightPuzzleBFSSearchEngine bfs3(5);
	EightPuzzleDFSSearchEngine dfs3(5);
	EightPuzzleState s2(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 0, 6, 7, 5, 8));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s2, &g1, &bfs3);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s2, &g1, &dfs3);

	// teste #4
	EightPuzzleBFSSearchEngine bfs4(10);
	EightPuzzleDFSSearchEngine dfs4(10);
	EightPuzzleState s3(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 0, 3, 4, 8, 6, 7, 5, 2));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s3, &g1, &dfs4, false);

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week3::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week3::TestSuite::testLinkedList();
	pel216::week3::TestSuite::test8PuzzleStateClass();
	pel216::week3::TestSuite::test8PuzzleSolverClass();

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
