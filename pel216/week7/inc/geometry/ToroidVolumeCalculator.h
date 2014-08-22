#pragma once

#ifndef __TOROID_VOLUME_CALCULATOR_H__
#define __TOROID_VOLUME_CALCULATOR_H__

#include <chrono>
#include <random>

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

#include <inc/Function.h>
#include <inc/functions/ToroidFunction.h>
#include <inc/NumericalBounds.h>

namespace pel216 {

	namespace week7 {

		static const double DEFAULT_TOROID_ENCLOSING_CUBE_VOLUME = 3.0f * 7.0f * 2.0f;
		static const NumericalBounds DEFAULT_TOROID_BOUNDS = NumericalBounds(1.0f, 4.0f, -3.0f, 4.0f, -1.0f, 1.0f);

		typedef struct _tagCenterOfMass {
			double x;
			double y;
			double z;
		} CENTER_OF_MASS, PCENTER_OF_MASS;

		/**
		 * Classe que representa o cálculo do volume de um toróide.<br />
		 *
		 * @author arrebola
		 */
		class ToroidVolumeCalculator {

		private:
			size_t hitCount;				/* qtde de pontos válidos */
			double hitCountAsPercentage;	/* % de pontos válidos */
			double mass;					/* a massa do toróide */
			double error;					/* a taxa de erro */
			CENTER_OF_MASS centerOfMass;	/* centro de massa */

			/**
			 * Determina se os pontos informados definem um toróide concordante com restrições pré-definidas.<br />
			 * Aqui, a restrição é z^2 + (sqrt(x^2 + y^2) - 2)^2 <= 1.<br />
			 * Uma forma alterantiva de expressar a equação acima é: (-6 * sqrt(x^2 + y^2)) + x^2 + y^2 + z^2 + 9 <= 1.<br />
			 *
			 * @param x
			 *				o <code>double</code> que representa o x
 			 * @param y
			 *				o <code>double</code> que representa o y
			 * @param z
			 *				o <code>double</code> que representa o z
			 */

		public:
			/**
			 * Construtor padrão.<br />
			 */
			ToroidVolumeCalculator() {
				this->hitCount = 0;
				this->hitCountAsPercentage = 0.0f;
			};

			/**
			 * Calcula o volume de um toróide.
			 *
			 * @param function
			 *				o @link{Function} que representa a função a ser integrada
			 * @param enclosingCubeVolume
			 *				o <code>double</code> que representa o volume do cubo que abriga o toróide
			 * @param toroidBounds
			 *				o @link{NumericalBounds} que representa os limites numéricos do toróide (para que a escolha aleatória de amostras seja mais eficaz)
			 * @param intervals 
			 *				o <code>size_t</code> que indica a quantidade de intervalos
			 */
			void evaluate(
					pel216::week6::Function *function, 
					double enclosingCubeVolume = DEFAULT_TOROID_ENCLOSING_CUBE_VOLUME, 
					NumericalBounds bounds = DEFAULT_TOROID_BOUNDS, 
					size_t samples = -1) {

				if (pel216::commons::Utils::isInvalidHandle(function)) {
					throw new IllegalParameterException();
				}

				this->hitCount = 0;
				this->hitCountAsPercentage = 0.0f;
				this->mass = 0.0f;
				this->error = 0.0f;

				// cria o gerador aleatório
				std::random_device generator;
				std::uniform_real_distribution<double> x_dist(bounds.lowerX(), bounds.upperX());
				std::uniform_real_distribution<double> y_dist(bounds.lowerY(), bounds.upperY());
				std::uniform_real_distribution<double> z_dist(bounds.lowerZ(), bounds.upperZ());
								
				double xSum = 0.0f;
				double ySum = 0.0f;
				double zSum = 0.0f;

				for (size_t idx = 0; idx < samples; idx++) {
					
					register double x = x_dist(generator);
					register double y = y_dist(generator);
					register double z = z_dist(generator);

					if (function->evaluate(x, y, z) > 0.0f) {
						continue;
					}

					xSum += x;
					ySum += y;
					zSum += z;
					this->hitCount++;

				}

				double hits_div_samples = this->hitCount / (samples * 1.0f);
				
				this->hitCountAsPercentage = hits_div_samples * 100.0f;
				
				// a massa do toróide é dada por:
				// (hitCount * enclosingCubeVolume) / samples
				this->mass = (this->hitCount * enclosingCubeVolume) / (samples * 1.0f);
				
				// a taxa de erro é dada por:
				// (enclosingCubeVolume * sqrt((hitCount / samples - (hitCount / samples)^2) / samples))
				this->error = enclosingCubeVolume * (std::sqrt(hits_div_samples - std::pow(hits_div_samples, 2.0f)) / samples);

				// calcula o centro de massa
				centerOfMass.x = (xSum / this->hitCount) ;
				centerOfMass.y = (ySum / this->hitCount);
				centerOfMass.z = (zSum / this->hitCount);

			};

			/**
			 * Obtém a quantidade de pontos válidos.
			 *
			 * @return o <code>size_t</code> que representa a quantidade de pontos válidos
			 */
			size_t getHitCount() {
				return this->hitCount;
			};

			/**
			 * Obtém a quantidade % de pontos válidos.
			 *
			 * @return o <code>double</code> que representa a quantidade % de pontos válidos
			 */
			double getHitCountAsPercentage() {
				return this->hitCountAsPercentage;
			};

			/**
			 * Obtém a massa do toróide.
			 *
			 * @return o <code>double</code> que representa a massa do toróide
			 */
			double getMass() {
				return this->mass;
			};
			
			/**
			 * Obtém o erro da aproximação.
			 *
			 * @return o <code>double</code> que representa o erro da aproximação
			 */
			double getError() {
				return this->error;
			};
			
			/**
			 * Obtém o centro de massa do toróide.
			 *
			 * @return o @link{CENTER_OF_MASS} que representa o centro de massa do toróide
			 */
			CENTER_OF_MASS getCenterOfMass() {
				return this->centerOfMass;
			};

		}; /* class ToroidVolumeCalculator */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __TOROID_VOLUME_CALCULATOR_H__ */
