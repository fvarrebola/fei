#pragma once

#ifndef _THREE_D_SHAPE_H_
#define _THREE_D_SHAPE_H_

#include <inc/Utils.h>
#include <inc/Shape.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa uma forma tridimensional.
		 *
		 * @author arrebola
		 */
		class ThreeDShape : public Shape {
		private:
		public:
			/**
			 * Construtor.
			 */
			ThreeDShape() : Shape() {
			};

			/**
			 * Destrutor.
			 */
			virtual ~ThreeDShape() {
			};

			/**
			 * Obtem a area da face da forma.
			 *
			 * @return <code>double</code> que representa a area da face da forma
			 */
			virtual double getFaceArea() const = 0;

			/**
			 * Obtem a area da superficie da forma.
			 *
			 * @return <code>double</code> que representa a area da superficie da forma
			 */
			virtual double getSurfaceArea() const = 0;

			/**
			 * Obtem o volume da forma.
			 *
			 * @return <code>double</code> que representa o volume da forma
			 */
			virtual double getVolume() const = 0;

		}; /* class ThreeDShape */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _THREE_D_SHAPE_H_ */
