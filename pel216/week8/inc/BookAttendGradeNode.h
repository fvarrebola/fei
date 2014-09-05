#pragma once

#ifndef __BOOK_ATTEND_GRADE_NODE_H__
#define __BOOK_ATTEND_GRADE_NODE_H__

#include <inc/BookAttendGrade.h>

namespace pel216 {

	namespace week8 {

		/**
		 * Representação do dado.<br />
		 *
		 * @author arrebola
		 */
		class BookAttendGradeNode {

		private:
			double distance;
			BookAttendGrade data;

		public:
			/**
			 * Construtor.
			 *
			 * @oaram data 
			 *				o @link{BookAttendGrade} que representa a amostra
			 * @oaram distance 
			 *				o <code>double</code> que representa a distância da amostra para um alvo
			 */
			BookAttendGradeNode(BookAttendGrade data, double distance = 0.0f) {
				this->data = data;
				this->distance = distance;
			};

			/**
			 * Retorna a amostra.
			 * 
			 * @return o @link{BookAttendGrade} que representa a amostra
			 */
			BookAttendGrade getData() {
				return this->data;
			};

			/**
			 * Retorna a distância da amostra para um alvo.
			 * 
			 * @return o <code>double</code> que representa a distância da amostra para um alvo
			 */
			double getDistance() const {
				return this->distance;
			};

			/**
			 * Sobrecarga do operador '>' (maior que), comparando as distâncias entre a amostra atual e uma amostra qualquer.<br />
			 *
			 * @oaram other 
			 *				o @link{BookAttendGrade} que representa a amostra informada
			 *
			 * @return <code>true</code> caso a amostra informada seja <quote>maior</quote> que a amostra atual
			 */
			bool operator> (const BookAttendGradeNode &other) const {
				return getDistance() < other.getDistance();
			};

			/**
			 * Sobrecarga do operador '<' (menor que), comparando as distâncias entre a amostra atual e uma amostra qualquer.<br />
			 *
			 * @oaram other 
			 *				o @link{BookAttendGrade} que representa a amostra informada
			 *
			 * @return <code>true</code> caso a amostra informada seja <quote>menor</quote> que a amostra atual
			 */
			bool operator< (const BookAttendGradeNode &other) const {
				return getDistance() > other.getDistance();
			};

		}; /* class BookAttendGradeNode */

	} /* namespace week8 */

} /* namespace pel216 */

#endif /* __BOOK_ATTEND_GRADE_NODE_H__ */
