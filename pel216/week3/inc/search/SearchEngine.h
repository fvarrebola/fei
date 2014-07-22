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

		protected:
			/* a estrutura de dados utilizada pelo mecanismo */
			LinkedList<T> *list; 				

			T *startingNode;					/* o n� de partida */
			T *goalNode;						/* o n� alvo */

			// os n�s conhecidos
			std::map<std::string,T*> *knownNodes;
			
			// informa��es sobre a solu��o
			bool hasSolution;					/* se h� solu��o */
			size_t maxAllowedDepth;				/* a profundidade m�xima permitida */
			size_t maxKnownDepth;				/* a maior profundidade atingida */
			std::vector<T*> *solutionPath;		/* o caminho at� a solu��o */
			size_t solutionDepth;				/* a profundidade at� a solu��o */
			
			// a quantidade de n�s expandidos
			size_t expandedNodesCount; 

			// indica se as mensagens de rastreio da execu��o devem ser exibidas
			bool debug;

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
			 * Expande um n�.
			 *
			 * @param node
			 *				o <T> que representa o n�
			 */
			virtual void expandNode(T *node) {
			};
		
			/**
			 * Imprime o conte�do da estrutura de dados utilizada pelo mecanismo de busca.
			 */
			void dumpListToFile() {
				
				if (pel216::commons::Utils::isInvalidHandle(this->list)) {
					return;
				}

				Logger::logToFile("----------------------------------------\n"); 
				Logger::logToFile("Imprimindo lista\n"); 
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

		public:
			/**
			 * Construtor padr�o.
			 */
			SearchEngine() {
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
			 */
			virtual void search() {
			};

		}; /* class SearchEngine */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __SEARCHENGINE_H__ */
