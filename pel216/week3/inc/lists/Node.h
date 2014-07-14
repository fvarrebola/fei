#pragma once

#ifndef __NODE_H__
#define __NODE_H__

#include <inc/Utils.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um nó.
		 *
		 * @author arrebola
		 */
		template<class T>
		class Node {

		private:
			Node<T> *previous;
			Node<T> *next;
			T data;

		public:
			/**
			 * Construtor.
			 *
			 * @param data
			 * 				o <code>T</code> que representa o dado
			 * @param Node<T>
			 * 				o <code>Node<T></code> que representa o nó anterior
			 * @param Node<T>
			 * 				o <code>Node<T></code> que representa o nó seguinte
			 */
			Node(T data, Node<T> *previous = NULL, Node<T> *next = NULL) {
			    this->data = data;
				this->previous = previous;
				this->next = next;
			};

			/**
			 * Obt�m o nó anterior ligado ao nó atual.
			 *
			 * @return o <code>Node<T>*</code> que representa o nó anterior
			 */
			Node<T> *getPrevious() {
				return this->previous;
			};

			/**
			 * Configura o nó anterior ligado ao nó atual.
			 *
			 * @param previous
			 * 					o <code>Node<T>*</code> que representa o nó anterior
			 */
			void setPrevious(Node<T> *previous) {
				this->previous = previous;
			};

			/**
			 * Obt�m o nó posterior ligado ao nó atual.
			 *
			 * @return o <code>Node<T>*</code> que representa o nó posterior
			 */
			Node<T> *getNext() {
				return this->next;
			};

			/**
			 * Configura o nó posterior ligado ao nó atual.
			 *
			 * @param next
			 * 					o <code>Node<T>*</code> que representa o nó posterior
			 */
			void setNext(Node<T> *next) {
				this->next = next;
			};

			/**
			 * Obt�m o dado armazenado no nó.
			 *
			 * @return o <code>T</code> que representa o dado
			 */
			T getData() {
				return this->data;
			};

			/**
			 * Configura o dado armazenado no nó.
			 *
			 * @param data
			 * 				o <code>T</code> que representa o dado
			 */
			void setData(T data) {
				this->data = data;
			};

		}; /* class Node */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __NODE_H__ */
