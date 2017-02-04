#pragma once

#ifndef __LAYER_H__
#define __LAYER_H__

#include <vector>

#include <inc\Neuron.h>

using namespace pel208::week5;

namespace pel208 {

	namespace week5 {

		/**
		 * Implementação de uma camada da rede neural.<br />
		 *
		 * @author arrebola
		 */
		class Layer {
		private:
			size_t _neurons;
			std::vector<Neuron*> *_neuronsVector;

		public:
			/**
			 * Construtor.<br />
			 */
			Layer() {
			};

			/**
			 * Construtor.<br />
			 *
			 * @param neurons
			 *			o <code>size_t</code> que representa a quantidade de neurônios da camada
			 * @param inputsPerNeuron
			 *			o <code>size_t</code> que representa a quantidade de entradas que um neurônio possui
			 */
			Layer(IN size_t neurons, IN size_t inputsPerNeuron) {

				this->_neurons = neurons;
				this->_neuronsVector = new std::vector<Neuron*>(neurons);

				for (size_t idx = 0; idx < neurons; idx++) {
					(*this->_neuronsVector)[idx] = new Neuron(inputsPerNeuron);
				}

			};

			/**
			 * Destrutor.<br />
			 */
			~Layer() {

				for (size_t idx = 0; idx < this->_neuronsVector->size(); idx++) {
					delete (*this->_neuronsVector)[idx];
				}

				delete this->_neuronsVector;

			};

			/**
			 * Obtém a quantidade de neurônios da camada.<br />
			 * 
			 * @return o <code>size_t</code> que representa a quantidade de neurônios da camada
			 */
			PUBLIC size_t neurons() {
				return this->_neurons;
			};

						/**
			 * Obtém um neurônio.<br />
			 * 
			 * @param idx
			 *				o <code>size_t</code> que representa o índice do neurônio
			 *
			 * @return o <code>size_t</code> que representa a quantidade de neurônios da camada
			 */
			PUBLIC Neuron *getNeuron(IN size_t idx) {

				if (idx > this->_neuronsVector->size()) {
					throw IllegalParameterException();
				}

				return (*this->_neuronsVector)[idx];

			};

			PUBLIC void dumpToFile() {

				register size_t neuronsCount = this->neurons();
				for (size_t neuronIdx = 0; neuronIdx < neuronsCount; neuronIdx++) {
					register Neuron *neuron = this->getNeuron(neuronIdx);
					Logger::logToFile("[%05d] %s\n", neuronIdx + 1, neuron->toString().c_str());
					register size_t inputs = neuron->getInputs();
					for (size_t weightIdx = 0; weightIdx < inputs; weightIdx++) {
						Logger::logToFile("       W__%d_%d = %9.6f\n", neuronIdx + 1, weightIdx, neuron->getWeight(weightIdx));
					}
				}

			};

		}; /* class Layer */

	} /* namespace week5 */

} /* namespace pel208 */

#endif // __LAYER_H__
