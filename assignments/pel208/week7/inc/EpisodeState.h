#pragma once

#ifndef __EPISODE_STATE_H__
#define __EPISODE_STATE_H__

#include <inc\Utils.h>

using namespace pel216::commons;

namespace pel208 {

	namespace week7 {

		/**
		 * Classe que representa um estado do episódio.<br />
		 *
		 * @author arrebola
		 */
		class EpisodeState {
		private:
			size_t stateIdx;
			size_t actionIdx;
			EpisodeState *previous;
			EpisodeState *next;
			double R;

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param stateIdx
			 *				 o <code>size_t</code> que representa o estado
			 * @param actionIdx
			 *				 o <code>size_t</code> que representa a ação
			 * @param previous
			 *				 o EpisodeState que representa o estado anterior
			 * @param next
			 *				 o EpisodeState que representa o estado posterior
			 */
			EpisodeState(
					IN size_t stateIdx, 
					IN size_t actionIdx, 
					IN EpisodeState *previous = NULL, 
					IN EpisodeState *next = NULL) {
				this->stateIdx = stateIdx;
				this->actionIdx = actionIdx;
				this->previous = previous;
				this->next = next;
				this->R = 0;
			};
			
			/**
			 * Destrutor.<br />
			 */
			~EpisodeState() {
			};
			
			/**
			 * Determina se um objeto é igual à instância atual.<br />
			 *
			 * @param that
			 *				o EpisodeState que representa o objeto
			 *
			 * @return <code>true</code> caso o objeto seja igual; do contrário <code>false</code>
			 */
			PUBLIC bool equals(IN EpisodeState *that) {
				
				bool equals = false;
				if (Utils::isValidHandle(that)) {
					equals = ((this->getActionIdx() == that->getActionIdx()) && 
						(this->getStateIdx() == that->getStateIdx()));
				}

				return equals;
			
			};

			/**
			 * Retorna o estado.<br />
			 *
			 * @return o <code>size_t</code> que representa o estado
			 */
			PUBLIC size_t getStateIdx() {
				return this->stateIdx;
			};

			/**
			 * Retorna o ação.<br />
			 *
			 * @return o <code>size_t</code> que representa a ação
			 */
			PUBLIC size_t getActionIdx() {
				return this->actionIdx;
			};

			/**
			 * Retorna o estado anterior.<br />
			 *
			 * @return o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC EpisodeState *getPrevious() {
				return this->previous;
			};

			/**
			 * Retorna o estado anterior.<br />
			 *
			 * @param previous 
			 *				o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC void setPrevious(IN EpisodeState *previous) {
				this->previous = previous;
			};

			/**
			 * Retorna o próximo estado.<br />
			 *
			 * @return o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC EpisodeState *getNext() {
				return this->next;
			};

			/**
			 * Retorna o próximo estado.<br />
			 *
			 * @param next 
			 *				o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC void setNext(IN EpisodeState *next) {
				this->next = next;
			};

			/**
			 * Obtém valor de R.<br />
			 *
			 * @return o <code>double</code> que representa o R
			 */
			PUBLIC double getR() {
				return this->R;
			};

			/**
			 * Configura o valor de R.<br />
			 *
			 * @param R 
			 *				o <code>double</code> que representa o R
			 */
			PUBLIC void setR(IN double R) {
				this->R = R;
			};

		}; /* class EpisodeState */

	} /* namespace week7 */

} /* namespace pel208 */

#endif /* __EPISODE_STATE_H__ */
