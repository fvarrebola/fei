#pragma once

#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include <string>

#include <inc\Utils.h>
#include <inc\Layer.h>
#include <inc\Neuron.h>

#define DEFAULT_TRAINING_CYCLES						1000
#define DEFAULT_STATS_GROUP_SIZE					500
#define DEFAULT_LEARNING_RATE						0.05
#define DEFAULT_BIAS								1.0f

using namespace pel203::neural;

namespace pel203 {

	namespace neural {

		/**
		 * Implementação de uma rede neural com back propagation para reconhecimento de dígitos.<br />
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
			 * Determina se o resultado obtido é o esperado.<br />
			 *
			 * @param output
			 *				o Matrix que representa a saída da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 * @param actualIdx
			 *				o <code>size_t</code> que representa o valor obtido
			 *
			 * @return o <code>true</code> caso o feed forward tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE static bool succeeded(IN Matrix *output, IN size_t expectedIdx, IN OUT size_t *actualIdx) {
				
				(*actualIdx) = 0;
				
				double max = DBL_MIN;
				size_t maxColIdx = 0;
				if (!output->max(&max, &(*actualIdx), &maxColIdx)) {
					return false;
				}

				return ((*actualIdx) == expectedIdx);

			};

			/**
			 * Determina se o resultado obtido é o esperado.<br />
			 *
			 * @param output
			 *				o Matrix que representa a saída da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 *
			 * @return o <code>true</code> caso o feed forward tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE static bool succeeded( IN Matrix *output, IN size_t expectedIdx) {
				size_t actualIdx = 0;
				return succeeded(output, expectedIdx, &actualIdx);
			};

			/**
			 * Calcula o valor da função <i>sigmoid</i> definido por 1 / (1 + e^-x).<br />
			 *
			 * @param x
			 *				o <code>double</code> que representa o valor de x
			 *
			 * @return o <code>double</code> que valor da função <i>sigmoid</i>
			 */
			PRIVATE static double sigmoid(IN double x) {
				return (1.0f / (1.0f + std::exp(-x)));
			};

			/**
			 * Calcula o valor da derivada da função <i>sigmoid</i> definido por e^x / (e^x + 1)^2.<br />
			 *
			 * @param x
			 *				o <code>double</code> que representa o valor de x
			 *
			 * @return o <code>double</code> que valor da derivada função <i>sigmoid</i>
			 */
			PRIVATE static double sigmoidPrime(IN double x) {
				double e = std::exp(x);
				return e / std::pow((1.0f + e), 2.0f);
			};

