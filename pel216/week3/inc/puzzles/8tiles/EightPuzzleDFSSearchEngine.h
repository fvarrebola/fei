#pragma once

#ifndef __8PUZZLE_DFS_H__
#define __8PUZZLE_DFS_H__

#include <list>

#include <vector>
#include <map>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/search/SearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleNode.h>

using namespace pel216::commons;

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa a busca em profundidade (<i>depth-first-search</i>).
		 *
		 * @author arrebola
		 */
		class EightPuzzleDFSSearchEngine : public SearchEngine<EightPuzzleNode> {

		private:
			// a estrutura de dados utilizada pelo mecanismo
			LinkedList<EightPuzzleNode> *list; 		
			
		protected:
			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				std::vector<EightPuzzleState*> children = state->getChildren();
				size_t len = children.size();
				for (size_t idx = 0; idx < len; idx++) {
					EightPuzzleState *child = children.at(idx);
					EightPuzzleNode *childNode = new EightPuzzleNode(child, state, node->getDepth() + 1);
					this->list->push_back(childNode);
				}

			};

		public:
			/**
			 * Construtor.
			 *
			 * @param maxAllowedDepth
			 *				o <code>size_t</code> que representa a profundidade m�xima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleDFSSearchEngine(size_t maxAllowedDepth = -1, bool debug = false) : SearchEngine("Depth First Search") {
				setup(maxAllowedDepth, debug);
				this->list = new LinkedList<EightPuzzleNode>();
			};

			/**
			 * Destrutor.
			 */
			~EightPuzzleDFSSearchEngine() {
				delete this->list;
			};

			/**
			 * @see pel216::week3::SearchEngine::doSearch()
			 */
			virtual void doSearch() {

				this->solutionDepth = 0;
				this->expandedNodesCount = 0;
				
				EightPuzzleNode *startingNode = getStartingNode();
				EightPuzzleState *initialState = startingNode->getState();
				EightPuzzleNode *goalNode = getGoalNode();
				EightPuzzleState *goalState = goalNode->getState();

				list->push_back(startingNode);

				size_t iteractions = 0;
				size_t maxDepth = 0;
				while (list->size() != 0) { 

					iteractions++;

					if (this->debug) {
						this->list->dumpToFile();
					}

					EightPuzzleNode *node = list->pop_back();
					EightPuzzleState *state = node->getState();

					bool discard = isKnownNode(node);

					if (this->debug) {
						Logger::logToFile("\n");
						Logger::logToFile("#%06d %s no %s...\n", 
							iteractions, (discard ? "Descartando" : "Visitando"), (state)->toString().c_str());
					}

					if (discard) {
						continue;
					}

					addKnownNode(node);

					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log(
								"!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
								this->solutionDepth, 
								this->expandedNodesCount);
						Logger::log("\n");

						do { /* constr�i o caminho da solu��o */
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

					// descarta o n� com profundidade m�xima
					if (node->getDepth() == this->maxAllowedDepth) {
						if (this->debug) {
							Logger::logToFile("  >> No descartado (profundidade maxima atingida)\n");
						}
						continue;
					}

					expandNode(node);

				}

			};

		}; /* class EightPuzzleDFSSearchEngine */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __8PUZZLE_DFS_H__ */
