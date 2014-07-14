#pragma once

#ifndef _DECAGON_H_
#define _DECAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um decagono.
		 *
		 * @author arrebola
		 */
		class Decagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Decagon(double sideLength) : Polygon(DECAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Decagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* (5/2)*(t^2)*cot(PI/10) */
				return (5 / 2) * pow(this->getSideLength(), 2) * (pel216::week2::cot(pel216::week2::pi / 10));
			};

		}; /* class Decagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _DECAGON_H_ */
