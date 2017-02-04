#pragma once

#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <map>
#include <string>

#include <inc\Utils.h>
#include <inc\Layer.h>
#include <inc\Neuron.h>

#define TRAINING_CYCLES								1000

#define INPUT_LAYER_NEURONS_COUNT					256
#define OUTPUT_LAYER_NEURONS_COUNT					10

#define TRAINING_SET_COLUMN_COUNT					INPUT_LAYER_NEURONS_COUNT + 1

#define SIGMOID_THRESHOLD							1
#define LEARNING_RATE								0.0005

using namespace pel208::week5;

namespace pel208 {

	namespace week5 {

		/**
		 * Implementa��o de uma rede neural com back propagation para reconhecimento de d�gitos.<br />
		 * Baseado nas implementa��es de:<br />
		 * <ul>
		 * <li><a href="http://www.codeproject.com/Articles/16650/Neural-Network-for-Recognition-of-Handwritten-Digi">Neural Network for Recognition of Handwritten Digits</a></li>
		 * <li><a href="https://github.com/bcuccioli/neural-ocr">Neural OCR</a></li>
		 * </ul>
		 *
		 * @author arrebola
		 */
		class NeuralNetwork {
		private:
			size_t inputs;
			size_t outputs;
			size_t hiddenLayers;
			std::vector<int> neuronsPerLayer;
			double learningRate;
			double bias;

			size_t trainingSuccesses;
			size_t trainingFailures;
			size_t overallTrainingSuccesses;
			size_t overallTrainingFailures;

			size_t overallTestingSuccesses;
			size_t overallTestingFailures;

			std::vector<Layer*> *layers;

			/**
			 * Determina se o resultado obtido � o esperado.<br />
			 *
			 * @param output
			 *				o Matrix que representa a sa�da da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 * @param debug
			 *				indica se devem ser impressas mensagens com os valores
			 *
			 * @return o <code>true</code> caso o feed forward tenha sido bem sucedido; do contr�rio <code>false</code>
			 */
			PRIVATE static bool succeeded(IN Matrix *output, IN size_t expectedIdx, IN bool debug = false) {
				
				double max = DBL_MIN;
				size_t maxRowIdx = 0;
				size_t maxColIdx = 0;
				if (!output->max(&max, &maxRowIdx, &maxColIdx)) {
					return false;
				}

				if (debug) {
					output->dumpToFile();
					Logger::logToFile("Valor obtido: %d (%f), Valor esperado: %d\n", maxRowIdx, max, expectedIdx);
				}

				return (maxRowIdx == expectedIdx);

			};

			/**
			 * Calcula o valor da fun��o <i>sigmoid</i> definido por 1 / (1 + e^-x).<br />
			 *
			 * @param x
			 *				o <code>double</code> que representa o valor de x
			 *
			 * @return o <code>double</code> que valor da fun��o <i>sigmoid</i>
			 */
			PRIVATE static double sigmoid(IN double x) {
				return (1.0f / (1.0f + std::exp(-x)));
				//return std::tanh(x);
			};

			/**
			 * Calcula o valor da derivada da fun��o <i>sigmoid</i> definido por e^x / (e^x + 1)^2.<br />
			 *
			 * @param x
			 *				o <code>double</code> que representa o valor de x
			 *
			 * @return o <code>double</code> que valor da derivada fun��o <i>sigmoid</i>
			 */
			PRIVATE static double sigmoidPrime(IN double x) {
				double e = std::exp(x);
				return e / std::pow((1.0f + e), 2.0f);
				//return 1 - std::pow(x, 2.0f);
			};

