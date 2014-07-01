#pragma once

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um triangulo.
		 *
		 * @author arrebola
		 */
		class Triangle : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Triangle(double sideLength) : Polygon(TRIANGLE, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Triangle() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* sqrt(3)/4) * (t^2) */
				return std::sqrt(3) / 4 * pow(this->getSideLength(), 2);
			};

		}; /* class Triangle */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _TRIANGLE_H_ */
