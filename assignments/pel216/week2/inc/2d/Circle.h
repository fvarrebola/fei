#pragma once

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/TwoDShape.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um circulo.
		 *
		 * @author arrebola
		 */
		class Circle : public TwoDShape {
		private:
			double diameter;

		public:
			/**
			 * Construtor.
			 */
			Circle(double diameter) {
				if (diameter > 0) {
					this->diameter = diameter;
				}
			};

			/**
			 * Destrutor.
			 */
			virtual ~Circle() {
			};

			/**
			 * Retorna a area do circulo.
			 *
			 * @return <code>double</code> que representa a area do circulo
			 */
			double getArea() const {
				return ((pel216::commons::pi * std::pow(this->diameter, 2)) / 4);
			};

			/**
			 * Retorna o perimetro do circulo.
			 *
			 * @return <code>double</code> que representa o perimetro do circulo
			 */
			double getPerimeter() const {
				return (pel216::commons::pi * this->diameter);
			};

			/**
			 * @see pel216::week2::Shape::toString()
			 */
			std::string toString() const {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				sprintf_s(
						(char*)stringRep.c_str(),
						MAX_PATH * 2,
						"Circulo com diametro %f, area %f e perimetro %f",
						this->diameter,
						getArea(),
						getPerimeter());
				return stringRep;

			}

		}; /* class Circle */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _CIRCLE_H_ */
