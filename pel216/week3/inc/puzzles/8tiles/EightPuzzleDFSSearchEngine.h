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
			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				// avalia cada um dos novos estados
				std::vector<EightPuzzleState*> children = state->getChildren();
				size_t len = children.size();
				for (size_t idx = 0; idx < len; idx++) {

					EightPuzzleState *child = children.at(idx);
					EightPuzzleNode *childNode = new EightPuzzleNode(child, state, node->getDepth() + 1);

					// se o nó já foi visitado deve ser descartado
					bool discard = isKnownNode(childNode);

					if (this->debug) {
						Logger::logToFile(">> #%d: %s (%s)\n", (idx + 1),  child->toString().c_str(), (discard ? "D" : "M"));
					}

					if (discard) {
						continue;
					}
					
					addKnownNode(childNode);
					this->list->push_back(childNode);

				}

			};

		public:
			/**
			 * Construtor padrão.
			 *
			 * @param maxAllowedDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleDFSSearchEngine(size_t maxAllowedDepth = -1, bool debug = false) : SearchEngine("Depth First Search") {
				setup(maxAllowedDepth, debug);
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
				addKnownNode(startingNode);

				size_t iteractions = 0;
				size_t maxDepth = 0;
				while (list->size() != 0) { 

					iteractions++;

					if (this->debug) {
						log();
					}

					EightPuzzleNode *node = list->pop_back();
					EightPuzzleState *state = node->getState();

					if (this->debug) {
						Logger::logToFile("#%06d Visitando no %s...\n", iteractions, (state)->toString().c_str());
					}

					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log(
								"!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
								this->solutionDepth, 
								this->expandedNodesCount);
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
