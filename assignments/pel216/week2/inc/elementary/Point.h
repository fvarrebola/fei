#pragma once

#ifndef _POINT_H_
#define _POINT_H_

#include <inc/Utils.h>
#include <inc/Shape.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe que representa um ponto.
		 *
		 * @author arrebola
		 */
		class Point : public Shape {
		private:
			int x;
			int y;
			int z;

		public:
			/**
			 * Construtor.
			 */
			Point() : x(0), y(0), z(0) {
			};

			/**
			 * Construtor.
			 *
			 * @param x
			 * 				o <code>int</code> que representa a coordenada x
			 * @param y
			 * 				o <code>int</code> que representa a coordenada y
			 */
			Point(int x, int y) : x(x), y(y), z(0) {
			};

			/**
			 * Construtor.
			 *
			 * @param x
			 * 				o <code>int</code> que representa a coordenada x
			 * @param y
			 * 				o <code>int</code> que representa a coordenada y
			 * @param z
			 * 				o <code>int</code> que representa a coordenada z
			 */
			Point(int x, int y, int z) : x(x), y(y), z(z) {
			};

			/**
			 * Destrutor.
			 */
			~Point() {
			};

			/**
			 * Retorna a coordenada y.
			 *
			 * @return o <code>int</code> que representa a coordenada x
			 */
			int getX() {
				return this->x;
			};

			/**
			 * Retorna a coordenada y.
			 *
			 * @return o <code>int</code> que representa a coordenada y
			 */
			int getY() {
				return this->y;
			};

			/**
			 * Retorna a coordenada z.
			 *
			 * @return o <code>int</code> que representa a coordenada z
			 */
			int getZ() {
				return this->z;
			};

			/**
			 * Configura a coordenada x.
			 *
			 * @param x
			 * 				o <code>int</code> que representa a coordenada x
			 */
			void setX(int x) {
				this->x = x;
			}

			/**
			 * Configura a coordenada y.
			 *
			 * @param y
			 * 				o <code>int</code> que representa a coordenada y
			 */
			void setY(int y) {
				this->y = y;
			}

			/**
			 * Configura a coordenada z.
			 *
			 * @param z
			 * 				o <code>int</code> que representa a coordenada z
			 */
			void setZ(int z) {
				this->z = z;
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
						"Ponto com coordenadas (x, y, z) = (%d, %d, %d)",
						this->x,
						this->y,
						this->z);
				return stringRep;

			}

		}; /* class Point */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* _POINT_H_ */
