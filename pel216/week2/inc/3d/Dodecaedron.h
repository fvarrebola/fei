#pragma once

#ifndef _DODECAEDRON_SHAPE_H_
#define _DODECAEDRON_SHAPE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/Polyhedral.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um dodecaedro.
		 *
		 * @author arrebola
		 */
		class Dodecaedron : public Polyhedral {
		public:
			/**
			 * Construtor.
			 */
			Dodecaedron(float sideLength) : Polyhedral(DODECAEDRON, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Dodecaedron() {
			};

			/**
			 * @see pel216::week2::Polyhedral::getFaceArea()
			 */
			double getFaceArea() const {
				return ((3.0f / 12.0f) * std::sqrt(25.0f + (10.0f * std::sqrt(5.0f))) * std::pow(this->getSideLength(), 2.0f));
			};

			/**
			 * @see pel216::week2::Polyhedral::getVolume()
			 */
			double getVolume() const {
				return (((15.0f + (7.0f * std::sqrt(5))) * std::pow(this->getSideLength(), 3.0f)) / 4.0f);
			};

		}; /* class Dodecaedron */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _DODECAEDRON_SHAPE_H_ */