			/**
			 * Calcula a sa�da da rede.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param rowIdx
			 *				o <code>size_t</code> que representa o �ndice da amostra de treino
			 * @param output
			 *				o Matrix que representa a sa�da da rede
			 * @param trace
			 *				indica se os neuronios devem ser impressos
			 *
			 * @return o <code>true</code> caso o feed forward tenha sido bem sucedido; do contr�rio <code>false</code>
			 */
			PRIVATE bool feedForward(
					IN Matrix *input, 
					IN size_t rowIdx, 
					IN OUT Matrix **output, 
					IN bool trace = false) {

				if (trace) {
					Logger::logToFile("\n");
					Logger::logToFile(">>>> feedForward()\n");
				}

				// alimenta a camada de entrada 
				Layer *inputLayer = layers->at(0);
				for (size_t idx = 0; idx < this->inputs; idx++) {
					Neuron *neuron = inputLayer->getNeuron(idx);
					neuron->setNeuronOutput(input->data()[rowIdx][idx + 1]);
				}

				// alimenta as camadas escondidas
				for (size_t layerIdx = 1; layerIdx < hiddenLayers + 2; layerIdx++) {
					
					register Layer *layer = layers->at(layerIdx);
					register Layer *previousLayer = layers->at(layerIdx - 1);
					
					if (trace) {
						Logger::logToFile("Imprimindo neuronios da camada #%d...\n", layerIdx);
					}

					register size_t neuronsCount = layer->neurons();
					for (size_t neuronIdx = 0; neuronIdx < neuronsCount; neuronIdx++) {
						
						register size_t prevNeuronsCount = previousLayer->neurons();
						register double sum = this->bias;
						register Neuron *neuron = layer->getNeuron(neuronIdx);
						for (size_t prevIdx = 0; prevIdx < prevNeuronsCount; prevIdx++) {
							sum += neuron->getWeight(prevIdx) * previousLayer->getNeuron(prevIdx)->getNeuronOutput();
						}
						
						neuron->setNetValue(sum);
						neuron->setNeuronOutput(sigmoid(sum));

						if (trace) {
							Logger::logToFile("[%05d] %s\n", neuronIdx, neuron->toString().c_str());
							size_t inputs = neuron->getInputs();
							/*
							for (size_t weightIdx = 0; weightIdx < inputs; weightIdx++) {
								Logger::logToFile("       W__%d_%d = %9.6f\n", neuronIdx, weightIdx, neuron->getWeight(weightIdx));
							}
							*/
						}
					
					}
				
				}

				(*output) = new Matrix(this->outputs, 1);

				// alimenta a matriz de sa�da
				Layer* lastLayer = layers->at(hiddenLayers + 1);
				for (size_t idx = 0; idx < this->outputs; idx++) {
					(*output)->data()[idx][0] = lastLayer->getNeuron(idx)->getNeuronOutput();
				}

				if (trace) {
					Logger::logToFile("<<<< feedForward()\n");
					Logger::logToFile("\n");
				}

				return true;

			};

