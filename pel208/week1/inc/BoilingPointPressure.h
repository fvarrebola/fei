#pragma once

#ifndef __BOILING_POINT_PRESSURE_H__
#define __BOILING_POINT_PRESSURE_H__

#include <string>
#include <sstream>

namespace pel208 {

	namespace week1 {

		/**
		 * Representação do dado.<br />
		 *
		 * @author arrebola
		 */
		class BoiolingPointPressure {

		private:
			double boilingPoint;
			double pressure;

		public:
			/**
			 * Construtor.
			 *
			 * @param boilingPoint 
			 *				o <code>double</code> que representa a quantidade de livros
			 * @param pressure 
			 *				o <code>double</code> que representa a frequencia
			 */
			BoiolingPointPressure(double boilingPoint = 0.0f, double pressure = 0.0f) {
				this->boilingPoint = boilingPoint;
				this->pressure = pressure;
			};

			/**
			 * Retorna o ponto de ebulição.
			 * 
			 * @return o <code>double</code> que representa o ponto de ebulição
			 */
			double getBoilingPoint() {
				return this->boilingPoint;
			};
			
			/**
			 * Retorna a pressão.
			 * 
			 * @return o <code>double</code> que representa a pressão
			 */
			double getPressure() {
				return this->pressure;
			};

			/**
			 * Retorna uma representação do dado.<br />
			 *
			 * @return o <code>std::string</code> que representa o dado
			 */
			std::string toString() {

				char pszMsg[20] = {0x00};
				sprintf_s(pszMsg, 20, "(%9.6f, %9.6f)", this->boilingPoint, this->pressure);
				return std::string(pszMsg);

			};

		}; /* class BoiolingPointPressure */

	} /* namespace week1 */

} /* namespace pel208 */

#endif /* __BOILING_POINT_PRESSURE_H__ */
