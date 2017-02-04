#pragma once

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <chrono>
#include <random>

#include <inc\Utils.h>

namespace pel208 {

	namespace commons {

		/**
		 * Classe utilit�ria para gera��o de n�meros aleat�rios.<br />
		 *
		 * @author arrebola
		 */
		class Random {

		private:

		public:
			/**
			 * Construtor.
			 */
			Random() {
			};

			/**
			 * Destrutor.
			 */
			~Random() {
			};

			/**
			 * Obt�m um n�mero inteiro aleat�rio.<br />
			 *
			 * @param min
			 *					o <code>int</code> que representa o valor m�nimo (padr�o INT_MIN)
			 * @param max
			 *					o <code>int</code> que representa o valor m�ximo (padr�o INT_MAX)
			 *
			 * @return o <code>int</code> que representa o n�mero inteiro aleat�rio
			 */
			PUBLIC static int nextInt(IN int min = INT_MIN, IN int max = INT_MAX) {

				std::random_device generator;
				std::uniform_real_distribution<int> distribution(min, max);

				return distribution(generator);

			};

			/**
			 * Obt�m um n�mero inteiro sem sinal aleat�rio.<br />
			 *
			 * @param min
			 *					o <code>int</code> que representa o valor m�nimo (padr�o 0)
			 * @param max
			 *					o <code>int</code> que representa o valor m�ximo(padr�o UINT_MAX)
			 *
			 * @return o <code>size_t</code> que representa o n�mero inteiro aleat�rio
			 */
			PUBLIC static size_t nextUint(IN int min = 0, IN int max = UINT_MAX - 1) {

				std::random_device generator;
				std::uniform_int_distribution<size_t> distribution(min, max);

				return distribution(generator);

			};

			/**
			 * Obt�m um n�mero double aleat�rio.<br />
			 *
			 * @param min
			 *					o <code>double</code> que representa o valor m�nimo (padr�o DBL_MIN)
			 * @param max
			 *					o <code>double</code> que representa o valor m�ximo (padr�o DBL_MAX)
			 *
			 * @return o <code>double</code> que representa o n�mero inteiro aleat�rio
			 */
			PUBLIC static double nextDouble(IN double min = DBL_MIN, IN double max = DBL_MAX) {

				std::random_device generator;
				std::uniform_real_distribution<double> distribution(min, max);

				return distribution(generator);

			};

		}; /* class Random */

	} /* namespace commons */

} /* namespace pel208 */

#endif /* __RANDOM_H__ */
