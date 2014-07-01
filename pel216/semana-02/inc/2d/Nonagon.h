#pragma once

#ifndef _NONAGON_H_
#define _NONAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um nonagono.
		 *
		 * @author arrebola
		 */
		class Nonagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Nonagon(double sideLength) : Polygon(NONAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Nonagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* (9/4)*(t^2)*cot(PI/9) */
				return (9 / 4) * std::pow(this->getSideLength(), 2) * (pel216::week2::cot(pel216::week2::pi / 9));
			};

		}; /* class Nonagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _NONAGON_H_ */