			/**
			 * Realiza o back propagation.<br />
			 *
			 * @param output
			 *				o Matrix que representa a sa�da da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 * @param trace
			 *				indica se os neuronios devem ser impressos
			 *
			 * @return o <code>true</code> caso o back propagation tenha sido bem sucedido; do contr�rio <code>false</code>
			 */
			PRIVATE bool backPropagate(
					IN Matrix *output, 
					IN size_t expectedIdx, 
					OUT double *quadraticError, 
					IN bool trace = false) {

				if (trace) {
					Logger::logToFile("\n");
					Logger::logToFile(">> backPropagate()\n");
				}

				// obt�m o resultado esperado
				if (succeeded(output, expectedIdx, trace)) {
					this->trainingSuccesses++;
					this->overallTrainingSuccesses++;
				} else {
					this->trainingFailures++;
					this->overallTrainingFailures++;
				}
				/*
				Matrix *expected = output->clone();
				expected->data()[expectedIdx][0] = +1.0f;
				*/
				if (trace) {
					Logger::logToFile("Analisando a camada de saida...\n");
				}

				// obt�m a camada de sa�da
				Layer *outputLayer = (*layers)[this->hiddenLayers + 1];
				
				*quadraticError = 0;

				// calcula o delta de cada neur�nio da camada de sa�da
				for (size_t idx = 0; idx < this->outputs; idx++) {
					
					Neuron *neuron = outputLayer->getNeuron(idx);

					double error = -output->data()[idx][0];
					if (idx == expectedIdx) {
						error += 1.0f;
					}

					neuron->setDelta(sigmoidPrime(neuron->getNetValue()) * error);
					
					if (trace) {
						Logger::logToFile("[%05d] %s E: %+9.6f\n", idx, neuron->toString().c_str(), error);
					}
				
					*quadraticError += std::pow(error, 2.0f);
					
				}

				*quadraticError *= 0.5f;

				// atualiza os pesos das camadas anteriores
				// iniciando na �ltima camada escondida...
				for (size_t layerIdx = this->hiddenLayers; layerIdx != 0; layerIdx--) {
					
					if (trace) {
						Logger::logToFile("Analisando a camada escondida %d...\n", layerIdx);
					}
				
					Layer *layer = (*layers)[layerIdx];
					register size_t layerNeuronsCount = layer->neurons();

					Layer *nextLayer = (*layers)[layerIdx + 1];
					register size_t nextLayerNeuronsCount = nextLayer->neurons();

					// para todos os neur�nios da camada atual...
					for (size_t neuronIdx = 0; neuronIdx < layerNeuronsCount; neuronIdx++) {

						// obtenha os deltas somando (pesos * deltas) de todos os neur�nios da pr�xima camada
						register double sum = 0;
						Neuron *neuron = layer->getNeuron(neuronIdx);

						for (size_t nextLayerNeuronIdx = 0; nextLayerNeuronIdx < nextLayerNeuronsCount; nextLayerNeuronIdx++) {
							register Neuron *nextLayerNeuron = nextLayer->getNeuron(nextLayerNeuronIdx);
							sum += nextLayerNeuron->getWeight(neuronIdx) * nextLayerNeuron->getDelta();
						}
						neuron->setDelta(sigmoidPrime(neuron->getNetValue()) * sum);

						if (trace) {
							Logger::logToFile("[%05d] %s\n", neuronIdx, neuron->toString().c_str());
						}

						// agora, atualize os pesos da pr�xima camada usando a taxa de aprendizado
						for (size_t nextLayerNeuronIdx = 0; nextLayerNeuronIdx < nextLayerNeuronsCount; nextLayerNeuronIdx++) {
							
							register Neuron *nextLayerNeuron = nextLayer->getNeuron(nextLayerNeuronIdx);
							register double weight = this->learningRate * sigmoid(neuron->getNetValue()) * nextLayerNeuron->getDelta();
							nextLayerNeuron->updateWeight(neuronIdx,  weight);

							if (trace) {
								Logger::logToFile("       W__%d_%d = %9.6f\n", 
									neuronIdx, nextLayerNeuronIdx, nextLayerNeuron->getWeight(neuronIdx));
							}

						}

					}

				}
				
				//delete expected;

				if (trace) {
					Logger::logToFile("<<<< backPropagate()\n");
					Logger::logToFile("\n");
				}

				return true;

			};

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param hiddenLayers
			 *				o <code>size_t</code> que representa a quantidade de camadas escondidas
			 * @param neuronsPerLayer
			 *				o <code>std::vector</code> que representa a quantidade de neur�nios por camada
			 * @param learningRate
			 *				a taxa de aprendizado
			 * @param bias
			 *				o <code>double</code> que representa o bias
			 */
			NeuralNetwork(
					IN size_t hiddenLayers, 
					IN std::vector<int> neuronsPerLayer,
					IN double learningRate = LEARNING_RATE,
					IN double bias = 1.0f) {

				this->inputs = INPUT_LAYER_NEURONS_COUNT;
				this->outputs = OUTPUT_LAYER_NEURONS_COUNT;
				this->hiddenLayers = hiddenLayers;
				this->neuronsPerLayer = neuronsPerLayer;

				this->layers = new std::vector<Layer*>(hiddenLayers + 2);
				this->layers->at(0) = new Layer(inputs, 0);
				this->layers->at(1) = new Layer(neuronsPerLayer[0], inputs);
				for (size_t idx = 2; idx < layers->size() - 1; idx++) {
					(*layers)[idx] = new Layer(neuronsPerLayer[idx - 1], neuronsPerLayer[idx - 2]);
				}
				this->layers->at(hiddenLayers + 1) = new Layer(outputs, neuronsPerLayer[hiddenLayers - 1]);

				this->learningRate = learningRate;

				this->bias = bias;

				this->trainingSuccesses = 0;
				this->trainingFailures = 0;
				
				this->overallTrainingSuccesses = 0;
				this->overallTrainingFailures = 0;

				this->overallTestingSuccesses = 0;
				this->overallTestingFailures = 0;

			};

