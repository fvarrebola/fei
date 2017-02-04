#pragma once

#ifndef _POLYHEDRAL_SHAPE_H_
#define _POLYHEDRAL_SHAPE_H_

#include <inc/Utils.h>
#include <inc/3d/ThreeDShape.h>

namespace pel216 {

	namespace week2 {

		enum PolyhedralType {
			TETRAHEDRON = 4,
			CUBE = 6,
			OCTAEDRON = 8,
			DODECAEDRON = 12,
			ICOSAEDRON = 20
		};

		static int ALLOWED_TYPES_COUNT = 5;
		static int ALLOWED_TYPES[] = {TETRAHEDRON, CUBE, OCTAEDRON, DODECAEDRON, ICOSAEDRON};

		/**
		 * Classe que representa um poliedro regular (com todos os lados iguais).
		 *
		 * @author arrebola
		 */
		class Polyhedral : public ThreeDShape {
		private:
			int faces;
			float sideLength;

		public:
			/**
			 * Construtor.
			 */
			Polyhedral(PolyhedralType faces, float sideLength) {

				bool isAllowedType = false;
				for (int idx = 0; (idx < ALLOWED_TYPES_COUNT && !isAllowedType); idx++) {
					if (faces == ALLOWED_TYPES[idx]) {
						isAllowedType = true;
					}
				}

				if (!isAllowedType || sideLength <= 0.0f) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->faces = faces;
				this->sideLength = sideLength;

			};

			/**
			 * Destrutor.
			 */
			virtual ~Polyhedral() {
			};

			/**
			 * Retorna a quantidade de faces do poliedro.
			 *
			 * @return o <code>int</code> que representa a quantidade de faces
			 */
			int getFaces() const {
				return this->faces;
			}

			/**
			 * Retorna o tamanho do lado do poliedro.
			 *
			 * @return o <code>double</code> que representa o tamanho do lado
			 */
			double getSideLength() const {
				return this->sideLength;
			}

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
			double getSurfaceArea() const {
				return (this->getFaces() * getFaceArea());
			}

			/**
			 * Obtem o volume da forma.
			 *
			 * @return <code>double</code> que representa o volume da forma
			 */
			virtual double getVolume() const = 0;

			/**
			 * @see pel216::week2::Shape::toString()
			 */
			std::string toString() const {

				std::string stringRep;
				stringRep.resize(MAX_PATH * 2);
				sprintf_s(
						(char*)stringRep.c_str(),
						MAX_PATH * 2,
						"Poliedro com %d faces de tamanho ~%.2f, area da face ~%.2f, area da superficie ~%.2f e volume ~%.2f",
						this->faces,
						this->sideLength,
						getFaceArea(),
						getSurfaceArea(),
						getVolume());
				return stringRep;

			}

		}; /* class Polyhedral */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _POLYHEDRAL_SHAPE_H_ */
