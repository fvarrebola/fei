#pragma once

#ifndef __NEURON_H__
#define __NEURON_H__

#include <vector>

#include <inc\Utils.h>
#include <inc\Matrix.h>

using namespace pel203::commons;

#define MIN_W_VALUE									+0.0f
#define MAX_W_VALUE									+0.1f

namespace pel203 {

	namespace neural {

		/**
		 * Implementação de um neurônio.<br />
		 *
		 * @author arrebola
		 */
		class Neuron {
		private:
			size_t inputs;
			Matrix *weights;

			double netValue;
			double neuronOutput;
			double delta;

		public:
			/**
			 * Construtor.<br />
			 */
			Neuron() {
			};

			/**
			 * Construtor.<br />
			 *
			 * @param inputs
			 *			o <code>size_t</code> que representa a quantidade de entradas que um neurônio possui
			 * @param minWeight
			 *			o <code>double</code> que representa o valor mínimo dos pesos
			 * @param maxWeight
			 *			o <code>double</code> que representa o valor máximo dos pesos
			 */
			Neuron(IN size_t inputs, IN double minWeight = MIN_W_VALUE, IN double maxWeight = MAX_W_VALUE) {

				if (minWeight < MIN_W_VALUE || maxWeight > MAX_W_VALUE) {
					throw new IllegalParameterException();
				}

				this->inputs = inputs;

				this->weights = new Matrix(this->inputs + 1, 1);
				if (this->inputs > 0) {
					this->weights->randomFill(minWeight,  maxWeight);
				}

				this->delta = 0.0f;
				this->netValue = 0.0f;
				this->neuronOutput = 0.0f;

			};

			/**
			 * Destrutor.<br />
			 */
			~Neuron() {
				if (Utils::isValidHandle(this->weights)) {
					delete weights;
				}
			};

			/**
			 * Obtém a quantidade de entradas.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de entradas
			 */
			PUBLIC size_t getInputs() {
				return this->inputs;
			};
				
			/**
			 * Obtém o peso de uma entrada.<br />
			 *
			 * @param idx
			 *				o <code>size_t</code> que representa o índice da entrada
			 *
			 * @return o <code>double</code> que representa o peso
			 */
			PUBLIC double getWeight(IN size_t idx) {

				if (idx > this->weights->getRows()) {
					throw IllegalParameterException();
				}

				return weights->data()[idx][0];

			};

			/**
			 * Atualiza o peso de uma entrada.<br />
			 *
			 * @param idx
			 *				o <code>size_t</code> que representa o índice da entrada
			 * @param value
			 *				o <code>double</code> que representa o valor da atualização
			 */
			PUBLIC void updateWeight(IN size_t idx, IN double value) {

				if (idx > this->weights->getRows()) {
					throw IllegalParameterException();
				}

				weights->data()[idx][0] += value;

			};

			/**
			 * Obtém o valor de ativação do neurônio.<br />
			 *
			 * @return o <code>double</code> que representa o valor de ativação do neurônio
			 */
			PUBLIC double getNetValue() {
				return this->netValue;
			};

			/**
			 * Configura o valor de ativação do neurônio.<br />
			 *
			 * @param value
			 *				o <code>double</code> que representa o valor de ativação do neurônio
			 */
			PUBLIC void setNetValue(IN double netValue) {
				this->netValue = netValue;
			};

			/**
			 * Obtém o delta do neurônio.<br />
			 *
			 * @return o <code>double</code> que representa o delta do neurônio
			 */
			PUBLIC double getDelta() {
				return this->delta;
			};

			/**
			 * Configura o delta do neurônio.<br />
			 *
			 * @param error
			 *				o <code>double</code> que representa o delta do neurônio
			 */
			PUBLIC void setDelta(IN double delta) {
				this->delta = delta;
			};

			/**
			 * Obtém o valor do neurônio.<br />
			 *
			 * @return o <code>double</code> que representa o valor do neurônio
			 */
			PUBLIC double getNeuronOutput() {
				return this->neuronOutput;
			};

			/**
			 * Configura o valor do neurônio.<br />
			 *
			 * @param output
			 *				o <code>double</code> que representa o valor do neurônio
			 */
			PUBLIC void setNeuronOutput(IN double neuronOutput) {
				this->neuronOutput = neuronOutput;
			};

			/**
			 * Obtém a representação de um neurônio.<br />
			 *
			 * @return o <code>std:string</code> da representação de um neurônio
			 */
			PUBLIC std::string toString() {
				char pszMsg[MAX_PATH] = {0x00};
				sprintf_s(pszMsg, MAX_PATH, ">> [N] A: %+9.6f, S: %+9.6f, D: %+9.6f", 
					this->netValue, this->neuronOutput, this->delta);
				return std::string(pszMsg);
			};
			
		}; /* class Neuron */

	} /* namespace neural */
	
} /* namespace pel203 */

#endif // __NEURON_H__