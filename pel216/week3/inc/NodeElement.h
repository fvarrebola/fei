#pragma once

#ifndef _NODEELEMENT_H_
#define _NODEELEMENT_H_

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Representa um dado armazenado em um no.
		 *
		 * @author arrebola
		 */
		class NodeElement {

		private:
			int data[9];

		public:
			/**
			 * Construtor.
			 */
			NodeElement(int data[EIGHT_PUZZLE_STATE_SIZE]) {
				this->data = data;
			};

			/**
			 * Destrutor.
			 */
			virtual ~NodeElement();

			/**
			 * Retorna o dado do no.
			 *
			 * @return o <code>void *</code> que representa o dado
			 */
			int *getData() {
				return this->data;
			};

		}; /* class NodeElement */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* _NODEELEMENT_H_ */
