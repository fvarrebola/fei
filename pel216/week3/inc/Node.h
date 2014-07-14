#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa um no de uma lista ligada.
		 *
		 * @author arrebola
		 */
		template <class T>
		class Node {

		private:
			Node<T> *bLink;
			Node<T> *fLink;
			NodeElement *element;

		public:
			/**
			 * Construtor.
			 *
			 * @param element
			 * 				o <code>NodeElement *</code> que representa o dado do no
			 * @param bLink
			 * 				o <code>Node *</code> que representa o no anterior
			 * @param fLink
			 * 				o <code>Node *</code> que representa o no posterior
			 */
			Node(NodeElement *element, Node *bLink, Node *fLink) {

				if (pel216::commons::Utils::isInvalidHandle(element)) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->element = element;
				this->bLink = bLink;
				this->fLink = fLink;

			};

			/**
			 * Destrutor.
			 */
			virtual ~Node();

			/**
			 * Retorna o elemento armazenado no no.
			 *
			 * @return o <code>NodeElement *</code> que representa o elemento
			 */
			NodeElement *getElement() {
				return this->element;
			};

			/**
			 * Retorna o no anterior.
			 *
			 * @return o <code>Node</code> que representa o no anterior
			 */
			Node *getBLink() {
				return this->bLink;
			};

			/**
			 * Retorna o no posterior.
			 *
			 * @return o <code>Node</code> que representa o no posterior
			 */
			Node *getFLink() {
				return this->fLink;
			};

		}; /* class Node */

	} /* namespace week3 */

} /* namespace pel216 */

#endif
