#pragma once

#ifndef _STACK_H_
#define _STACK_H_

#include <inc/Collection.h>

#include <stack>

namespace pel216 {

	namespace week1 { 

		class Stack : public Collection {

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
			Stack();

			/**
			 * Destrutor.
			 */
			virtual ~Stack();

			/**
			 * Insere um elemento no topo da pilha.
			 *
			 * @param element
			 *				o <code>Element</code> que representa o elemento
			 *
			 * @return o <code>true</code> caso a insersao tenha sido bem sucedida; do contrario <code>false</code>
			 */
			bool push(IN Element *element);
			
			/**
			 * Remove o elemento do topo da pilha.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *pop();
			
			/**
			 * Obtem o elemento do topo da pilha sem removê-lo.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *peek();
			
		}; // class Stack

	} // namespace week1

} // namespace pel216

#endif
