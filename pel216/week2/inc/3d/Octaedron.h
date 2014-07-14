#pragma once

#ifndef _OCTAEDRON_SHAPE_H_
#define _OCTAEDRON_SHAPE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/Polyhedral.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um octaedro.
		 *
		 * @author arrebola
		 */
		class Octaedron : public Polyhedral {
		public:
			/**
			 * Construtor.
			 */
			Octaedron(float sideLength) : Polyhedral(OCTAEDRON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Octaedron() {
			};

			/**
			 * @see pel216::week2::Polyhedral::getFaceArea()
			 */
			double getFaceArea() const {
				return ((std::sqrt(3.0f) * std::pow(this->getSideLength(), 2.0f)) / 4.0f);
			};

			/**
			 * @see pel216::week2::Polyhedral::getVolume()
			 */
			double getVolume() const {
				return ((std::sqrt(2.0f) * std::pow(this->getSideLength(), 3.0f)) / 3.0f);
			};

		}; /* class Octaedron */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _OCTAEDRON_SHAPE_H_ */
