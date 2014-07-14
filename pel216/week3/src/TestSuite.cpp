#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/tests/TestSuite.h>

#include <inc/lists/Node.h>
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

PRIVATE void pel216::week3::TestSuite::testNodeClassUsingIntType() {

	Logger::log("Testando classe pel216::week3::Node (com T = int)...\n");

	Logger::log("Testando classe pel216::week3::Node::[get|set][Data|Previous|Next]...\n");

	Node<int> *previous = new Node<int>(-1);
	Node<int> *node = new Node<int>(1);
	Node<int> *next = new Node<int>(2);

	assert(node->getData() == 1);
	assert(node->getPrevious() == NULL);
	assert(node->getNext() == NULL);

	assert(previous->getData() == -1);
	assert(next->getData() == 2);

	node->setPrevious(previous);
	node->setNext(next);
	assert(node->getPrevious() == previous);
	assert(node->getNext() == next);

	delete node;
	delete next;
	delete previous;


}



PRIVATE void pel216::week3::TestSuite::testNodeClassUsingIntArray() {

	Logger::log("Testando classe pel216::week3::Node (com T = int[])...\n");

	Logger::log("Testando classe pel216::week3::Node::[get|set][Data|Previous|Next]...\n");

	int v0[] = {2, 3, 5, 7, 11, 13};
	int v1[] = {23, 27, 29, 31, 37};
	int v2[] = {2, 4, 8, 16, 32};

	Node<int*> *previous = new Node<int*>(v0);
	Node<int*> *next = new Node<int*>(v1);
	Node<int*> *node = new Node<int*>(v2, previous, next);
	assert(node->getData() == v2);
	assert(node->getPrevious() == previous);
	assert(node->getNext() == next);
	assert(previous->getData() == v0);
	assert(next->getData() == v1);
	node->setPrevious(next);
	node->setNext(previous);
	assert(node->getPrevious() == next);
	assert(node->getNext() == previous);
	delete node;
	delete next;
	delete previous;

}



PRIVATE void pel216::week3::TestSuite::testNodeClassUsingStateClassAsData() {

	Logger::log("Testando classe pel216::week3::Node (com T = State)...\n");

	Logger::log("Testando classe pel216::week3::Node::[get|set][Data|Previous|Next]...\n");


	//int v0[] = {2, 3, 5, 7, 11, 13};
	//int v1[] = {23, 27, 29, 31, 37};
	//int v2[] = {2, 4, 8, 16, 32};

//	Node< State<int*> > *previous = new Node< State<int*> >(v0);
//	Node< State<int*> > *next = new Node< State<int*> >(v1);
//	Node< State<int*> > *node = new Node< State<int*> >(v2, previous, next);
//	State<int *> state = node->getData();
//	int *stateData = state.getData();
//	assert(stateData != NULL);
//	assert(node->getPrevious() == previous);
//	assert(node->getNext() == next);
//
//	delete node;
//	delete next;
//	delete previous;

}



PRIVATE void pel216::week3::TestSuite::testStateClass() {

	Logger::log("Testando classe pel216::week3::State...\n");

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
	solver.solve();

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

	EightPuzzleBFSSearchEngine bfs1(5);
	EightPuzzleDFSSearchEngine dfs1(5, true);

	// teste #1
	EightPuzzleState g1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&g1, &g1, &bfs1);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&g1, &g1, &dfs1);

	// teste #2
	EightPuzzleState s1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s1, &g1, &bfs1);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s1, &g1, &dfs1);

	// teste #3
	EightPuzzleState s2(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 0, 6, 7, 5, 8));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s2, &g1, &bfs1);
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s2, &g1, &dfs1);

	// teste #3
	EightPuzzleState s3(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 0, 3, 4, 8, 6, 7, 5, 2));
	pel216::week3::TestSuite::test8PuzzleSearchEngine(&s3, &g1, &dfs1, false);

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

	pel216::week3::TestSuite::testNodeClassUsingIntType();
	pel216::week3::TestSuite::testNodeClassUsingIntArray();
	pel216::week3::TestSuite::testNodeClassUsingStateClassAsData();
	pel216::week3::TestSuite::test8PuzzleStateClass();
	pel216::week3::TestSuite::test8PuzzleSolverClass();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
