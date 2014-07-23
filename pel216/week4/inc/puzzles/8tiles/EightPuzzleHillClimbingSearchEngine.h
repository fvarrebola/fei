#pragma once

#ifndef __8PUZZLE_HILL_CLIMBING_H__
#define __8PUZZLE_HILL_CLIMBING_H__

#include <list>

#include <vector>
#include <map>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/search/SearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

using namespace pel216::commons;
using namespace pel216::week3;

namespace pel216 {

	namespace week4 {

		/**
		 * Classe que representa a busca <i>hill climbing</i>.
		 *
		 * @author arrebola
		 */
		class EightPuzzleHillClimbingSearchEngine : public SearchEngine<EightPuzzleNode> {

		private:
			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				// avalia cada um dos novos estados
			};

		public:
			/**
			 * Construtor padrão.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleHillClimbingSearchEngine(size_t maxDepth = -1, bool debug = false) : SearchEngine("Hill Climbing") {
				setup(maxDepth, debug);
			};

			/**
			 * @see pel216::week3::SearchEngine::search()
			 */
			virtual void search() {

				this->solutionDepth = 0;
				this->expandedNodesCount = 0;
				
				EightPuzzleNode *startingNode = getStartingNode();
				EightPuzzleState *initialState = startingNode->getState();
				EightPuzzleNode *goalNode = getGoalNode();
				EightPuzzleState *goalState = goalNode->getState();

				list->push_back(startingNode);
				addKnownNode(startingNode);

				size_t iteractions = 1;
				while (list->size() != 0) { /* enquanto houver estados a serem analisados */

					EightPuzzleNode *node = list->pop_back();
					EightPuzzleState *state = node->getState();

					if (this->debug) {
						log();
						Logger::logToFile("\n");
						Logger::logToFile("#%06d Visitando no %s...\n", iteractions, (state)->toString().c_str());
					}

					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log("!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
							this->solutionDepth, this->expandedNodesCount);
						Logger::log("\n");

						do { /* constrói o caminho da solução */
							addPath(node);
							EightPuzzleState *parentState = node->getParent();
							if (Utils::isInvalidHandle(parentState)) {
								break;
							}
							node = knownNodes->at(parentState->hashCode());
						} while(!initialState->equals(node->getState()));
						
						hasSolution = true;
						break;

					}

					// descarta o nó com profundidade máxima
					if (node->getDepth() == this->maxAllowedDepth) {
						if (this->debug) {
							Logger::log("  >> No descartado (profundidade maxima atingida)\n");
						}
						continue;
					}

					expandNode(node);

				}

			};

		}; /* class EightPuzzleHillClimbingSearchEngine */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __8PUZZLE_HILL_CLIMBING_H__ */
