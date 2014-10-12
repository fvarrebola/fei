#pragma once

#ifndef __HALD_H__
#define __HALD_H__

#include <string>
#include <sstream>

namespace pel208 {

	namespace week2 {

		/**
		 * Representação do dado.<br />
		 *
		 * @author arrebola
		 */
		class Hald {

		private:
			double x1;
			double x2;
			double x3;
			double x4;
			double y;

		public:
			/**
			 * Construtor.
			 *
			 * @param x1
			 *				o <code>double</code> que representa o x1
			 * @param x2
			 *				o <code>double</code> que representa o x2
			 * @param x3
			 *				o <code>double</code> que representa o x3
			 * @param x4
			 *				o <code>double</code> que representa o x4
			 * @param y
			 *				o <code>double</code> que representa o y
			 */
			Hald(double x1 = 0.0f, double x2 = 0.0f, double x3 = 0.0f, double x4 = 0.0f, double y = 0.0f) {
				this->x1 = x1;
				this->x2 = x2;
				this->x3 = x3;
				this->x4 = x4;
				this->y = y;
			};

			/**
			 * Retorna o x1.
			 * 
			 * @return o <code>double</code> que representa o x1
			 */
			double getX1() {
				return this->x1;
			};
			
			/**
			 * Retorna o x2.
			 * 
			 * @return o <code>double</code> que representa o x2
			 */
			double getX2() {
				return this->x2;
			};

			/**
			 * Retorna o x3.
			 * 
			 * @return o <code>double</code> que representa o x3
			 */
			double getX3() {
				return this->x3;
			};

			/**
			 * Retorna o x4.
			 * 
			 * @return o <code>double</code> que representa o x4
			 */
			double getX4() {
				return this->x4;
			};

			/**
			 * Retorna o y.
			 * 
			 * @return o <code>double</code> que representa o y
			 */
			double getY() {
				return this->y;
			};

			/**
			 * Retorna uma representação do dado.<br />
			 *
			 * @return o <code>std::string</code> que representa o dado
			 */
			std::string toString() {

				char pszMsg[50] = {0x00};
				sprintf_s(pszMsg, 50, "(%9.6f, %9.6f, %9.6f, %9.6f, %9.6f)", this->x1, this->x2, this->x3, this->x4, this->y);
				return std::string(pszMsg);

			};

		}; /* class Hald */

	} /* namespace week2 */

} /* namespace pel208 */

#endif /* __HALD_H__ */
