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
		 * Classe que representa o c�lculo do volume de um tor�ide.<br />
		 *
		 * @author arrebola
		 */
		class ToroidVolumeCalculator {

		private:
			size_t hitCount;				/* qtde de pontos v�lidos */
			double hitCountAsPercentage;	/* % de pontos v�lidos */
			double mass;					/* a massa do tor�ide */
			double error;					/* a taxa de erro */
			CENTER_OF_MASS centerOfMass;	/* centro de massa */

			/**
			 * Determina se os pontos informados definem um tor�ide concordante com restri��es pr�-definidas.<br />
			 * Aqui, a restri��o � z^2 + (sqrt(x^2 + y^2) - 2)^2 <= 1.<br />
			 * Uma forma alterantiva de expressar a equa��o acima �: (-6 * sqrt(x^2 + y^2)) + x^2 + y^2 + z^2 + 9 <= 1.<br />
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
			 * Construtor padr�o.<br />
			 */
			ToroidVolumeCalculator() {
				this->hitCount = 0;
				this->hitCountAsPercentage = 0.0f;
			};

			/**
			 * Calcula o volume de um tor�ide.
			 *
			 * @param function
			 *				o @link{Function} que representa a fun��o a ser integrada
			 * @param enclosingCubeVolume
			 *				o <code>double</code> que representa o volume do cubo que abriga o tor�ide
			 * @param toroidBounds
			 *				o @link{NumericalBounds} que representa os limites num�ricos do tor�ide (para que a escolha aleat�ria de amostras seja mais eficaz)
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

				// cria o gerador aleat�rio
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
				
				// a massa do tor�ide � dada por:
				// (hitCount * enclosingCubeVolume) / samples
				this->mass = (this->hitCount * enclosingCubeVolume) / (samples * 1.0f);
				
				// a taxa de erro � dada por:
				// (enclosingCubeVolume * sqrt((hitCount / samples - (hitCount / samples)^2) / samples))
				this->error = enclosingCubeVolume * (std::sqrt(hits_div_samples - std::pow(hits_div_samples, 2.0f)) / samples);

				// calcula o centro de massa
				centerOfMass.x = (xSum / this->hitCount) ;
				centerOfMass.y = (ySum / this->hitCount);
				centerOfMass.z = (zSum / this->hitCount);

			};

			/**
			 * Obt�m a quantidade de pontos v�lidos.
			 *
			 * @return o <code>size_t</code> que representa a quantidade de pontos v�lidos
			 */
			size_t getHitCount() {
				return this->hitCount;
			};

			/**
			 * Obt�m a quantidade % de pontos v�lidos.
			 *
			 * @return o <code>double</code> que representa a quantidade % de pontos v�lidos
			 */
			double getHitCountAsPercentage() {
				return this->hitCountAsPercentage;
			};

			/**
			 * Obt�m a massa do tor�ide.
			 *
			 * @return o <code>double</code> que representa a massa do tor�ide
			 */
			double getMass() {
				return this->mass;
			};
			
			/**
			 * Obt�m o erro da aproxima��o.
			 *
			 * @return o <code>double</code> que representa o erro da aproxima��o
			 */
			double getError() {
				return this->error;
			};
			
			/**
			 * Obt�m o centro de massa do tor�ide.
			 *
			 * @return o @link{CENTER_OF_MASS} que representa o centro de massa do tor�ide
			 */
			CENTER_OF_MASS getCenterOfMass() {
				return this->centerOfMass;
			};

		}; /* class ToroidVolumeCalculator */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __TOROID_VOLUME_CALCULATOR_H__ */
