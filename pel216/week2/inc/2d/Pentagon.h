#pragma once

#ifndef _PENTAGON_H_
#define _PENTAGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/Polygon.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um pentagono.
		 *
		 * @author arrebola
		 */
		class Pentagon : public Polygon {
		private:

		public:
			/**
			 * Construtor.
			 *
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Pentagon(double sideLength) : Polygon(PENTAGON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Pentagon() {
			};

			/**
			 * @see pel216::week2::Polygon::getArea()
			 */
			double getArea() const {
				/* (5*(t^2) * tan(54)) / 4 */
				return ((5 * std::pow(this->getSideLength(), 2) * std::tan(pel216::week2::cotUsingDegrees(54))) / 4);
			};

		}; /* class Pentagon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _PENTAGON_H_ */
