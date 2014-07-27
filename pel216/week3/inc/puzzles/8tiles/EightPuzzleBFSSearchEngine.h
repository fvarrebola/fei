#pragma once

#ifndef __8PUZZLE_BFS_H__
#define __8PUZZLE_BFS_H__

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
		 * Classe que representa a busca em largura (<i>breadth-first-search</i>).
		 *
		 * @author arrebola
		 */
		class EightPuzzleBFSSearchEngine : public SearchEngine<EightPuzzleNode> {

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

				// avalia cada um dos novos estados
				std::vector<EightPuzzleState*> children = state->getChildren();
				size_t len = children.size();
				for (size_t idx = 0; idx < len; idx++) {

					EightPuzzleState *child = children.at(idx);
					EightPuzzleNode *childNode = new EightPuzzleNode(child, state, node->getDepth() + 1);

					// determina se o estado já foi visitado
					bool discard = isKnownNode(childNode);

					if (this->debug) {
						Logger::logToFile("> Estado #%d: %s (%s)\n", (idx + 1),  child->toString().c_str(), (discard ? "D" : "M"));
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
			 * Construtor.
			 *
			 * @param maxAllowedDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleBFSSearchEngine(size_t maxAllowedDepth = -1, bool debug = false) : SearchEngine("Breadth First Search") {
				setup(maxAllowedDepth,  debug);
				this->list = new LinkedList<EightPuzzleNode>();
			};

			/**
			 * Destrutor.
			 */
			~EightPuzzleBFSSearchEngine() {
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

				// inicia a lista com o primeiro nó
				list->push_back(startingNode);
				addKnownNode(startingNode);

				size_t iteractions = 0;
				while (list->size() != 0) { /* enquanto houver estados a serem analisados */

					iteractions++;
					
					if (this->debug) {
						this->list->dumpToFile();
					}

					EightPuzzleNode *node = list->pop_front();
					EightPuzzleState *state = node->getState();
					
					if (this->debug) {
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

					// determina a profundidade máxima foi atingida
					if (node->getDepth() == this->maxAllowedDepth) {
						Logger::logToFile("A profundidade %d foi atingida e nenhuma solucao foi encontrada\n", this->maxAllowedDepth); 
						break;
					}

					expandNode(node);

				}

			};

		}; /* class EightPuzzleBFSSearchEngine */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __8PUZZLE_BFS_H__ */
