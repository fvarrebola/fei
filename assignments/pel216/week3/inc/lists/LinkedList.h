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
		
		protected:
			size_t listSize;
			Node<T> *begin;
			Node<T> *end;

		public:
			/**
			 * Construtor.
			 */
			LinkedList() {
				this->listSize = 0;
				this->begin = NULL;
				this->end = NULL;
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
			 * Insere um n� ap�s um determinado n�.
			 *
			 * @param node
			 *				o @link{Node<T>} que representa o n�
			 * @param data
			 *				o <code>T*</code> que representa o dado do n�
			 */
			void insertAfter(IN Node<T> *node, IN T *data) {

				Node<T> *newNode = new Node<T>(data);

				Node<T> *nextNode = node->getNext();
				if (pel216::commons::Utils::isValidHandle(nextNode)) {
					nextNode->setPrevious(newNode);
				}
				newNode->setNext(nextNode);
				newNode->setPrevious(node);
				node->setNext(newNode);

				this->listSize++;

			};

			/**
			 * Insere um n� antes de um determinado n�.
			 *
			 * @param node
			 *				o @link{Node<T>} que representa o n�
			 * @param data
			 *				o <code>T*</code> que representa o dado do n�
			 */
			void insertBefore(IN Node<T> *node, IN T *data) {

				Node<T> *newNode = new Node<T>(data);

				Node<T> *previousNode = node->getPrevious();
				previousNode->setNext(newNode);
				newNode->setPrevious(previousNode);
				newNode->setNext(node);
				node->setPrevious(newNode);

				this->listSize++;

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

				if (pel216::commons::Utils::isValidHandle(this->begin)) {
					this->begin->setPrevious(node);
				}
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

			/**
			 * Registra o conte�do da estrutura de dados utilizada pelo mecanismo de busca.
			 */
			virtual void dumpToFile() {

				if (isEmpty()) {
					return;
				}

				Logger::logToFile("----------------------------------------\n"); 
				Logger::logToFile("Imprimindo estrutura de dados \n"); 
				Logger::logToFile("----------------------------------------\n"); 
				
				size_t idx = 0;
				Node<T> *node = front(); 
				while (pel216::commons::Utils::isValidHandle(node)) {
					T *data = node->getData();
					if (pel216::commons::Utils::isValidHandle(data)) {
						Logger::logToFile("\t#%d %s\n", idx++, (data)->toString().c_str());
					}
					node = node->getNext();
				}
				Logger::logToFile("----------------------------------------\n");
				
			};


		}; /* class LinkedList */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* _LINKEDLIST_H_ */
