#pragma once

#ifndef __SEARCHENGINE_H__
#define __SEARCHENGINE_H__

#include <string>
#include <list>
#include <vector>
#include <map>

#include <inc/Utils.h>
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

		protected:
			std::list<T*> *list; 				/* a estrutura de dados utilizada pelo mecanismo */

			T *startingNode;					/* o nó de partida */
			T *goalNode;						/* o nó alvo */

			// os nós conhecidos
			std::map<std::string,T*> *knownNodes;
			
			// informações sobre a solução
			size_t maxDepth;					/* a profundidade máxima permitida */
			bool hasSolution;					/* se há solução */
			std::vector<T*> *solutionPath;		/* o caminho até a solução */
			size_t solutionDepth;				/* a profundidade até a solução */
			
			// a quantidade de nós expandidos
			size_t expandedNodesCount; 

			// indica se as mensagens de rastreio da execução devem ser exibidas
			bool debug;

			/**
			 * Configura o mecanismo de busca.
			 *
			 * @param maxDepth
			 *				o <code>size_t</code> que representa a profundidade máxima permitida
			 * @param debug
			 *				determina se as mensagens de <i>debug</i> devem ser exibidas
			 */
			virtual void setup(size_t maxDepth, bool debug) {
				this->maxDepth = maxDepth;
				this->debug = debug;
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
			 * Imprime o conteúdo da estrutura de dados utilizada pelo mecanismo de busca.
			 */
			void dumpList() {

				if (pel216::commons::Utils::isInvalidHandle(this->list)) {
					return;
				}

				Logger::log("----------------------------------------\n"); 
				Logger::log("Imprimindo lista\n"); 
				Logger::log("----------------------------------------\n"); 
				size_t idx = 0;
				for (std::list<T*>::iterator it = this->list->begin(); it != this->list->end(); ++it) {
					Logger::log("\t#%d %s\n", idx++, (*it)->toString().c_str());
				}
				Logger::log("----------------------------------------\n");

			};

		public:
			/**
			 * Construtor padrão.
			 */
			SearchEngine() {
				this->list = new std::list<T*>();
				this->solutionPath = new std::vector<T*>;
				this->knownNodes = new std::map<std::string,T*>;
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
			 */
			virtual void search() {
			};

		}; /* class SearchEngine */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __SEARCHENGINE_H__ */
