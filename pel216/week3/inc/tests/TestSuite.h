#pragma once

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <assert.h>

#include <inc/search/SearchEngine.h>

#include <inc/puzzles/State.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testNodeClassUsingIntType();
			static void testNodeClassUsingIntArray();
			static void testNodeClassUsingStateClassAsData();

			static void testLinkedList();

			/**
			 * Testa a classe @link{EightPuzzleState}.
			 */
			static void test8PuzzleStateClass();

			/**
			 * Testa um mecanismo de busca no jogo de 8 peças.
			 *
			 * @param s
			 *			o @link{EightPuzzleState} que representa o estado inicial
			 * @param g
			 *			o @link{EightPuzzleState} que representa o estado alvo
			 * @param hasSolution
			 *			indica se há solução
			 * @param expandedNodesExpectation
			 *			o <code>size_t</code> que representa a quantidade esperada de nós expandidos para a solução
			 * @param solutionDepthExpectation
			 *			o <code>size_t</code> que representa a quantidade esperada de profundidade para a solução
			 */
			static void test8PuzzleSearchEngine(
					EightPuzzleState *s, 
					EightPuzzleState *g,
					SearchEngine<EightPuzzleNode> *e,
					bool hasSolution,
					size_t expandedNodesExpectation, 
					size_t solutionDepthExpectation);

			/**
			 * Testa a classe @link{EightPuzzleSolver} com os mecanismos de busca BFS e DFS.
			 */
			static void test8PuzzleSolverClass();

		public:
			/**
			 * Executa todos os testes.
			 */
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __TESTSUITE_H__ */
