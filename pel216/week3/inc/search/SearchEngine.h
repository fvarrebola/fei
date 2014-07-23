#pragma once

#ifndef __SEARCHENGINE_H__
#define __SEARCHENGINE_H__

#include <string>
#include <list>
#include <vector>
#include <map>

#include <inc/Utils.h>

#include <inc/lists/LinkedList.h>
#include <inc/puzzles/State.h>
#include <inc/search/SolutionNotFoundException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um mecanismo de busca.<br />
		 * O <i>template</i> deve definir uma classe que represente um n�.
		 *
		 * @author arrebola
		 */
		template <class T>
		class SearchEngine {
		private:
			std::string name;

			/**
			 * Imprime o cabe�alho do mecanismo de buscas.
			 */
			void printHeader() {

				Logger::log("*****************************************\n");
				Logger::log("*                                       *\n");
				Logger::log("* %s\n", this->name.c_str());
				Logger::log("*                                       *\n");
				Logger::log("*****************************************\n"); 

				Logger::log("> Inicio:    %s\n", getStartingNode()->getState()->toString().c_str());
				Logger::log("> Objetivo:  %s\n", getGoalNode()->getState()->toString().c_str());
				Logger::log("> Prof. max: %d\n", this->maxAllowedDepth);
				Logger::log("> Debug:     %s\n", (this->debug? "S" : "N"));

			};

		protected:
			LinkedList<T> *list; 				/* a estrutura de dados utilizada pelo mecanismo */

			T *startingNode;					/* o n� de partida */
			T *goalNode;						/* o n� alvo */

			// os n�s conhecidos
			std::map<std::string,T*> *knownNodes;
			
			bool hasSolution;					/* se h� solu��o */
			size_t maxAllowedDepth;				/* a profundidade m�xima permitida */
			size_t maxKnownDepth;				/* a maior profundidade atingida */
			std::vector<T*> *solutionPath;		/* o caminho at� a solu��o */
			size_t solutionDepth;				/* a profundidade at� a solu��o */
			
			size_t expandedNodesCount;			/* a quantidade de n�s expandidos */

			bool debug;							/* indica se as mensagens de rastreio da execu��o devem ser exibidas */

			/**
			 * Registra o conte�do da estrutura de dados utilizada pelo mecanismo de busca.
			 */
			void log() {

				if (pel216::commons::Utils::isInvalidHandle(this->list)) {
					return;
				}

				Logger::logToFile("----------------------------------------\n"); 
				Logger::logToFile("Imprimindo estrutura de dados \n"); 
				Logger::logToFile("----------------------------------------\n"); 
				
				size_t idx = 0;
				Node<T> *node = this->list->front(); 
				while (pel216::commons::Utils::isValidHandle(node)) {
					T *data = node->getData();
					if (pel216::commons::Utils::isValidHandle(data)) {
						Logger::logToFile("\t#%d %s\n", idx++, (data)->toString().c_str());
					}
					node = node->getNext();
				}
				Logger::logToFile("----------------------------------------\n");
				
			};

			/**
			 * Configura o mecanismo de busca.
			 *
			 * @param maxAllowedDepth
			 *				o <code>size_t</code> que representa a profundidade m�xima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			virtual void setup(size_t maxAllowedDepth, bool debug) {
				this->maxAllowedDepth = maxAllowedDepth;
				this->debug = debug;
			};

			/**
			 * Adiciona um n� ao mapa de n�s conhecidos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 */
			void addKnownNode(T *node) {
				knownNodes->insert(std::pair<std::string,T*>((node)->getState()->hashCode(), node));
			};

			/**
			 * Determina se um n� j� � conhecido.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 *
			 * @return <code>true</code> caso o n� seja conhecido; do contr�rio <code>false</code>
			 */
			bool isKnownNode(T *node) {
				return (knownNodes->find((node)->getState()->hashCode()) != knownNodes->end());
			};

			/**
			 * Adiciona um estado � lista de movimentos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o n�
			 */
			void addPath(T *node) {
				solutionPath->insert(solutionPath->begin(), node);
			};


			/**
			 * Expande um n�.
			 *
			 * @param node
			 *				o <T> que representa o n�
			 */
			virtual void expandNode(T *node) {
			};
		
			/**
			 * Realiza a busca.
			 */
			virtual void doSearch() {
			};

		public:
			/**
			 * Construtor.
			 *
			 * @param name
			 *				o <code>std::string</code> que representa o algoritmo utilizado
			 */
			SearchEngine(std::string name) {
				this->name = name;
				this->list = new LinkedList<T>();
				this->solutionPath = new std::vector<T*>();
				this->knownNodes = new std::map<std::string,T*>();
				this->hasSolution = false;
			};

			/**
			 * Destrutor.
			 */
			virtual ~SearchEngine() {
				delete this->list;
				delete this->solutionPath;
				delete this->knownNodes;
			};

			/**
			 * Obt�m o n� inicial.
			 *
			 * @return o <T> que representa o n� inicial
			 */
			T *getStartingNode() {
				return this->startingNode;
			};

			/**
			 * Configura o n� inicial.
			 *
			 * @param startingNode 
			 *				o <T> que representa o n� inicial
			 */
			void setStartingNode(T *startingNode) {
				this->startingNode = startingNode;
			};

			/**
			 * Obt�m o n� alvo.
			 *
			 * @return o <T> que representa o n� alvo
			 */
			T *getGoalNode() {
				return this->goalNode;
			};

			/**
			 * Configura o n� alvo.
			 *
			 * @param goalNode 
			 *				o <T> que representa o n� alvo
			 */
			void setGoalNode(T *goalNode) {
				this->goalNode = goalNode;
			};

			/**
			 * Obt�m o mapa de n�s conhecidos.
			 *
			 * @return <code>std::map<std::string, T>*</code> que representa o mapa de n�s conhecidos
			 */
			std::map<std::string, T*> *getKnownNodes() {
				return this->visited;
			};

			/**
			 * Obt�m a quantidade de n�s expandidos.
			 *
			 * @return o <code>size_t</code> que representa a quantidade de n�s expandidos
			 */
			size_t getExpandedNodesCount() {
				return this->expandedNodesCount;
			};

			/**
			 * Determina se uma solu��o foi encontrada.
			 *
			 * @return <code>true</code> caso uma solu��o tenha sido encontrada; do contr�rio <code>false</code>
			 */
			bool hasFoundSolution() {
				return this->hasSolution;
			};

			/**
			 * Obt�m a profundidade da solu��o.
			 *
			 * @throws {@link SolutionNotFoundException} caso o n�o seja encontrada solu��o
			 *
			 * @return o <code>size_t</code> que representa a profundidade da solu��o
			 */
			size_t getSolutionDepth() {
				if (!hasFoundSolution()) {
					throw new pel216::week3::SolutionNotFoundException();
				}
				return this->solutionDepth;
			};
			
			/**
			 * Obt�m o caminho desde o n� inicial at� o alvo.
			 *
			 * @throws {@link SolutionNotFoundException} caso o n�o seja encontrada solu��o
			 *
			 * @return <code>std::vector<T>*</code> que representa o caminho da solu��o
			 */
			std::vector<T*> *getSolutionPath() {
				if (!hasFoundSolution()) {
					throw new pel216::week3::SolutionNotFoundException();
				}
				return this->solutionPath;
			};
			
			/**
			 * Realiza a busca.
			 *
			 * @see #printHeader()
			 * @see #doSearch()
			 */
			void search() {
				this->printHeader();
				this->doSearch();
			};

		}; /* class SearchEngine */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __SEARCHENGINE_H__ */
