#include <algorithm>

#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/NeuralNetwork.h>
#include <inc/Layer.h>
#include <inc/Neuron.h>
#include <inc/Matrix.h>

#define ICADEMO_INPUT_LAYER_NEURONS_COUNT		10
#define ICADEMO_OUTPUT_LAYER_NEURONS_COUNT		10
#define ICADEMO_DATA_SET_COLUMN_COUNT			21

#define USPS_INPUT_LAYER_NEURONS_COUNT			256
#define USPS_OUTPUT_LAYER_NEURONS_COUNT			10
#define USPS_DATA_SET_COLUMN_COUNT				USPS_INPUT_LAYER_NEURONS_COUNT + 1


#define TRAINING_SET___INPUT_MSG				"Informe o conjunto de treinamento ....."
#define TEST_SET____INPUT_MSG					"Informe o conjunto de testes .........."

#define HIDDEN_LAYERS___INPUT_MSG				"Informe a qtde as camadas escondidas .."
#define NEURONS_PER_LAYER___INPUT_MSG			"Informe a qtde de nos por camada ......"
#define BIAS___INPUT_MSG						"Informe o bias ........................"
#define LEARNING_RATE___INPUT_MSG				"Informe a taxa de aprendizado ........."
#define TRAINING_CYCLES___INPUT_MSG				"Informe a qtde de iteracoes de treino ."
#define GROUP_STATS_BY___INPUT_MSG				"Informe o agrupador de estatisticas ..."

#define DEBUG___INPUT_MSG						"Imprimir a rede a cada ciclo?    "
#define TRACE___INPUT_MSG						"Imprimir conteudo dos neuronios? "

using namespace pel203::commons;
using namespace pel203::neural;

void playWithICADemoDataSet();
void playWithUSPSDataSet();

// enum de comandos
enum Commands {
	PLAY_WITH_ICADEMO_DATA_SET				= 0,
	PLAY_WITH_ICADEMO_EX_DATA_SET			= 1,
    PLAY_WITH_ZIP_CODE_DATA_SET    			= 2,
    EXIT                           			= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_ICADEMO_DATA_SET,
		"Analise do conjunto de digitos \"icademo\"",
		playWithICADemoDataSet,
	},
	{
		PLAY_WITH_ICADEMO_EX_DATA_SET,
		"Analise do conjunto de digitos \"icademo\" com variacoes",
		playWithICADemoDataSet,
	},
	{
		PLAY_WITH_ZIP_CODE_DATA_SET,
		"Analise do conjunto de dados do \"zip code\"",
		playWithUSPSDataSet,
	},
    {
        EXIT,        
        "Sair",                
        NULL
    },
    {-1, NULL, NULL}
};

/**
 * Imprime o cabecalho.
 */
