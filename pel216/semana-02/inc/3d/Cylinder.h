#pragma once

#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/ThreeDShape.h>
#include <inc/ex/UnsupportedOperationException.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um cilindro.
		 *
		 * @author arrebola
		 */
		class Cylinder : public ThreeDShape {
		private:
			double diameter;
			double height;

		public:
			/**
			 * Construtor.
			 *
			 * @param diameter
			 * 				o <code>double</code> que representa o diametro
			 * 	@param height
			 * 				o <code>double</code> que representa a altura
			 */
			Cylinder(double diameter, double height) {

				if (diameter <= 0.0f || height <= 0.0f) {
					throw new pel216::week2::IllegalParameterException();
				}

				this->diameter = diameter;
				this->height = height;

			};

			/**
			 * Destrutor.
			 */
			~Cylinder() {
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
				return this->height;
			};

			/**
			 * @see pel216::week2::ThreeDShape::getFaceArea()
			 */
			double getFaceArea() const {
				throw new UnsupportedOperationException();
			};

			/**
			 * @see pel216::week2::ThreeDShape::getSurfaceArea()
			 */
			double getSurfaceArea() const {
				return ((2 * pel216::week2::pi * std::pow((this->diameter / 2.0f), 2)) +
						(2 * pel216::week2::pi * (this->diameter / 2.f) * this->height));
			};

			/**
			 * @see pel216::week2::ThreeDShape::getVolume()
			 */
			double getVolume() const {
				return (pel216::week2::pi * std::pow((this->diameter / 2.0f), 2) * this->height);
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
						"Cilindro com diametro ~%.2f, altura ~%.2f, volume ~%.2f e area da superficie ~%.2f",
						this->diameter,
						this->height,
						this->getVolume(),
						this->getSurfaceArea());
				return stringRep;

			};

		}; /* class Cylinder */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _CYLINDER_H_ */
