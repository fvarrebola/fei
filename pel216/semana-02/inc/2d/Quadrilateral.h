#pragma once

#ifndef _QUADRILATERAL_H_
#define _QUADRILATERAL_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um quadrilatero.
		 *
		 * @author arrebola
		 */
		class Quadrilateral : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Quadrilateral(double sideLength) : Polygon(QUADRILATERAL, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Quadrilateral() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				return (this->getSideLength() * 2);
			};

		}; /* class Quadrilateral */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _QUADRILATERAL_H_ */
