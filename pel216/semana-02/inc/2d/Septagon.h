#pragma once

#ifndef _SEPTAGON_H_
#define _SEPTAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um septagono.
		 *
		 * @author arrebola
		 */
		class Septagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Septagon(double sideLength) : Polygon(SEPTAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Septagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* (7/4)*(t^2)*cot(PI/7) */
				return ((7 / 4) * std::pow(this->getSideLength(), 2) * pel216::week2::cot(pel216::week2::pi / 7));
			};

		}; /* class Septagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _SEPTAGON_H_ */
