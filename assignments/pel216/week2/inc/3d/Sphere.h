#pragma once

#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/ThreeDShape.h>
#include <inc/ex/UnsupportedOperationException.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um esfera.
		 *
		 * @author arrebola
		 */
		class Sphere : public ThreeDShape {
		private:
			double diameter;

		public:
			/**
			 * Construtor.
			 *
			 * @param diameter
			 * 				o <code>double</code> que representa o diametro
			 */
			Sphere(double diameter) {

				if (diameter <= 0.0f) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->diameter = diameter;

			};

			/**
			 * Destrutor.
			 */
			~Sphere() {
			};

			/**
			 * Obtem o diametro do cilindro.
			 *
			 * @return o <code>double</code> que representa o diametro
			 */
			double getDiameter() const {
				return this->diameter;
			};

			/**
			 * Obtem a altura do cilindro.
			 *
			 * o <code>double</code> que representa o altura
			 */
			double getHeight() const {
				throw new pel216::commons::UnsupportedOperationException();
			};

			/**
			 * @see pel216::week2::ThreeDShape::getFaceArea()
			 */
			double getFaceArea() const {
				throw new pel216::commons::UnsupportedOperationException();
			};

			/**
			 * @see pel216::week2::ThreeDShape::getSurfaceArea()
			 */
			double getSurfaceArea() const {
				return (4 * pel216::commons::pi * std::pow((this->diameter / 2.0f), 2));
			};

			/**
			 * @see pel216::week2::ThreeDShape::getVolume()
			 */
			double getVolume() const {
				return ((4.0f * pel216::commons::pi * std::pow((this->diameter / 2.0f), 3)) / 3.0f);
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
						"Esfera com diametro ~%.2f, volume ~%.2f e area da superficie ~%.2f",
						this->diameter,
						this->getVolume(),
						this->getSurfaceArea());
				return stringRep;

			};

		}; /* class Sphere */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _SPHERE_H_ */
