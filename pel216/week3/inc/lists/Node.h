#pragma once

#ifndef __NODE_H__
#define __NODE_H__

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa um nó de uma lista ligada.
		 *
		 * @author arrebola
		 */
		template <class T>
		class Node {

		private:
			Node<T> *previous;
			Node<T> *next;
			T *data;

		public:
			/**
			 * Construtor padrão.
			 */
			Node() {
			};

			/**
			 * Construtor.
			 *
			 * @param data
			 * 				o <code><T></code> que representa o dado do nó
			 * @param previous
			 * 				o <code>Node *</code> que representa o no anterior
			 * @param next
			 * 				o <code>Node *</code> que representa o no posterior
			 */
			Node(T* data, Node<T> *previous = NULL, Node<T> *next = NULL) {
				this->data = data;
				this->previous = previous;
				this->next = next;
			};

			/**
			 * Destrutor.
			 */
			virtual ~Node() {
			};

			/**
			 * Retorna o dado armazenado no nó.
			 *
			 * @return o <code>T*</code> que representa o dado armazenado no nó
			 */
			T *getData() {
				return this->data;
			};

			/**
			 * Configura o dado armazenado no nó.
			 *
			 * @param data
			 *				o <code>T*</code> que representa o dado armazenado no nó
			 */
			void setData(T *data) {
				this->data = data;
			};

			/**
			 * Retorna o nó anterior.
			 *
			 * @return o <code>Node<T>*</code> que representa o nó anterior
			 */
			Node<T> *getPrevious() {
				return this->previous;
			};

			/**
			 * Configura o nó anterior.
			 *
			 * @param previous
			 *				o <code>Node<T>*</code> que representa o nó anterior
			 */
			void setPrevious(Node<T> *previous) {
				this->previous = previous;
			};
			
			/**
			 * Retorna o nó posterior.
			 *
			 * @return o <code>Node<T>*</code> que representa o nó posterior
			 */
			Node<T> *getNext() {
				return this->next;
			};

			/**
			 * Configura o nó posterior.
			 *
			 * @param next
			 *				o <code>Node<T>*</code> que representa o nó posterior
			 */
			void setNext(Node<T> *next) {
				this->next = next;
			};

		}; /* class Node */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __NODE_H__ */
