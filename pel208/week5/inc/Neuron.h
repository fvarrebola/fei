#pragma once

#ifndef __NEURON_H__
#define __NEURON_H__

#include <vector>

#include <inc\Utils.h>
#include <inc\Matrix.h>

using namespace pel208::commons;

#define MIN_W_VALUE									+0.0f
#define MAX_W_VALUE									+0.1f

namespace pel208 {

	namespace week5 {

		/**
		 * Implementa��o de um neur�nio.<br />
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
			 *			o <code>size_t</code> que representa a quantidade de entradas que um neur�nio possui
			 * @param minWeight
			 *			o <code>double</code> que representa o valor m�nimo dos pesos
			 * @param maxWeight
			 *			o <code>double</code> que representa o valor m�ximo dos pesos
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
			 * Obt�m a quantidade de entradas.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de entradas
			 */
			PUBLIC size_t getInputs() {
				return this->inputs;
			};
				
			/**
			 * Obt�m o peso de uma entrada.<br />
			 *
			 * @param idx
			 *				o <code>size_t</code> que representa o �ndice da entrada
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
			 *				o <code>size_t</code> que representa o �ndice da entrada
			 * @param value
			 *				o <code>double</code> que representa o valor da atualiza��o
			 */
			PUBLIC void updateWeight(IN size_t idx, IN double value) {

				if (idx > this->weights->getRows()) {
					throw IllegalParameterException();
				}

				weights->data()[idx][0] += value;

			};

			/**
			 * Obt�m o valor de ativa��o do neur�nio.<br />
			 *
			 * @return o <code>double</code> que representa o valor de ativa��o do neur�nio
			 */
			PUBLIC double getNetValue() {
				return this->netValue;
			};

			/**
			 * Configura o valor de ativa��o do neur�nio.<br />
			 *
			 * @param value
			 *				o <code>double</code> que representa o valor de ativa��o do neur�nio
			 */
			PUBLIC void setNetValue(IN double netValue) {
				this->netValue = netValue;
			};

			/**
			 * Obt�m o delta do neur�nio.<br />
			 *
			 * @return o <code>double</code> que representa o delta do neur�nio
			 */
			PUBLIC double getDelta() {
				return this->delta;
			};

			/**
			 * Configura o delta do neur�nio.<br />
			 *
			 * @param error
			 *				o <code>double</code> que representa o delta do neur�nio
			 */
			PUBLIC void setDelta(IN double delta) {
				this->delta = delta;
			};

			/**
			 * Obt�m o valor do neur�nio.<br />
			 *
			 * @return o <code>double</code> que representa o valor do neur�nio
			 */
			PUBLIC double getNeuronOutput() {
				return this->neuronOutput;
			};

			/**
			 * Configura o valor do neur�nio.<br />
			 *
			 * @param output
			 *				o <code>double</code> que representa o valor do neur�nio
			 */
			PUBLIC void setNeuronOutput(IN double neuronOutput) {
				this->neuronOutput = neuronOutput;
			};

			/**
			 * Imprime o conte�do do neur�nio.
			 */
			PUBLIC std::string toString() {
				char pszMsg[MAX_PATH] = {0x00};
				sprintf_s(pszMsg, MAX_PATH, ">> [N] A: %+9.6f, S: %+9.6f, D: %+9.6f", 
					this->netValue, this->neuronOutput, this->delta);
				return std::string(pszMsg);
			};
			
		}; /* class Neuron */

	} /* namespace week5 */
	
} /* namespace pel208 */

#endif // __NEURON_H__