#pragma once

#ifndef _COLLECTION_H_
#define _COLLECTION_H_

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/Element.h>

#define	MAX_SIZE							256

namespace pel216 {

	namespace week1 {

		enum Types {
			UNDEFINED = 0,
			STACK = 1,
			QUEUE = 2
		};

		/**
		 * Representa uma colecao de elementos que deve ser estendida por pilhas e filas.
		 *
		 * @author arrebola
		 */
		class Collection {
		
		private:
			int type; // o tipo da colecao

		protected:
			int size; // quantidade de elementos na colecao
			Element *collection[MAX_SIZE]; // a colecao de elementos

			/**
			 * Adiciona um elemento na colecao.
			 *
			 * @param element
			 *				o <code>Element</code> que representa o elemento
			 *
			 * @return o <code>true</code> caso o elemento tenha sido adicionado com sucesso
			 */
			virtual bool add(IN Element *element) = 0;

			/**
			 * Remove um elemento da colecao.
			 *
			 * @return o <code>true</code> caso o elemento tenha sido removido com sucesso
			 */
			virtual bool remove() = 0;

		public:
			/**
			 * Construtor.
			 */
			Collection();

			/**
			 * Destrutor.
			 */
			virtual ~Collection();

			/**
			 * Retorna a quantidade de elementos na colecao.
			 *
			 * @return o <code>int</code> que representa a quantidade de elementos na colecao
			 */
			int count() {
				return this->size;
			}

			/**
			 * Determina se a colecao esta vazia.
			 *
			 * @return <code>true</code> caso a colecao esteja vazia; do contrario <code>false</code>
			 */
			bool isEmpty() {
				return (this->size == ZERO);
			}

			/**
			 * Obtem um elemento na colecao de uma determinada posicao.
			 *
			 * @param position
			 *				o <code>int</code> que representa a posicao
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *getNthElement(IN int position);

			/**
			 * Obtem o primeiro elemento da colecao.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *getFirstElement();

			/**
			 * Obtem o ultimo elemento da colecao.
			 *
			 * @return o <code>Element</code> que representa o elemento
			 */
			Element *getLastElement();

			/**
			 * Limpa a colecao, removendo todos os elementos.
			 *
			 * @return o <code>true</code> caso a colecao tenha sido limpa com sucesso
			 */
			bool clear();

			/**
			 * Busca um elemento na colecao.
			 *
			 * @param element
			 *				o <code>Element</code> que representa o elemento
			 *
			 * @return o <code>int</code> que representa a posicao do elemento na colecao
			 */
			int search(IN Element *element);

			/**
			 * Imprime o conteúdo de uma colecao.
			 */
			void dump();

		}; // class Collection

	} // namespace week1

} // namespace pel216

#endif
