#pragma once

#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <inc/Utils.h>
#include <inc/lists/LinkedList.h>
#include <inc/lists/Node.h>

#include <inc/puzzles/8tiles/EightPuzzleNode.h>

using namespace pel216::week3;

namespace pel216 {

	namespace week4 {

		/**
		 * Representa uma fila com prioridade para n�s do tipo @link{EightPuzzleState}.
		 *
		 * @author arrebola
		 */
		class PriorityQueue : public LinkedList<EightPuzzleNode> {
		private:
		public:
			/**
			 * Adiciona um n� � fila considerando uma fila em ordem crescente.<br />
			 * O n�s com prioridade menor s�o colocados � frente da fila.
			 *
			 * @param data
			 *				o @link{Node} de o @link{EightPuzzleNode} que representa o n�
			 */
			void push_asc(IN EightPuzzleNode *data) {
			
				register double heuristic = data->getHeuristic();

				bool gotValidNode = false;
				Node<EightPuzzleNode> *node = this->begin;
				while (pel216::commons::Utils::isValidHandle(node)) {
					if (heuristic < node->getData()->getHeuristic()) {
						gotValidNode = true;
						break;
					}
					node = node->getNext();
				}

				if (gotValidNode) {
					if (node == this->begin) {
						push_front(data);
					} else {
						insertBefore(node, data);
					}
				} else {
					push_back(data);
				}

			};

			/**
			 * Adiciona um n� � fila considerando uma fila em ordem decrescente.<br />
			 * O n�s com prioridade maior s�o colocados � frente da fila.
			 *
			 * @param data
			 *				o @link{Node} de o @link{EightPuzzleNode} que representa o n�
			 */
			void push_desc(IN EightPuzzleNode *data) {
			
				register double heuristic = data->getHeuristic();

				bool gotValidNode = false;
				Node<EightPuzzleNode> *node = this->begin;
				while (pel216::commons::Utils::isValidHandle(node)) {
					if (heuristic > node->getData()->getHeuristic()) {
						gotValidNode = true;
						break;
					}
					node = node->getNext();
				}

				if (gotValidNode) {
					if (node == this->begin) {
						push_front(data);
					} else {
						insertBefore(node, data);
					}
				} else {
					push_back(data);
				}

			};

			/**
			 * Remove um n� do come�o da fila.
			 *
			 * @return o @link{EightPuzzleNode} que representa o n�
			 */
			EightPuzzleNode *pop() {
			
				EightPuzzleNode *data = NULL;

				if (isEmpty()) {
					return data;
				}

				if (pel216::commons::Utils::isValidHandle(this->begin)) {
					data = this->begin->getData();
					Node<EightPuzzleNode> *next = this->begin->getNext();
					delete this->begin;
					if (pel216::commons::Utils::isValidHandle(next)) {
						next->setPrevious(next);
					}
					this->begin = next;
					this->listSize--;
				}

				return data;

			};

		}; /* class PriorityQueue */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* _PRIORITY_QUEUE_H_ */
