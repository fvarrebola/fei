#pragma once

#ifndef _PYRAMID_H_
#define _PYRAMID_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/3d/ThreeDShape.h>
#include <inc/ex/UnsupportedOperationException.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa uma piramide.
		 *
		 * @author arrebola
		 */
		class Pyramid : public ThreeDShape {
		private:
			double base;
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
			Pyramid(double base, double height) {

				if (base <= 0.0f || heigth <= 0.0f) {
					throw new pel216::week2::IllegalParameterException();
				}

				this->base = base;
				this->heigth = height;

			};

			/**
			 * Destrutor.
			 */
			~Pyramid() {
			};

			/**
			 * Obtem a base da piramide.
			 *
			 * @return o <code>double</code> que representa a base
			 */
			double getBase() const {
				return this->base;
			};

			/**
			 * Obtem a altura da piramide.
			 *
			 * o <code>double</code> que representa a altura
			 */
			double getHeight() const {
				return this->heigth;
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
				return (this->base * (this->base + std::sqrt(std::pow(this->base, 2) + 4 * (std::pow(this->heigth, 2)))));
			};

			/**
			 * @see pel216::week2::ThreeDShape::getVolume()
			 */
			double getVolume() const {
				return ((std::pow(this->base, 2) * this->heigth) / 3.0f);
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
						"Piramide com base ~%.2f, altura ~%.2f, volume ~%.2f e area da superficie ~%.2f",
						this->base,
						this->heigth,
						this->getVolume(),
						this->getSurfaceArea());
				return stringRep;

			};

		}; /* class Pyramid */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _PYRAMID_H_ */
