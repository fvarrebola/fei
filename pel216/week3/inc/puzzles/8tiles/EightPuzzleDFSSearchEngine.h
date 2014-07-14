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
			 * Adiciona um n� ao mapa de n�s conhecidos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 */
			void addKnownNode(EightPuzzleNode *node) {
				knownNodes->insert(std::pair<std::string,EightPuzzleNode*>(node->getState()->hashCode(), node));
			};

			/**
			 * Determina se um n� j� � conhecido.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 *
			 * @return <code>true</code> caso o n� seja conhecido; do contr�rio <code>false</code>
			 */
			bool isKnownNode(EightPuzzleNode *node) {
				return (knownNodes->find(node->getState()->hashCode()) != knownNodes->end());
			};

			/**
			 * Adiciona um estado � lista de movimentos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 */
			void addPath(EightPuzzleNode *node) {
				solutionPath->insert(solutionPath->begin(), node);
			};

			/**
			 * @see pel216::week3::SearchEngine::expandNode()
			 */
			void expandNode(EightPuzzleNode *node) {

				EightPuzzleState *state = node->getState();

				state->expand();
				this->expandedNodesCount++;

				// avalia cada um dos novos estados
				std::vector<std::vector<int> > expandedDataVector = state->getExpandedData();
				size_t len = expandedDataVector.size();
				for (size_t idx = 0; idx < len; idx++) {

					// um estado � criado a partir da expans�o
					EightPuzzleState *successorState = 
						new EightPuzzleState(expandedDataVector[idx]);

					// um n� � criado
					EightPuzzleNode *successorNode = 
						new EightPuzzleNode(successorState, state, node->getDepth() + 1);

					// se o n�s j� foi visitado deve ser descartado
					bool discard = isKnownNode(successorNode);

					if (this->debug) {
						Logger::log(">> #%d: %s (%s)\n", (idx + 1),  successorState->toString().c_str(), (discard ? "D" : "M"));
					}

					if (discard) {
						continue;
					}

					addKnownNode(successorNode);
					this->list->push_back(successorNode);

				}

			};

		public:
			/**
			 * Construtor padr�o.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade m�xima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			EightPuzzleDFSSearchEngine(size_t maxDepth = -1, bool debug = false) : SearchEngine() {
				setup(maxDepth, debug);
			};

			/**
			 * @see pel216::week3::SearchEngine::search()
			 */
			virtual void search() {

				this->solutionDepth = 0;
				this->expandedNodesCount = 0;
				
				Logger::log("*****************************************\n");
				Logger::log("*                                       *\n");
				Logger::log("* DFS                                   *\n");
				Logger::log("*                                       *\n");
				Logger::log("*****************************************\n"); 

				EightPuzzleNode *startingNode = getStartingNode();
				EightPuzzleState *initialState = startingNode->getState();
				EightPuzzleNode *goalNode = getGoalNode();
				EightPuzzleState *goalState = goalNode->getState();

				Logger::log("> Inicio:    %s\n", initialState->toString().c_str());
				Logger::log("> Objetivo:  %s\n", goalState->toString().c_str());
				Logger::log("> Prof. max: %d\n", this->maxDepth);
				Logger::log("> Debug:     %s\n", (this->debug? "S" : "N"));

				list->push_back(startingNode);
				addKnownNode(startingNode);

				size_t iteractions = 1;
				while (list->size() != 0) { /* enquanto houver estados a serem analisados */

					if (this->debug) {
						dumpList();
					}

					// remove o elemento 
					EightPuzzleNode *node = list->back();
					EightPuzzleState *state = node->getState();
					list->pop_back();

					if (this->debug) {
						Logger::log("\n");
						Logger::log("#%04d Visitando no %s...\n", iteractions++, state->toString().c_str());
					}

					// verifica se o alvo foi atingido
					if (state->equals(goalState)) { 

						this->solutionDepth = node->getDepth();

						Logger::log("\n");
						Logger::log("!!! SOLUCAO ENCONTRADA !!! (em profundidade %d apos expandir %d nos)\n", 
							this->solutionDepth, this->expandedNodesCount);
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
					if (node->getDepth() == this->maxDepth) {
						if (this->debug) {
							Logger::log("  >> No descartado (profundidade maxima atingida)\n");
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