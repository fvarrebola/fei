#pragma once

#ifndef __STATE_H__
#define __STATE_H__

#include <vector>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um estado.
		 *
		 * @author arrebola
		 */
		template<class T>
		class State {

		private:
			T data;

		public:
			/**
			 * Construtor padrão.
			 */
			State() {
			};
			
			/**
			 * Destrutor.
			 */
			virtual ~State() {
			};

			/**
			 * Obtém o dado do estado.
			 *
			 * @return o <code>T</code> que representa o dado
			 */
			T getData() {
				return this->data;
			};

			/**
			 * Configura o dado armazenado no estado.
			 *
			 * @param data
			 * 				o <code>T</code> que representa o dado
			 *
			 * @throws {@link IllegalParameterException} caso o dado seja inválido
			 */
			void setData(T data) {
				this->data = data;
			};

			/**
			 * Obtém o <i>hash code</i> do estado.
			 *
			 * @return o <code>std::string</code> que representa o <i>hash code</i> do estado
			 */
			virtual std::string hashCode() {
				return NULL;
			};

			/**
			 * Determina se o estado informado é o estado alvo.
			 *
			 * @param obj
			 * 					o <code>EightPuzzleState*</code> que representa o estado
			 * @param goal
			 * 					o <code>EightPuzzleState*</code> que representa o estado alvo
			 *
			 * @return <code>true</code> caso o estado informado seja o estado alvo; do contrário <code>false</code>
			 */
			virtual bool equals(State<T> obj) {
				return false;
			};

			/**
			 * Retorna a representação da classe.
			 *
			 * @return o <code>std::string</code> que representa a classe
			 */
			virtual std::string toString() {
				return NULL;
			};

		}; /* class State */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __STATE_H__ */
