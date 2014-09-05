#pragma once

#ifndef __NEAREST_NEIGHBOR_H__
#define __NEAREST_NEIGHBOR_H__

#include <list>
#include <queue>
#include <functional>

#include <inc/BookAttendGrade.h>
#include <inc/BookAttendGradeNode.h>

namespace pel216 {

	namespace week8 {

		/**
		 * Implementa��o do m�todo Nearest Neighbor.<br />
		 *
		 * @author arrebola
		 */
		class NearestNeighbor {

		private:
			std::list<BookAttendGrade> samples;
			std::vector<BookAttendGrade> neighborsList;

			/**
			 * Determina a dist�ncia de uma amostra para o alvo utilizando a dist�ncia euclidiana.<br />
			 *
			 * @param sample
			 *				o @link{BookAttendGrade} que representa a amostra que se quer classificar
			 * @param target
			 *				o @link{BookAttendGrade} que representa a amostra que se quer estimar
			 *
			 * @return o <code>double</code> que representa 
			 */
			double evaluate(BookAttendGrade sample, BookAttendGrade target) const {
				return std::sqrt(std::pow(sample.getBooks() - target.getBooks(), 2.0f) +  std::pow(sample.getAttendance() - target.getAttendance(), 2.0f));
			};

			/**
			 * Organiza as amostras de acordo com sua proximidade do alvo.<br />
			 * Aqui, as amostras originais s�o interpretados uma a uma, calculando a dist�ncia euclidiana para o alvo.
			 * Durante essa interpreta��o, as amostras originais s�o organizadas em uma fila com prioridade.
			 *
			 * @param target
			 *				o @link{BookAttendGrade} que representa a amostra que se quer estimar
			 * @oaram neighbors
			 *				o <code>size_t</code> que representa a quantidade de vizinhos a considerar (K)
			 */
			void buildNearestNeighborList(BookAttendGrade target, size_t neighbors = 1) {
				
				this->neighborsList.clear();

				// a fila com prioridade customizada para a classe BookAttendGradeNode
				std::priority_queue<
					BookAttendGradeNode, 
					std::vector<BookAttendGradeNode>,
					std::less<std::vector<BookAttendGradeNode>::value_type>>  queue;

				// determina a proximidade de cada uma das amostras para o alvo
				for (std::list<BookAttendGrade>::iterator iterator = this->samples.begin(); 
						iterator != this->samples.end(); 
						++iterator) {
					queue.push(BookAttendGradeNode(*iterator, evaluate(*iterator, target)));
				}

				// remove da fila os N elementos com maior proximidade do alvo
				for (size_t idx = 0; idx < neighbors && !queue.empty(); idx++) {
					neighborsList.push_back(queue.top().getData());
					queue.pop();
				}

			};
			
		public:
			/**
			 * Construtor.
			 *
			 * @param samples 
			 *				o <code>std::list</code> de @link{BookAttendGrade} que representa a lista de dados
			 */
			NearestNeighbor(std::list<BookAttendGrade> samples) {
				this->samples = samples;
				this->neighborsList.clear();
			};

			/**
			 * Determina o valor da nota utilizando o K-NN e considerando os par�metros informados.
			 *
			 * @oaram target 
			 *				o @link{BookAttendGrade} que representa o alvo
			 * @oaram neighbors
			 *				o <code>size_t</code> que representa a quantidade de vizinhos a considerar (K)
			 *
			 * @return o <code>double</code> que representa a nota
			 */
			double evaluate(BookAttendGrade target, size_t neighbors = 1) {

				double result = 0.0f;

				buildNearestNeighborList(target, neighbors);

				size_t length = this->neighborsList.size();
				for (size_t idx = 0; idx < length; idx++) {
					result += this->neighborsList[idx].getGrade();
				}

				result /= (neighbors * 1.0f);

				return result;

			};


			/**
			 * Obt�m a lista de amostras mais pr�ximas ao alvo.<br />
			 *
			 * @return o <code>std::vector</code> de @link{BookAttendGrade} que representa a lista de amostras mais pr�ximas ao alvo
			 */
			std::vector<BookAttendGrade> getNeighborList() {
				return this->neighborsList;
			};

		}; /* class NearestNeighbor */

	} /* namespace week8 */

} /* namespace pel216 */

#endif /* __NEAREST_NEIGHBOR_H__ */
