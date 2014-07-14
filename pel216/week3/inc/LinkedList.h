#pragma once

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <inc/Utils.h>
#include <inc/Node.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa uma lista ligada.
		 *
		 * @author arrebola
		 */
		class LinkedList {
		
		private:
			int size;
			Node *begin;
			Node *end;

		protected:
			/**
			 * Adiciona um no na lista.
			 *
			 * @param element
			 *				o <code>Node *</code> que representa o no
			 *
			 * @return o <code>true</code> caso o no tenha sido adicionado com sucesso
			 */
			virtual bool add(IN Node *node) = 0;

			/**
			 * Remove um no da lista.
			 *
			 * @return o <code>true</code> caso o no tenha sido removido com sucesso
			 */
			virtual bool remove() = 0;

		public:
			/**
			 * Construtor.
			 *
			 * @param begin
			 * 				o <code>Node *</code> que representa o inicio da lista
			 */
			LinkedList(IN Node *begin);

			/**
			 * Destrutor.
			 */
			virtual ~LinkedList();

			/**
			 * Retorna a quantidade de nos na lista.
			 *
			 * @return o <code>int</code> que representa a quantidade de nos na lista
			 */
			int count() const {
				return this->size;
			};

			/**
			 * Obtem o primeiro no da lista.
			 *
			 * @return o <code>Node *</code> que representa o no
			 */
			Node *getFirstElement();

			/**
			 * Obtem o ultimo no da lista.
			 *
			 * @return o <code>Element</code> que representa o no
			 */
			Node *getLastElement();

			/**
			 * Obtem um no da lista de uma determinada posicao.
			 *
			 * @param position
			 *				o <code>int</code> que representa a posicao
			 *
			 * @return o <code>Node *</code> que representa o no
			 */
			Node *getNthElement(IN int position);

			/**
			 * Determina se a lista esta vazia.
			 *
			 * @return <code>true</code> caso a lista esteja vazia; do contrario <code>false</code>
			 */
			bool isEmpty() {
				return (this->size == ZERO);
			};

			/**
			 * Adiciona um no na lista.
			 *
			 * @param node
			 *				o <code>Node</code> que representa o no
			 *
			 * @return o <code>true</code> caso o elemento tenha sido adicionado com sucesso
			 */
			bool add(IN Node *node);

			/**
			 * Remove um no na lista.
			 *
			 * @return o <code>true</code> caso o elemento tenha sido removido com sucesso
			 */
			bool remove();

			/**
			 * Limpa a lista, removendo todos os nos.
			 *
			 * @return o <code>true</code> caso a colecao tenha sido limpa com sucesso
			 */
			bool clear();

			/**
			 * Determina o indice de um no da lista.
			 *
			 * @param node
			 *				o <code>Node *</code> que representa o no
			 *
			 * @return o <code>int</code> que representa a posicao do elemento na colecao
			 */
			int indexOf(IN Node *node);

			/**
			 * Determina se um no esta presente na lista.
			 *
			 * @param node
			 *				o <code>Node *</code> que representa o no
			 *
			 * @return <code>true</code> se o no estiver presente; do contrario <code>false</code>
			 */
			bool contains(IN Node *node);

		}; /* class LinkedList */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* _LINKEDLIST_H_ */
