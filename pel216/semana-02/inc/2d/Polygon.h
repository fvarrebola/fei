#pragma once

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <cmath>

#include <inc/Utils.h>
#include <inc/2d/TwoDShape.h>

namespace pel216 {

	namespace week2 {

		enum PoligonType {
			TRIANGLE = 3,
			QUADRILATERAL = 4,
			PENTAGON = 5,
			HEXAGON = 6,
			SEPTAGON = 7,
			OCTAGON = 8,
			NONAGON = 9,
			DECAGON = 10,
		};

		/**
		 * Classe que representa um poligono regular (com todos os lados iguais).
		 *
		 * @author arrebola
		 */
		class Polygon : public TwoDShape {
		private:
			PoligonType type;
			double sideLength;

		public:
			/**
			 * Construtor.
			 *
			 * @param type
			 * 				o {@link PoligonType} que determina o tipo do poligono
			 * @param sideLength
			 * 				o <code>double</code> que representa o tamanho do lado
			 */
			Polygon(PoligonType type, double sideLength) {

				if (type < TRIANGLE || sideLength <= 0.0f) {
					throw new pel216::week2::IllegalParameterException();
				}

				this->type = type;
				this->sideLength = sideLength;

			}

			/**
			 * Destrutor.
			 */
			~Polygon() {
			};

			/**
			 * Retorna o tipo do poligono.
			 *
			 * @return o <code>PoligonType</code> que representa o tipo do poligono
			 */
			PoligonType getType() {
				return this->type;
			};

			/**
			 * Retorna o tamanho do lado do poligono.
			 *
			 * @return o <code>double</code> que representa o tamanho do lado
			 */
			double getSideLength() const {
				return this->sideLength;
			}

			/**
			 * Retorna a area do poligono.
			 *
			 * @return o <code>double</code> que representa a area do poligono
			 */
			virtual double getArea() const  = 0;

			/**
			 * Retorna o perimetro do poligono.
			 *
			 * @return o <code>double</code> que representa o perimetro do poligono
			 */
			double getPerimeter() const {
				return (this->type * this->sideLength);
			};

			/**
			 * Retorna o valor individual em graus de um angulo interno do poligono.
			 *
			 * @return o <code>double</code> que representa o angulo interno do poligono
			 */
			double getInteriorAngleInDegrees() const {
				return ((this->type - 2) * 180 / this->type);
			}

			/**
			 * Retorna a soma em graus de angulos internos do poligono.
			 *
			 * @return o <code>double</code> que representa soma de angulos internos do poligono
			 */
			double getInteriorAngleSumInDegrees() const {
				return ((this->type - 2) * 180);
			}

			/**
			 * @see pel216::week2::Shape::toString()
			 */
			std::string toString() const {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				sprintf_s(
						(char*)stringRep.c_str(),
						MAX_PATH * 2,
						"Poligono com %d lados de tamanho ~%.2f, area ~%.2f, perimetro ~%.2f, angulo %.2f graus e soma de angulos %.2f graus",
						this->type,
						this->getSideLength(),
						this->getArea(),
						this->getPerimeter(),
						this->getInteriorAngleInDegrees(),
						this->getInteriorAngleSumInDegrees());
				return stringRep;

			}

		}; /* class Polygon */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _POLYGON_H_ */