			/**
			* Destrutor.<br />
			*/
			~NeuralNetwork() {
			};

			/**
			 * Treina a rede neural com base no conjunto de amostras de entrada.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param debug
			 *				indica se a rede deve ser impressa ao fim de cada ciclo
			 * @param trace
			 *				indica se os neuronios devem ser impressos
			 *
			 * @return o <code>true</code> caso o treinamento tenha sido bem sucedido; do contr�rio <code>false</code>
			 */
			PUBLIC bool train(IN Matrix *input, IN size_t cycles = TRAINING_CYCLES, IN bool debug = false, IN bool trace = false) {

				if (Utils::isInvalidHandle(input)) {
					throw new IllegalParameterException();
				}

				size_t columns = input->getColumns();
				if (columns < TRAINING_SET_COLUMN_COUNT) {
					throw new IllegalParameterException();
				}

				size_t rows = input->getRows();

				Logger::log("Realizando treino. Aguarde...\n");
				for (size_t cycleIdx = 0; cycleIdx < cycles; cycleIdx++) {

					register double mse = 0.0f;
					
					for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					
						register size_t expected = (size_t)input->data()[rowIdx][0];

						Matrix *output = NULL;
						if (!feedForward(input, rowIdx, &output, trace)) {
							continue;
						}
					
						register double quadraticError = 0.0f;	
						backPropagate(output, expected, &quadraticError, trace);

						mse += quadraticError;

						delete output;

					}

					register double div_factor = (rows * 1.0f);
					Logger::log(">> CICLO #%06d: MSE %13.9f (+%013.9f%% -%013.9f%%) <<\n", 
							cycleIdx + 1,  
							mse / div_factor, 
							(this->trainingSuccesses / div_factor) * 100.0f,  
							(this->trainingFailures  / div_factor) * 100.0f);

					if (debug) {
						for (size_t idx = 1; idx < this->hiddenLayers + 1; idx++) {
							register Layer *layer = this->layers->at(idx);
							layer->dumpToFile();
						}
					}

					this->trainingSuccesses = 0;
					this->trainingFailures = 0;

				}

				double cycles_times_rows = (cycles * rows * 1.0f);
				Logger::log("\n");
				Logger::log(">> TOTAL:                            +%013.9f%% -%013.9f%%\n", 
						(this->overallTrainingSuccesses / cycles_times_rows) * 100.0f, 
						(this->overallTrainingFailures  / cycles_times_rows) * 100.0f);

				return true;

			};

			/**
			 * Avalia a rede contra uma amostra de teste.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param debug
			 *				indica se as matrizes devem ser impressas
			 *
			 * @return o <code>true</code> caso a avalia��o tenha sido bem sucedida; do contr�rio <code>false</code>
			 */
			PUBLIC bool test(IN Matrix *input, IN bool debug = false) {

				if (Utils::isInvalidHandle(input)) {
					throw new IllegalParameterException();
				}

				size_t columns = input->getColumns();
				if (columns < TRAINING_SET_COLUMN_COUNT) {
					throw new IllegalParameterException();
				}

				Logger::log("Realizando teste. Aguarde............... ");
				size_t rows = input->getRows();
				for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					
					Matrix *output = NULL;
					
					if (feedForward(input, rowIdx, &output, debug)) {
						register size_t expectedIdx = (size_t)input->data()[rowIdx][0];
						if (succeeded(output, expectedIdx)) {
							this->overallTestingSuccesses++;
						} else {
							this->overallTestingFailures++;
						}
						delete output;
					}


				}

				Logger::logWithoutTimestamp("[ OK ]\n");

				double div_factor = (rows * 1.0f);
				Logger::log("\n");
				Logger::log(">> TOTAL:                            +%013.9f%% -%013.9f%%\n", 
						(this->overallTestingSuccesses / div_factor) * 100.0f, 
						(this->overallTestingFailures  / div_factor) * 100.0f);

				return true;

			};

		}; /* class NeuralNetwork */

	} /* namespace week5 */

} /* namespace pel208 */

#endif /* __NEURAL_NETWORK_H__ */
