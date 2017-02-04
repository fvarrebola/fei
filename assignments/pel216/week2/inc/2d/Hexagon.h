#pragma once

#ifndef _HEXAGON_H_
#define _HEXAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um hexagono.
		 *
		 * @author arrebola
		 */
		class Hexagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Hexagon(double sideLength) : Polygon(HEXAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Hexagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* (3sqrt(3)/2) * (t^2)*/
				return (((3 * std::sqrt(3)) / 2) * std::pow(this->getSideLength(), 2));
			};

		}; /* class Hexagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _HEXAGON_H_ */
