#pragma once

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <chrono>
#include <random>

#include <inc\Utils.h>

namespace pel208 {

	namespace commons {

		/**
		 * Classe utilitária para geração de números aleatórios.<br />
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
			 * Obtém um número inteiro aleatório.<br />
			 *
			 * @param min
			 *					o <code>int</code> que representa o valor mínimo (padrão INT_MIN)
			 * @param max
			 *					o <code>int</code> que representa o valor máximo (padrão INT_MAX)
			 *
			 * @return o <code>int</code> que representa o número inteiro aleatório
			 */
			PUBLIC static int nextInt(IN int min = INT_MIN, IN int max = INT_MAX) {

				std::random_device generator;
				std::uniform_real_distribution<int> distribution(min, max);

				return distribution(generator);

			};

			/**
			 * Obtém um número inteiro sem sinal aleatório.<br />
			 *
			 * @param min
			 *					o <code>int</code> que representa o valor mínimo (padrão 0)
			 * @param max
			 *					o <code>int</code> que representa o valor máximo(padrão UINT_MAX)
			 *
			 * @return o <code>size_t</code> que representa o número inteiro aleatório
			 */
			PUBLIC static size_t nextUint(IN int min = 0, IN int max = UINT_MAX - 1) {

				std::random_device generator;
				std::uniform_int_distribution<size_t> distribution(min, max);

				return distribution(generator);

			};

			/**
			 * Obtém um número double aleatório.<br />
			 *
			 * @param min
			 *					o <code>double</code> que representa o valor mínimo (padrão DBL_MIN)
			 * @param max
			 *					o <code>double</code> que representa o valor máximo (padrão DBL_MAX)
			 *
			 * @return o <code>double</code> que representa o número inteiro aleatório
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
