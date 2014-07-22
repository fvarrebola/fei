#pragma once

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <inc/Utils.h>
#include <inc/lists/Node.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa uma lista ligada.
		 *
		 * @author arrebola
		 */
		template <class T>
		class LinkedList {
		
		private:
			size_t listSize;
			Node<T> *begin;
			Node<T> *end;

		public:
			/**
			 * Construtor.
			 */
			LinkedList() {
				this->listSize = 0;
			};

			/**
			 * Destrutor.
			 */
			virtual ~LinkedList() {
			};

			/**
			 * Retorna a quantidade de n�s na lista.
			 *
			 * @return o <code>size_t</code> que representa a quantidade de n�s na lista
			 */
			size_t size() {
				return this->listSize;
			};

			/**
			 * Determina se a lista esta vazia.
			 *
			 * @return <code>true</code> caso a lista esteja vazia; do contrario <code>false</code>
			 */
			bool isEmpty() {
				return (this->listSize == ZERO);
			};

			/**
			 * Obt�m um n� do come�o da lista.
			 *
			 * @return o <code>Node<T>*</code> que representa o dado do n�
			 */
			Node<T> *front() {
				return this->begin;
			};

			/**
			 * Obt�m o n� do fim da lista.
			 *
			 * @return o <code>Node<T>*</code> que representa o dado do n�
			 */
			Node<T> *back() {
				return this->end;
			};

			/**
			 * Adiciona um n� ao fim da lista.
			 *
			 * @param data
			 *				o <code>T*</code> que representa o dado do n�
			 */
			void push_back(IN T *data) {
				
				Node<T> *node = new Node<T>(data);

				// determina se existe elemento anterior ou o novo n� � o primeiro
				Node<T> *previous = NULL;
				if (isEmpty()) {
					previous = node;
					this->begin = node;
				} else {
					previous = this->end;
					previous->setNext(node);
				}
				node->setPrevious(previous);
				node->setNext(NULL);

				this->end = node;
				this->listSize++;

			};

			/**
			 * Adiciona um n� ao come�o da lista.
			 *
			 * @param data
			 *				o <code>T*</code> que representa o dado do n�
			 */
			void push_front(IN T *data) {
			
				Node<T> *node = new Node<T>();
				node->setPrevious(node);
				node->setNext(this->begin);
				node->setData(data);

				this->begin->setPrevious(node);
				this->begin = node;

				this->listSize++;

			};

			/**
			 * Remove um n� do fim da lista.
			 *
			 * @return o <code>T*</code> que representa o dado do n�
			 */
			T *pop_back() {

				T *data = NULL;

				if (isEmpty()) {
					return data;
				}

				Node<T> *node = this->end;
				if (pel216::commons::Utils::isValidHandle(node)) {
					data = node->getData();
					Node<T> *previous = node->getPrevious();
					if (pel216::commons::Utils::isValidHandle(previous)) {
						previous->setNext(NULL);
					}
					delete node;
					this->end = previous;
					this->listSize--;
				}

				return data;

			};

			/**
			 * Remove um n� do come�o da lista.
			 *
			 * @return o <code>T*</code> que representa o dado do n�
			 */
			T *pop_front() {
			
				T *data = NULL;

				if (isEmpty()) {
					return data;
				}

				if (pel216::commons::Utils::isValidHandle(this->begin)) {
					data = this->begin->getData();
					Node<T> *next = this->begin->getNext();
					delete this->begin;
					if (pel216::commons::Utils::isValidHandle(next)) {
						next->setPrevious(next);
					}
					this->begin = next;
					this->listSize--;
				}

				return data;

			};

		}; /* class LinkedList */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* _LINKEDLIST_H_ */
