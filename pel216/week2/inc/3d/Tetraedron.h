#pragma once

#ifndef _TETRAEDRON_SHAPE_H_
#define _TETRAEDRON_SHAPE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/Polyhedral.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um tetraedro.
		 *
		 * @author arrebola
		 */
		class Tetraedron : public Polyhedral {
		public:
			/**
			 * Construtor.
			 */
			Tetraedron(float sideLength) : Polyhedral(TETRAHEDRON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Tetraedron() {
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
				return (std::pow(this->getSideLength(), 3.0f) / (6.0f * std::sqrt(2.0f)));
			};

		}; /* class Tetraedron */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _TETRAEDRON_SHAPE_H_ */
