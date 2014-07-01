#pragma once

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <inc/Collection.h>

namespace pel216 {

	namespace week1 {

		/**
		 * Representa uma fila.
		 *
		 * @author arrebola
		 */
		class Queue : public Collection {

		private:

		protected:
			/**
			 * Adiciona um elemento ao fim na colecao.
			 *
			 * @param element
			 *				o <code>Element</code> que representa o elemento
			 *
			 * @return o <code>true</code> caso o elemento tenha sido adicionado com sucesso
			 */
			bool add(IN Element *element);

			/**
			 * Remove um elemento do fim colecao.
			 *
			 * @return o <code>true</code> caso o elemento tenha sido removido com sucesso
			 */
			bool remove();

		public:
			/**
			 * Construtor.
			 */
			Queue();

			/**
			 * Destrutor.
			 */
			virtual ~Queue();

			/**
			 * Insere um elemento no final da fila.
			 *
			 * @param element
			 *				o <code>Element</code> que representa o elemento
			 *
			 * @return o <code>true</code> caso a insersao tenha sido bem sucedida; do contrario <code>false</code>
			 */
			bool push(IN Element *element);
			
			/**
			 * Remove o elemento do comeco da fila.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *pop();
			
			/**
			 * Obtem o elemento do comeco da fila sem removê-lo.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *peek();

		}; // class Queue

	} // namespace week1

} // namespace pel216

#endif
