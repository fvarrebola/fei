#pragma once

#ifndef __EPISODE_H__
#define __EPISODE_H__

#include <inc\Utils.h>
#include <inc\Logger.h>
#include <inc\ex\IllegalParameterException.h>

#include <inc\EpisodeState.h>

#include <inc\RLConstants.h>

using namespace pel216::commons;

namespace pel208 {

	namespace week7 {

		/**
		 * Classe que representa um episódio.<br />
		 *
		 * @author arrebola
		 */
		class Episode {
		private:
			std::vector<EpisodeState*> *visitedStates;

		public:
			/**
			 * Construtor.<br />
			 */
			Episode() {
				this->visitedStates = new std::vector<EpisodeState*>();
			};

			/**
			 * Destrutor.<br />
			 */
			~Episode() {
				delete this->visitedStates;
			};

			/**
			 * Adição um estado ao episódio.<br />
			 * 
			 * @param state
			 *				o EpisodeState que representa o estado do episódio
			 */
			PUBLIC void add(IN EpisodeState* state) {

				if (Utils::isInvalidHandle(state)) {
					throw new IllegalParameterException();
				}

				this->visitedStates->push_back(state);

			};

			/**
			 * Retorna o tamanho do episódio.<br />
			 *
			 * @return o <code>size_t</code> que representa o tamanho do episódio
			 */
			PUBLIC size_t size() {
				return this->visitedStates->size();
			};

			/**
			 * Retorna os estados do episódio.<br />
			 *
			 * @return o <code>std::vector</code> de EpisodeState que representa os estado do episódio
			 */
			PUBLIC std::vector<EpisodeState*> *getVisitedStates() {
				return this->visitedStates;
			};

			/**
			 * Imprime detalhes sobre o episódio.<br />
			 */
			PUBLIC void dumpToFile() {

				size_t size = this->visitedStates->size();

				Logger::logToFile("Episodio com %d estados...\n", size);

				size_t counter = 1;
				for (std::vector<EpisodeState*>::iterator iterator =  this->visitedStates->begin() ; 
						iterator != this->visitedStates->end(); 
						++iterator) {

					register size_t stateIdx = (*iterator)->getStateIdx();
					register size_t actionIdx = (*iterator)->getActionIdx();
					register double r = (*iterator)->getR();

					Logger::logToFile("  %05d: s=%02d a=%s Rt=%f\n", 
						counter++,
						stateIdx, 
						(actionIdx == 0 ? "U" : ((actionIdx == 1) ? "D" : ((actionIdx == 2) ? "L" : "R"))),
						 r);

				}

			};

		}; /* class Episode */

	} /* namespace week7 */

} /* namespace pel208 */

#endif /* __EPISODE_H__ */
