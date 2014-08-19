#pragma once

#ifndef _CONE_H_
#define _CONE_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/ThreeDShape.h>
#include <inc/ex/UnsupportedOperationException.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um cone.
		 *
		 * @author arrebola
		 */
		class Cone : public ThreeDShape {
		private:
			double diameter;
			double heigth;

		public:
			/**
			 * Construtor.
			 *
			 * @param diameter
			 * 				o <code>double</code> que representa o diametro
			 * 	@param height
			 * 				o <code>double</code> que representa a altura
			 */
			Cone(double diameter, double height) {

				if (diameter <= 0.0f || heigth <= 0.0f) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->diameter = diameter;
				this->heigth = height;

			};

			/**
			 * Destrutor.
			 */
			~Cone() {
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
				return this->heigth;
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
				double radius = this->diameter / 2.0f;
				return ((pel216::commons::pi * std::pow(radius, 2)) +
						(pel216::commons::pi * radius * std::sqrt(std::pow(radius, 2) + std::pow(this->heigth, 2))));
			};

			/**
			 * @see pel216::week2::ThreeDShape::getVolume()
			 */
			double getVolume() const {
				return ((pel216::commons::pi * std::pow((this->diameter / 2.0f), 2) * this->heigth) / 3.0f);
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
						"Cone com diametro ~%.2f, altura ~%.2f, volume ~%.2f e area da superficie ~%.2f",
						this->diameter,
						this->heigth,
						this->getVolume(),
						this->getSurfaceArea());
				return stringRep;

			};

		}; /* class Cone */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _CONE_H_ */
