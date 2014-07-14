#pragma once

#ifndef _ICOSAEDRON_SHAPE_H_
#define _ICOSAEDRON_SHAPE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/Polyhedral.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um isocaedro.
		 *
		 * @author arrebola
		 */
		class Icosaedron : public Polyhedral {
		public:
			/**
			 * Construtor.
			 */
			Icosaedron(float sideLength) : Polyhedral(ICOSAEDRON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Icosaedron() {
			};

			/**
			 * @see pel216::week2::Polyhedral::getFaceArea()
			 */
			double getFaceArea() const {
				return ((1.0f / 4.0f) * std::sqrt(3.0f) * std::pow(this->getSideLength(), 2.0f));
			};

			/**
			 * @see pel216::week2::Polyhedral::getVolume()
			 */
			double getVolume() const {
				return ((5.0f / 12.0f) * ((3.0f + std::sqrt(5.0f)) * std::pow(this->getSideLength(), 3.0f)));
			};

		}; /* class Icosaedron */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _ICOSAEDRON_SHAPE_H_ */
