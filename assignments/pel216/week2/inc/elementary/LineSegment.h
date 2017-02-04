#pragma once

#ifndef _LINESEGMENT_H_
#define _LINESEGMENT_H_

#include <string>

#include <inc/Utils.h>
#include <inc/Shape.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um segmento de reta.
		 *
		 * @author arrebola
		 */
		class LineSegment : public Shape {
		private:
			Point *begin;
			Point *end;

		public:
			/**
			 * Construtor.
			 *
			 * @param begin
			 * 				o <code>Point*</code> que representa o ponto de inicio do segmento
			 * @param end
			 * 				o <code>Point*</code> que representa o ponto de fim do segmento
			 */
			LineSegment(Point *begin, Point *end) : begin(begin), end(end) {
			};

			/**
			 * Destrutor.
			 */
			~LineSegment() {
			};

			/**
			 * Retorna o ponto de inicio do segmento.
			 *
			 * @return o <code>Point*</code> que representa o ponto de inicio
			 */
			Point *getBegin() {
				return this->begin;
			}

			/**
			 * Retorna o ponto de termino do segmento.
			 *
			 * @return o <code>Point*</code> que representa o ponto de termino
			 */
			Point *getEnd() {
				return this->end;
			}

			/**
			 * @see pel216::week2::Shape::toString()
			 */
			std::string toString() const {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				sprintf_s((char*)stringRep.c_str(),
						MAX_PATH * 2,
						"Segmento de reta comeca no '%s' e termina no '%s'",
						(pel216::commons::Utils::isValidHandle(this->begin) ? this->begin->toString().c_str() : UNKNOWN),
						(pel216::commons::Utils::isValidHandle(this->end) ? this->end->toString().c_str() : UNKNOWN));
				return stringRep;

			}

		}; /* class LineSegment */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _LINESEGMENT_H_ */
