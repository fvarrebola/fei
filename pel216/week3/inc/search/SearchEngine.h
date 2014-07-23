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
		 * O <i>template</i> deve definir uma classe que represente um nó.
		 *
		 * @author arrebola
		 */
		template <class T>
		class SearchEngine {
		private:
			std::string name;

			/**
			 * Imprime o cabeçalho do mecanismo de buscas.
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

			T *startingNode;					/* o nó de partida */
			T *goalNode;						/* o nó alvo */

			// os nós conhecidos
			std::map<std::string,T*> *knownNodes;
			
			bool hasSolution;					/* se há solução */
			size_t maxAllowedDepth;				/* a profundidade máxima permitida */
			size_t maxKnownDepth;				/* a maior profundidade atingida */
			std::vector<T*> *solutionPath;		/* o caminho até a solução */
			size_t solutionDepth;				/* a profundidade até a solução */
			
			size_t expandedNodesCount;			/* a quantidade de nós expandidos */

			bool debug;							/* indica se as mensagens de rastreio da execução devem ser exibidas */

			/**
			 * Registra o conteúdo da estrutura de dados utilizada pelo mecanismo de busca.
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
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			virtual void setup(size_t maxAllowedDepth, bool debug) {
				this->maxAllowedDepth = maxAllowedDepth;
				this->debug = debug;
			};

			/**
			 * Adiciona um nó ao mapa de nós conhecidos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o nó
			 */
			void addKnownNode(T *node) {
				knownNodes->insert(std::pair<std::string,T*>((node)->getState()->hashCode(), node));
			};

			/**
			 * Determina se um nó já é conhecido.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o nó
			 *
			 * @return <code>true</code> caso o nó seja conhecido; do contrário <code>false</code>
			 */
			bool isKnownNode(T *node) {
				return (knownNodes->find((node)->getState()->hashCode()) != knownNodes->end());
			};

			/**
			 * Adiciona um estado à lista de movimentos.
			 *
			 * @param node
			 * 				o @link{EightPuzzleNode} que representa o nó
			 */
			void addPath(T *node) {
				solutionPath->insert(solutionPath->begin(), node);
			};


			/**
			 * Expande um nó.
			 *
			 * @param node
			 *				o <T> que representa o nó
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
			 * Obtém o nó inicial.
			 *
			 * @return o <T> que representa o nó inicial
			 */
			T *getStartingNode() {
				return this->startingNode;
			};

			/**
			 * Configura o nó inicial.
			 *
			 * @param startingNode 
			 *				o <T> que representa o nó inicial
			 */
			void setStartingNode(T *startingNode) {
				this->startingNode = startingNode;
			};

			/**
			 * Obtém o nó alvo.
			 *
			 * @return o <T> que representa o nó alvo
			 */
			T *getGoalNode() {
				return this->goalNode;
			};

			/**
			 * Configura o nó alvo.
			 *
			 * @param goalNode 
			 *				o <T> que representa o nó alvo
			 */
			void setGoalNode(T *goalNode) {
				this->goalNode = goalNode;
			};

			/**
			 * Obtém o mapa de nós conhecidos.
			 *
			 * @return <code>std::map<std::string, T>*</code> que representa o mapa de nós conhecidos
			 */
			std::map<std::string, T*> *getKnownNodes() {
				return this->visited;
			};

			/**
			 * Obtém a quantidade de nós expandidos.
			 *
			 * @return o <code>size_t</code> que representa a quantidade de nós expandidos
			 */
			size_t getExpandedNodesCount() {
				return this->expandedNodesCount;
			};

			/**
			 * Determina se uma solução foi encontrada.
			 *
			 * @return <code>true</code> caso uma solução tenha sido encontrada; do contrário <code>false</code>
			 */
			bool hasFoundSolution() {
				return this->hasSolution;
			};

			/**
			 * Obtém a profundidade da solução.
			 *
			 * @throws {@link SolutionNotFoundException} caso o não seja encontrada solução
			 *
			 * @return o <code>size_t</code> que representa a profundidade da solução
			 */
			size_t getSolutionDepth() {
				if (!hasFoundSolution()) {
					throw new pel216::week3::SolutionNotFoundException();
				}
				return this->solutionDepth;
			};
			
			/**
			 * Obtém o caminho desde o nó inicial até o alvo.
			 *
			 * @throws {@link SolutionNotFoundException} caso o não seja encontrada solução
			 *
			 * @return <code>std::vector<T>*</code> que representa o caminho da solução
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
