#pragma once

#ifndef __NODE_H__
#define __NODE_H__

#include <inc/Utils.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um n贸.
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
			 * 				o <code>Node<T></code> que representa o n贸 anterior
			 * @param Node<T>
			 * 				o <code>Node<T></code> que representa o n贸 seguinte
			 */
			Node(T data, Node<T> *previous = NULL, Node<T> *next = NULL) {
			    this->data = data;
				this->previous = previous;
				this->next = next;
			};

			/**
			 * Obt閙 o n贸 anterior ligado ao n贸 atual.
			 *
			 * @return o <code>Node<T>*</code> que representa o n贸 anterior
			 */
			Node<T> *getPrevious() {
				return this->previous;
			};

			/**
			 * Configura o n贸 anterior ligado ao n贸 atual.
			 *
			 * @param previous
			 * 					o <code>Node<T>*</code> que representa o n贸 anterior
			 */
			void setPrevious(Node<T> *previous) {
				this->previous = previous;
			};

			/**
			 * Obt閙 o n贸 posterior ligado ao n贸 atual.
			 *
			 * @return o <code>Node<T>*</code> que representa o n贸 posterior
			 */
			Node<T> *getNext() {
				return this->next;
			};

			/**
			 * Configura o n贸 posterior ligado ao n贸 atual.
			 *
			 * @param next
			 * 					o <code>Node<T>*</code> que representa o n贸 posterior
			 */
			void setNext(Node<T> *next) {
				this->next = next;
			};

			/**
			 * Obt閙 o dado armazenado no n贸.
			 *
			 * @return o <code>T</code> que representa o dado
			 */
			T getData() {
				return this->data;
			};

			/**
			 * Configura o dado armazenado no n贸.
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
