#pragma once

#ifndef _CUBE_SHAPE_H_
#define _CUBE_SHAPE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/Polyhedral.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um cube.
		 *
		 * @author arrebola
		 */
		class Cube : public Polyhedral {
		public:
			/**
			 * Construtor.
			 */
			Cube(float sideLength) : Polyhedral(CUBE, sideLength) {
			};

			/**
			 * Destrutor.
			 */
			~Cube() {
			};

			/**
			 * @see pel216::week2::Polyhedral::getFaceArea()
			 */
			double getFaceArea() const {
				return (std::pow(this->getSideLength(), 2.0f));
			};

			/**
			 * @see pel216::week2::Polyhedral::getVolume()
			 */
			double getVolume() const {
				return (std::pow(this->getSideLength(), 3.0f));
			}

		}; /* class Cube */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _CUBE_SHAPE_H_ */
