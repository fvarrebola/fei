#pragma once

#ifndef _LINE_H_
#define _LINE_H_

#include <string>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa uma reta.
		 *
		 * @author arrebola
		 */
		class Line : public Shape {
		private:
			float gradient;
			float yIntersect;

		public:
			/**
			 * Construtor.
			 */
			Line(float gradient, float yCoordinate) : gradient(gradient), yIntersect(yCoordinate) {
			};

			/**
			 * Construtor.
			 *
			 * @param a
			 * 				o <code>Point*</code> que representa um ponto <quote>a</quote> na reta
			 * @param b
			 * 				o <code>Point*</code> que representa um ponto <quote>b</quote> na reta
			 *
			 * @throws {@link IllegalParameterException} caso os pontos sejam invalidos ou
			 * 			se a operacao (a.getX() - b.getY()) resultar em 0
			 */
			Line(Point *a, Point *b) {

				if (pel216::commons::Utils::isInvalidHandle(a) ||
						pel216::commons::Utils::isInvalidHandle(b)) {
					throw new pel216::commons::IllegalParameterException();
				}

				float dividend = (float)(a->getY() - b->getY());
				float divisor = (float)(a->getX() - b->getX());

				if (divisor == 0) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->gradient = dividend / divisor;
				this->yIntersect = ((float)b->getY() - (float)b->getX() * this->gradient);

			};

			/**
			 * Destrutor.
			 *
			 */
			~Line() {
			};

			/**
			 * Retorna o gradiente da reta.
			 *
			 * @return o <code>float</code> que representa o gradiente da reta
			 */
			float getGradient() {
				return this->gradient;
			};

			/**
			 * Retorna o ponto de intersecao reta com o eixo y.
			 *
			 * @return o <code>float</code> que o ponto de intersecao reta com o eixo y
			 */
			float getYIntersect() {
				return this->yIntersect;
			};

			/**
			 * Determina se um ponto pertence a reta.
			 *
			 * @param a
			 * 				o <code>Point&</code> que representa um ponto
			 *
			 * @return <code>true</code> se o ponto pertence a reta; do contrario <code>false</code>
			 *
			 * @throws {@link IllegalParameterException} se o ponto for invalido
			 */
			bool belongs(Point *point) {

				if (pel216::commons::Utils::isInvalidHandle(point)) {
					throw new pel216::commons::IllegalParameterException();
				}

				return ((float)point->getY() == (this->gradient * (float) point->getX()) + this->yIntersect);

			};

			/**
			 * @see pel216::week2::Shape::toString()
			 */
			std::string toString() const {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				sprintf_s(
						(char*)stringRep.c_str(),
						MAX_PATH * 2,
						"Reta definida por y = %fx + %f",
						this->gradient,
						this->yIntersect);
				return stringRep;

			}

		}; /* class Line */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _LINE_H_ */
