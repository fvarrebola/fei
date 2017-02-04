#pragma once

#ifndef __TESTSUITE_WEEK4_H__
#define __TESTSUITE_WEEK4_H__

#include <assert.h>

#include <inc/search/SearchEngine.h>

#include <inc/puzzles/State.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

namespace pel216 {

	namespace week4 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testEightPuzzleStateHeuristics();
			static void testPriorityQueueClass();
			static void testEightPuzzleBestFirstSearchEngineClass();
			static void testEightPuzzleHillClimbingSearchEngineClass();
			static void testEightPuzzleAStarSearchEngineClass();

		public:
			/**
			 * Executa todos os testes.
			 */
			static void run(); 

		}; /* class TestSuiteWeek4 */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK4_H__ */
