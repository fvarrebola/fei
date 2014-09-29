#pragma once

#ifndef __BOOK_ATTEND_GRADE_H__
#define __BOOK_ATTEND_GRADE_H__

#include <string>
#include <sstream>

namespace pel208 {

	namespace week1 {

		/**
		 * Representa��o do dado.<br />
		 *
		 * @author arrebola
		 */
		class BookAttendGrade {

		private:
			int books;
			int attendance;
			int grade;

		public:
			/**
			 * Construtor.
			 *
			 * @oaram books 
			 *				o <code>int</code> que representa a quantidade de livros
			 * @oaram attendance 
			 *				o <code>int</code> que representa a frequencia
			 * @oaram grade 
			 *				o <code>int</code> que representa a nota
			 */
			BookAttendGrade(int books = 0, int attendance = 0, int grade = 0) {
				this->books = books;
				this->attendance = attendance;
				this->grade = grade;
			};

			/**
			 * Retorna a quantidade de livros.
			 * 
			 * @return o <code>int</code> que representa a quantidade de livros
			 */
			int getBooks() {
				return this->books;
			};
			
			/**
			 * Retorna a frequencia.
			 * 
			 * @return o <code>int</code> que representa a frequencia
			 */
			int getAttendance() {
				return this->attendance;
			};

			/**
			 * Retorna a nota.
			 * 
			 * @return o <code>int</code> que representa a nota
			 */
			int getGrade() {
				return this->grade;
			};
			
			/**
			 * Retorna uma representa��o do dado.<br />
			 *
			 * @return o <code>std::string</code> que representa o dado
			 */

			std::string toString() {

				char pszMsg[13] = {0x00};
				sprintf_s(pszMsg, 13, "(%2d, %2d, %2d)", this->books, this->attendance, this->grade);
				return std::string(pszMsg);

			};

		}; /* class BookAttendGrade */

	} /* namespace week1 */

} /* namespace pel208 */

#endif /* __BOOK_ATTEND_GRADE_H__ */
