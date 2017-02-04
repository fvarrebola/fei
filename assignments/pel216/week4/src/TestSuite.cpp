#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/tests/TestSuiteWeek4.h>

#include <inc/lists/Node.h>
#include <inc/queue/PriorityQueue.h>
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
 * Testa as heurísticas.
 */
PRIVATE void pel216::week4::TestSuite::testEightPuzzleStateHeuristics() {

	Logger::log("Testando busca com  pel216::week3::EightPuzzleState...\n");

	Logger::log("Testando busca com  pel216::week3::EightPuzzleState#getMisplaceBlocksCount()...\n");
	EightPuzzleState s1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0)); //0
	EightPuzzleState s2(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6)); // 2
	EightPuzzleState s3(initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 2, 1, 4, 3, 6, 7, 5, 8)); // 5
	assert(s1.h(&s1) == 0);
	assert(s2.h(&s1) == 2);
	assert(s3.h(&s1) == 5);

	Logger::log("Testando busca com  pel216::week3::EightPuzzleState#getManhattanDistance()...\n");
	EightPuzzleState s4(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0)); // 0
	EightPuzzleState s5(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6)); // 2
	EightPuzzleState s6(initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 2, 1, 4, 3, 6, 7, 5, 8)); // 5

	assert(s4.h(&s4, H_MANHATTAN_DISTANCE) == 0);
	assert(s5.h(&s4, H_MANHATTAN_DISTANCE) == 2);
	assert(s6.h(&s4, H_MANHATTAN_DISTANCE) == 10);

}

/**
 * Testa a classe PriorityQueue.
 */
PRIVATE void pel216::week4::TestSuite::testPriorityQueueClass() {

	Logger::log("Testando busca com  pel216::week4::PriorityQueue...\n");

	PriorityQueue *queue = new PriorityQueue();
	EightPuzzleState s1(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0)); // 0
	EightPuzzleNode n1(&s1, &s1, 0, s1.h(&s1));

	EightPuzzleState s2(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6)); // 2
	EightPuzzleNode n2(&s2, &s2, 0, s2.h(&s1));

	EightPuzzleState s3(initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 2, 1, 4, 3, 6, 7, 5, 8)); // 5
	EightPuzzleNode n3(&s3, &s3, 0, s3.h(&s1));

	EightPuzzleState s4(initVector(EIGHT_PUZZLE_STATE_LENGTH, 3, 0, 4, 1, 8, 7, 6, 2, 5)); // 9
	EightPuzzleNode n4(&s4, &s4, 0, s4.h(&s1));

	EightPuzzleState s5(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 0, 7, 8, 6)); // 2
	EightPuzzleNode n5(&s5, &s5, 0, s5.h(&s1));

	EightPuzzleState s6(initVector(EIGHT_PUZZLE_STATE_LENGTH, 0, 2, 1, 4, 3, 6, 7, 5, 8)); // 5
	EightPuzzleNode n6(&s6, &s6, 0, s6.h(&s1));

	queue->push_desc(&n2);
	queue->push_desc(&n3);
	queue->push_desc(&n4);
	queue->push_desc(&n1);
	queue->push_desc(&n5);
	queue->push_desc(&n6);

	Logger::log("Determinando se a insercao decrescente foi bem sucedida...\n");
	assert(queue->front()->getData()->getHeuristic() == 9);
	assert(queue->back()->getData()->getHeuristic() == 0);

	assert(queue->pop()->getHeuristic() == 9);
	assert(queue->pop()->getHeuristic() == 5);
	assert(queue->pop()->getHeuristic() == 5);
	assert(queue->pop()->getHeuristic() == 2);
	assert(queue->pop()->getHeuristic() == 2);
	assert(queue->pop()->getHeuristic() == 0);

	queue->push_asc(&n2);
	queue->push_asc(&n3);
	queue->push_asc(&n4);
	queue->push_asc(&n1);
	queue->push_asc(&n5);
	queue->push_asc(&n6);

	Logger::log("Determinando se a insercao crescente foi bem sucedida...\n");
	assert(queue->front()->getData()->getHeuristic() == 0);
	assert(queue->back()->getData()->getHeuristic() == 9);

	assert(queue->pop()->getHeuristic() == 0);
	assert(queue->pop()->getHeuristic() == 2);
	assert(queue->pop()->getHeuristic() == 2);
	assert(queue->pop()->getHeuristic() == 5);
	assert(queue->pop()->getHeuristic() == 5);
	assert(queue->pop()->getHeuristic() == 9);

}

/**
 * Testa a classe EightPuzzleBestFirstSearchEngine.
 */
PRIVATE void pel216::week4::TestSuite::testEightPuzzleBestFirstSearchEngineClass() {

	Logger::log("Testando busca com  pel216::week4::EightPuzzleBestFirstSearchEngine...\n");

	EightPuzzleState s(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 3, 5, 7, 2, 4, 6, 8, 0));
	EightPuzzleState g(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));

	EightPuzzleBestFirstSearchEngine e = EightPuzzleBestFirstSearchEngine(-1, false);
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("%s\n", ex->what());
	}

	assert(e.getSolutionDepth() == 34);

}

/**
 * Testa a classe EightPuzzleHillClimbingSearchEngine.
 */
PRIVATE void pel216::week4::TestSuite::testEightPuzzleHillClimbingSearchEngineClass() {

	Logger::log("Testando busca com  pel216::week4::EightPuzzleHillClimbingSearchEngine...\n");

	EightPuzzleState s(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 3, 5, 7, 2, 4, 6, 8, 0));
	EightPuzzleState g(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));

	EightPuzzleHillClimbingSearchEngine e = EightPuzzleHillClimbingSearchEngine(-1, false);
	EightPuzzleSolver solver(&e, &s, &g);
	
	bool hasException = false;
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		assert(ex->what() != NULL);
		hasException = true;
	}

	assert(hasException);

}

/**
 * Testa a classe EightPuzzleAStarSearchEngine.
 */
PRIVATE void pel216::week4::TestSuite::testEightPuzzleAStarSearchEngineClass() {

	Logger::log("Testando busca com  pel216::week4::EightPuzzleAStarSearchEngine...\n");

	EightPuzzleState s(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 3, 5, 7, 2, 4, 6, 8, 0));
	EightPuzzleState g(initVector(EIGHT_PUZZLE_STATE_LENGTH, 1, 2, 3, 4, 5, 6, 7, 8, 0));

	EightPuzzleAStarSearchEngine e = EightPuzzleAStarSearchEngine(-1, false);
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		assert(ex->what() != NULL);
	}

	assert(e.getSolutionDepth() == 18);

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week4::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week4::TestSuite::testPriorityQueueClass();
	pel216::week4::TestSuite::testEightPuzzleBestFirstSearchEngineClass();
	pel216::week4::TestSuite::testEightPuzzleHillClimbingSearchEngineClass();
	pel216::week4::TestSuite::testEightPuzzleAStarSearchEngineClass();
	
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
