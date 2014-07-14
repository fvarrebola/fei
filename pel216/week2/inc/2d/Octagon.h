#pragma once

#ifndef _OCTAGON_H_
#define _OCTAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um octagono.
		 *
		 * @author arrebola
		 */
		class Octagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Octagon(double sideLength) : Polygon(OCTAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Octagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* 2*cot(PI/8)*(t^2) */
				return (2 * pel216::week2::cot(pel216::week2::pi / 8) * std::pow(this->getSideLength(), 2));
			};

		}; /* class Octagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _OCTAGON_H_ */