void printHeader() {
    Logger::log("%s\n", STARS);
    Logger::log("* PEL203\n");
    Logger::log("* Trabalho opcional - Reconhecimento de digitos\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Carrega a matriz de dados de treinamento e/ou testes de um arquivo.<br />
 * 
 * @param filePath
 *				o <code>std::string</code> que representa o nome do arquivo
 * @param minColumnCount
 *				o <code>size_t</code> que representa a quantidade mínima que um registro deve ter
 * @param matrix
 *				o Matrix que representa a matriz de amostras de treinamento
 *
 * @return <code>true</code> caso a carga tenha sido bem sucedida; do contrário <code>false</code>
 */
bool loadMatrix(IN std::string filePath, IN size_t minColumnCount, IN OUT Matrix **matrix) {

	if (Utils::isInvalidHandle((char*)filePath.c_str())) {
		throw new IllegalParameterException();
	}

	std::ifstream ifstream(filePath);

	Logger::log("Determinando a quantidade de amostras... ");
	
	ifstream.unsetf(std::ios_base::skipws);
	size_t samples = std::count(std::istream_iterator<char>(ifstream), std::istream_iterator<char>(), '\n');
	if (samples < 1) {
		return false;
	}
	
	Logger::logWithoutTimestamp("%06d\n", samples);

	// volta o stream para o começo
	ifstream.clear();
	ifstream.seekg(0, std::ios::beg);

	// cria a matriz
	*matrix = new Matrix(samples, minColumnCount);

	Logger::log("Carregando as amostras.................. ");

	size_t samplesCount = 0;

	// leio o stream enquanto houver caracteres válidos
	while (ifstream.good() && (samplesCount < samples)) { 

		std::string line;
		std::getline(ifstream, line);

		// a delimitação por espaço é feita
		// a primeira coluna é o dígito
		// as demais colunas são as entradas
		const char delim = ' ';
		const char *str = line.c_str();
		size_t tokenCount = 0;
		do {
			const char *begin = str;
			while(*str != delim && *str) {
				str++;
			}
			(*matrix)->data()[samplesCount][tokenCount++] = atof(std::string(begin, str).c_str());
		} while (0 != *str++);

		if (tokenCount < minColumnCount) {
			continue;
		}

		samplesCount++;

	}

	Logger::logWithoutTimestamp("[ OK ]\n");

	return true;

}

/**
 * Analise as amostras do conjunto de dados ICADemo.<br />
 */
void playWithICADemoDataSet() {

	// a matriz de amostras para treinamento
	Matrix *trainingMatrix = NULL;
	if (!loadMatrix(
			UserParams::getStringParam(TRAINING_SET___INPUT_MSG), 
			ICADEMO_DATA_SET_COLUMN_COUNT, 
			&trainingMatrix)) {
		return;
	}

	// parâmetros de configuração da rede
	size_t hiddenLayers = UserParams::getIntParam(HIDDEN_LAYERS___INPUT_MSG); // 2
	std::vector<int> neuronsPerLayer = UserParams::getIntVectorParam(hiddenLayers, NEURONS_PER_LAYER___INPUT_MSG); // 64, 32

	double bias = UserParams::getDoubleParam(BIAS___INPUT_MSG); // 1.0f
	double learningRate = UserParams::getDoubleParam(LEARNING_RATE___INPUT_MSG); // 0.01f
	size_t trainingCycles = UserParams::getIntParam(TRAINING_CYCLES___INPUT_MSG);
	size_t groupStatsBy = UserParams::getIntParam(GROUP_STATS_BY___INPUT_MSG);
	
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);
	bool trace = UserParams::getBoolParam(TRACE___INPUT_MSG);

	NeuralNetwork *neuralNetwork = new NeuralNetwork(
			hiddenLayers, 
			ICADEMO_INPUT_LAYER_NEURONS_COUNT, 
			ICADEMO_OUTPUT_LAYER_NEURONS_COUNT,
			neuronsPerLayer, 
			learningRate, 
			bias);

	if (neuralNetwork->train(trainingMatrix, trainingCycles, groupStatsBy, debug, trace)) {
		Matrix *testMatrix = NULL;
		if (loadMatrix(
				UserParams::getStringParam(TEST_SET____INPUT_MSG), 
				ICADEMO_DATA_SET_COLUMN_COUNT, 
				&testMatrix)) {
			neuralNetwork->test(testMatrix, debug);
			delete testMatrix;
		}
	}

	delete neuralNetwork;
	delete trainingMatrix;

}

/**
 * Analise as amostras do conjunto de dados USPS.<br />
 */
void playWithUSPSDataSet() {

	// a matriz de amostras para treinamento
	Matrix *trainingMatrix = NULL;
	if (!loadMatrix(
			UserParams::getStringParam(TRAINING_SET___INPUT_MSG), 
			USPS_DATA_SET_COLUMN_COUNT, 
			&trainingMatrix)) {
		return;
	}

	// parâmetros de configuração da rede
	size_t hiddenLayers = UserParams::getIntParam(HIDDEN_LAYERS___INPUT_MSG); // 2
	std::vector<int> neuronsPerLayer = UserParams::getIntVectorParam(hiddenLayers, NEURONS_PER_LAYER___INPUT_MSG); // 64, 32

	double bias = UserParams::getDoubleParam(BIAS___INPUT_MSG); // 1.0f
	double learningRate = UserParams::getDoubleParam(LEARNING_RATE___INPUT_MSG); // 0.01f
	size_t trainingCycles = UserParams::getIntParam(TRAINING_CYCLES___INPUT_MSG);
	size_t groupStatsBy = UserParams::getIntParam(GROUP_STATS_BY___INPUT_MSG);

	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);
	bool trace = UserParams::getBoolParam(TRACE___INPUT_MSG);

	NeuralNetwork *neuralNetwork = new NeuralNetwork(
			hiddenLayers, 
			USPS_INPUT_LAYER_NEURONS_COUNT, 
			USPS_OUTPUT_LAYER_NEURONS_COUNT,
			neuronsPerLayer, 
			learningRate, 
			bias);

	if (neuralNetwork->train(trainingMatrix, trainingCycles, groupStatsBy, debug, trace)) {
		Matrix *testMatrix = NULL;
		if (loadMatrix(
				UserParams::getStringParam(TEST_SET____INPUT_MSG), 
				USPS_DATA_SET_COLUMN_COUNT,
				&testMatrix)) {
			neuralNetwork->test(testMatrix, debug);
			delete testMatrix;
		}
	}

	delete neuralNetwork;
	delete trainingMatrix;

}

/**
 * Ponto de entrada.
 */
int main(int argc, char** argv) {
	
	printHeader();

    bool shouldContinue = true;
    while (shouldContinue) {
	        PMENU_OPTION pCommand = pel203::commons::Menu::pickMenuOption(MAIN_MENU);
        shouldContinue = (pCommand && pCommand->iOptionId != EXIT);
        if (shouldContinue) {
            pCommand->pfnFunction();
        }
    }

    printFooter();

}
