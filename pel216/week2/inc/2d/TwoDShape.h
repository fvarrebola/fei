#pragma once

#ifndef _TWO_D_SHAPE_H_
#define _TWO_D_SHAPE_H_

#include <inc/Utils.h>
#include <inc/Shape.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa uma forma bidimensional.
		 *
		 * @author arrebola
		 */
		class TwoDShape : public Shape {
		private:
		public:
			/**
			 * Construtor.
			 */
			TwoDShape() : Shape() {
			};

			/**
			 * Destrutor.
			 */
			virtual ~TwoDShape() {
			};

			/**
			 * Obtem a area da forma.
			 *
			 * @return <code>double</code> que representa a area da forma
			 */
			virtual double getArea() const = 0;

			/**
			 * Obtem o perimetro da forma.
			 *
			 * @return <code>double</code> que representa o perimetro da forma
			 */
			virtual double getPerimeter() const = 0;

		}; /* class TwoDShape */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _TWO_D_SHAPE_H_ */
