#pragma once

#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <cstring>
#include <cmath>

#include <inc/Utils.h>

namespace pel216 {

	namespace week2 {

		static const double pi = 3.141592654f;

		/**
		 * Transforma um angulo de graus para radianos.
		 *T
		 * @param angle
		 * 				o <code>float</code> o angulo em graus
		 *
		 * @return o <code>double</code> que representa o angulo em radianos
		 */
		inline double toRadians(float angle) {
			return ((pel216::week2::pi /180) * angle);
		};

		/**
		 * Retorna a co-tangente de um angulo em radianos.
		 *
		 * @param angle
		 * 				o <code>float</code> o angulo em randianos
		 *
		 * @return o <code>double</code> que representa a co-tangente do angulo
		 */
		static double cot(float angle) {
			return (std::cos(angle) / std::sin(angle));
		};

		/**
		 * Retorna a co-tangente de um angulo em graus.
		 *
		 * @param angle
		 * 				o <code>float</code> o angulo em graus
		 *
		 * @return o <code>double</code> que representa a co-tangente do angulo
		 */
		inline double cotUsingDegrees(float angle) {
			return cot(toRadians(angle));
		};

		/**
		 * Classe que representa uma forma abstrata.
		 *
		 * @author arrebola
		 */
		class Shape {
		private:

		public:
			/**
			 * Construtor.
			 */
			Shape();

			/**
			 * Destrutor.
			 */
			virtual ~Shape();

			/**
			 * Retorna a representacao da classe.
			 *
			 * @return o <code>std::string</code> que representa a classe
			 */
			virtual std::string toString() const = 0;

		}; /* class Shape */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* SHAPE_H_ */