			/**
			 * Calcula a saída da rede.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param rowIdx
			 *				o <code>size_t</code> que representa o índice da amostra de treino
			 * @param output
			 *				o Matrix que representa a saída da rede
			 * @param logToFile
			 *				indica se as mensagens de progresso devem ser salvas em arquivo
			 *
			 * @return o <code>true</code> caso o feed forward tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE bool feedForward(
					IN Matrix *input, 
					IN size_t rowIdx, 
					IN OUT Matrix **output, 
					IN bool logToFile = false) {

				if (logToFile) {
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
					
					if (logToFile) {
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

						if (logToFile) {
							Logger::logToFile("[%05d] %s\n", neuronIdx, neuron->toString().c_str());
							size_t inputs = neuron->getInputs();
							for (size_t weightIdx = 0; weightIdx < inputs; weightIdx++) {
								Logger::logToFile("       W__%d_%d = %9.6f\n", neuronIdx, weightIdx, neuron->getWeight(weightIdx));
							}
						}
					
					}
				
				}

				(*output) = new Matrix(this->outputs, 1);

				// alimenta a matriz de saída
				Layer* lastLayer = layers->at(hiddenLayers + 1);
				for (size_t idx = 0; idx < this->outputs; idx++) {
					(*output)->data()[idx][0] = lastLayer->getNeuron(idx)->getNeuronOutput();
				}

				if (logToFile) {
					Logger::logToFile("<<<< feedForward()\n");
					Logger::logToFile("\n");
				}

				return true;

			};

			/**
			 * Realiza o back propagation.<br />
			 *
			 * @param output
			 *				o Matrix que representa a saída da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 * @param logToFile
			 *				indica se as mensagens de progresso devem ser salvas em arquivo
			 *
			 * @return o <code>true</code> caso o back propagation tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PRIVATE bool backPropagate(
					IN Matrix *output, 
					IN size_t expectedIdx, 
					OUT double *quadraticError, 
					IN bool logToFile = false) {

				if (logToFile) {
					Logger::logToFile("\n");
					Logger::logToFile(">> backPropagate()\n");
				}

				// obtém o resultado esperado
				if (succeeded(output, expectedIdx)) {
					this->trainingSuccesses++;
					this->overallTrainingSuccesses++;
				} else {
					this->trainingFailures++;
					this->overallTrainingFailures++;
				}

				if (logToFile) {
					Logger::logToFile("Analisando a camada de saida...\n");
				}

				// obtém a camada de saída
				Layer *outputLayer = (*layers)[this->hiddenLayers + 1];
				
				*quadraticError = 0;

				// calcula o delta de cada neurônio da camada de saída
				for (size_t idx = 0; idx < this->outputs; idx++) {
					
					Neuron *neuron = outputLayer->getNeuron(idx);

					double error = -output->data()[idx][0];
					if (idx == expectedIdx) {
						error += 1.0f;
					}

					neuron->setDelta(sigmoidPrime(neuron->getNetValue()) * error);
					
					if (logToFile) {
						Logger::logToFile("[%05d] %s E: %+9.6f\n", idx, neuron->toString().c_str(), error);
					}
				
					*quadraticError += std::pow(error, 2.0f);
					
				}

				*quadraticError *= 0.5f;

				// atualiza os pesos das camadas anteriores
				// iniciando na última camada escondida...
				for (size_t layerIdx = this->hiddenLayers; layerIdx != 0; layerIdx--) {
					
					if (logToFile) {
						Logger::logToFile("Analisando a camada escondida %d...\n", layerIdx);
					}
				
					Layer *layer = (*layers)[layerIdx];
					register size_t layerNeuronsCount = layer->neurons();

					Layer *nextLayer = (*layers)[layerIdx + 1];
					register size_t nextLayerNeuronsCount = nextLayer->neurons();

					// para todos os neurônios da camada atual...
					for (size_t neuronIdx = 0; neuronIdx < layerNeuronsCount; neuronIdx++) {

						// obtenha os deltas somando (pesos * deltas) de todos os neurônios da próxima camada
						register double sum = 0;
						Neuron *neuron = layer->getNeuron(neuronIdx);

						for (size_t nextLayerNeuronIdx = 0; nextLayerNeuronIdx < nextLayerNeuronsCount; nextLayerNeuronIdx++) {
							register Neuron *nextLayerNeuron = nextLayer->getNeuron(nextLayerNeuronIdx);
							sum += nextLayerNeuron->getWeight(neuronIdx) * nextLayerNeuron->getDelta();
						}
						neuron->setDelta(sigmoidPrime(neuron->getNetValue()) * sum);

						if (logToFile) {
							Logger::logToFile("[%05d] %s\n", neuronIdx, neuron->toString().c_str());
						}

						// agora, atualize os pesos da próxima camada usando a taxa de aprendizado
						for (size_t nextLayerNeuronIdx = 0; nextLayerNeuronIdx < nextLayerNeuronsCount; nextLayerNeuronIdx++) {
							
							register Neuron *nextLayerNeuron = nextLayer->getNeuron(nextLayerNeuronIdx);
							register double weight = this->learningRate * sigmoid(neuron->getNetValue()) * nextLayerNeuron->getDelta();
							nextLayerNeuron->updateWeight(neuronIdx,  weight);

							if (logToFile) {
								Logger::logToFile("       W__%d_%d = %9.6f\n", 
									neuronIdx, nextLayerNeuronIdx, nextLayerNeuron->getWeight(neuronIdx));
							}

						}

					}

				}
				
				if (logToFile) {
					Logger::logToFile("<<<< backPropagate()\n");
					Logger::logToFile("\n");
				}

				return true;

			};

			/**
			 * Imprime um falha de reconhecimento.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param inputRowIdx
			 *				o <code>size_t</code> que representa o registro da matriz de entrada
			 * @param output
			 *				o Matrix que representa a saída da rede
			 * @param expectedIdx
			 *				o <code>size_t</code> que representa o valor esperado
			 * @param actualIdx
			 *				o <code>size_t</code> que representa o valor obtido
			 * @param logToFile
			 *				indica se as mensagens de progresso devem ser salvas em arquivo
			 */
			PRIVATE static void printFailure(
					IN Matrix *input, 
					IN size_t inputRowIdx, 
					IN Matrix *output, 
					IN size_t expectedIdx, 
					IN size_t actualIdx,
					IN bool logToFile = false) {
				
				Logger::log("\n");

				const char *pszMsg = "[FALHA]: Valor obtido: %d, Valor esperado: %d\n";
				Logger::log(pszMsg, actualIdx, expectedIdx);

				Logger::log("         IN  :");
				const size_t inputColumns = input->getColumns();
				for (size_t idx = 1; idx < inputColumns; idx++) {
					Logger::logWithoutTimestamp(" %2.0f ", input->data()[inputRowIdx][idx]);
					if (idx % 4 == 0) {
						Logger::logWithoutTimestamp("\n");
						if (idx < 17) { 
							Logger::log("              ");
						}
					}
				}
				Logger::log("\n");

				const size_t outputRows = output->getRows();
				Logger::log("         OUT :");
				for (size_t idx = 0; idx < outputRows; idx++) {
					Logger::logWithoutTimestamp(" %8.5f ", output->data()[idx][0]);
				}
				Logger::logWithoutTimestamp("\n");
				
				if (logToFile) {
					Logger::logToFile(pszMsg, actualIdx, expectedIdx);
					input->dumpToFile(inputRowIdx);
					output->dumpToFile();
				}

			};

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param hiddenLayers
			 *				o <code>size_t</code> que representa a quantidade de camadas escondidas
			 * @param inputLayerNeuronCount
			 *				o <code>size_t</code> que representa a quantidade de neurônios da camada de entrada
			 * @param outputLayerNeuronCount
			 *				o <code>size_t</code> que representa a quantidade de neurônios da camada de saída
			 * @param neuronsPerLayer
			 *				o <code>std::vector</code> que representa a quantidade de neurônios por camada
			 * @param learningRate
			 *				a taxa de aprendizado
			 * @param bias
			 *				o <code>double</code> que representa o bias
			 */
			NeuralNetwork(
					IN size_t hiddenLayers, 
					IN size_t inputLayerNeuronCount, 
					IN size_t outputLayerNeuronCount, 
					IN std::vector<int> neuronsPerLayer,
					IN double learningRate = DEFAULT_LEARNING_RATE,
					IN double bias = DEFAULT_BIAS) {

				this->inputs = inputLayerNeuronCount;
				this->outputs = outputLayerNeuronCount;
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
			 * @param cycles
			 *				o <code>size_t</code> que representa a quantidade de ciclos
			 * @param groupStatsBy
			 *				o <code>size_t</code> que representa em que as estatísticas de treino devem ser agrupadas para exibição
			 * @param logNNToFile
			 *				indica se a rede deve ser impressa ao fim de cada ciclo
			 * @param logToFile
			 *				indica se as mensagens de progresso devem ser salvas em arquivo
			 *
			 * @return o <code>true</code> caso o treinamento tenha sido bem sucedido; do contrário <code>false</code>
			 */
			PUBLIC bool train(
					IN Matrix *input, 
					IN size_t cycles = DEFAULT_TRAINING_CYCLES, 
					IN size_t groupStatsBy = DEFAULT_STATS_GROUP_SIZE,
					IN bool logNNToFile = false, 
					IN bool logToFile = false) {

				if (Utils::isInvalidHandle(input)) {
					throw new IllegalParameterException();
				}
				
				size_t rows = input->getRows();
				size_t columns = input->getColumns();

				Logger::log("\n");
				Logger::log("Realizando treino. Aguarde...\n");
				for (size_t cycleIdx = 0; cycleIdx < cycles; cycleIdx++) {

					register double mse = 0.0f;
					
					for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					
						register size_t expected = (size_t)input->data()[rowIdx][0];

						Matrix *output = NULL;
						if (!feedForward(input, rowIdx, &output, logToFile)) {
							continue;
						}
					
						register double quadraticError = 0.0f;	
						backPropagate(output, expected, &quadraticError, logToFile);

						mse += quadraticError;

						delete output;

					}

					register double div_factor = (rows * 1.0f);
					if ((cycleIdx + 1) % groupStatsBy == 0) {
						Logger::log(">> CICLO #%06d: MSE %13.9f (+%013.9f%% -%013.9f%%) <<\n", 
								cycleIdx + 1,  
								mse / div_factor, 
								(this->trainingSuccesses / div_factor) * 100.0f,  
								(this->trainingFailures  / div_factor) * 100.0f);
					}

					if (logNNToFile) {
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
				Logger::log("\n");

				return true;

			};

			/**
			 * Avalia a rede contra uma amostra de teste.<br />
			 *
			 * @param input
			 *				o Matrix que representa o conjunto de amostras de treino
			 * @param logToFile
			 *				indica se as mensagens de progresso devem ser salvas em arquivo
			 * @param printFailures
			 *				indica se os resultados negativos devem ser impressos
			 *
			 * @return o <code>true</code> caso a avaliação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool test(
					IN Matrix *input, 
					IN bool logToFile = false,
					IN bool printFailures = false) {

				if (Utils::isInvalidHandle(input)) {
					throw new IllegalParameterException();
				}

				size_t rows = input->getRows();
				size_t columns = input->getColumns();

				Logger::log("\n");
				Logger::log("Realizando teste. Aguarde............... \n");
				
				for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					
					Matrix *output = NULL;

					if (!feedForward(input, rowIdx, &output, logToFile)) {
						continue;
					}

					register size_t expectedIdx = (size_t)input->data()[rowIdx][0];
					register size_t actualIdx = 0;

					if (succeeded(output, expectedIdx, &actualIdx)) {
						this->overallTestingSuccesses++;
					} else {
						if (printFailures) {
							printFailure(input, rowIdx, output, expectedIdx, actualIdx, logToFile);
						}
						this->overallTestingFailures++;
					}

					delete output;

				}

				double div_factor = (rows * 1.0f);
				Logger::log("\n");
				Logger::log(">> TOTAL:                            +%013.9f%% -%013.9f%%\n", 
						(this->overallTestingSuccesses / div_factor) * 100.0f, 
						(this->overallTestingFailures  / div_factor) * 100.0f);
				Logger::log("\n");

				return true;

			};

		}; /* class NeuralNetwork */

	} /* namespace neural */

} /* namespace pel203 */

#endif /* __NEURAL_NETWORK_H__ */
