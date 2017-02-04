#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/CSVFileReader.h>

#include <inc/IrisData.h>
#include <inc/Matrix.h>
#include <inc/LDAMethod.h>

#include <inc/tests/SampleDataSets.h>
#include <inc/tests/TestSuite.h>

#define SAMPLES_FILE___INPUT_MSG				"Informe o caminho para as amostras"
#define DEBUG___INPUT_MSG						"Imprimir o conteudo das matrizes?"

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week1;

void playWithTestSuiteDataSet();
void playWithIrisDataSet();

// enum de comandos
enum Commands {
	PLAY_WITH_TEST_DATA_SET					= 0,
	PLAY_WITH_IRIS_DATA_SET					= 1,
    RUN_TESTS                      			= 2,
    EXIT                           			= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_TEST_DATA_SET,
		"Analise do conjunto de dados de testes",
		playWithTestSuiteDataSet,
	},
	{
		PLAY_WITH_IRIS_DATA_SET,
		"Analise do conjunto de dados \"iris\"",
		playWithIrisDataSet,
	},
	{
		RUN_TESTS,
		"Executar testes",
		pel208::week3::TestSuite::run
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
    Logger::log("* PEL208\n");
    Logger::log("* Semana 3 - LDA\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Analise as amostras do conjunto de dados de teste.<br />
 */
void playWithTestSuiteDataSet() {

	size_t classColumnIdx = 0;

	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	
	if (LDAMethod::evaluate(
			SampleDataSets::getLDASimpleDS(), 
			classColumnIdx, 
			&eigenValues, 
			&eigenVectors,
			UserParams::getBoolParam(DEBUG___INPUT_MSG))) {
		delete eigenValues;
		delete eigenVectors;
	}

}

/**
 * Analise as amostras do conjunto de dados "iris".<br />
 */
void playWithIrisDataSet() {

	// carrega o arquivo de amostras
	std::string filePath = UserParams::getStringParam(SAMPLES_FILE___INPUT_MSG);
	std::list<IrisData> samples = CSVFileReader::loadAsIris(filePath.c_str());

	size_t classColumnIdx = 0;
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	Matrix *dataMatrix = new Matrix(samples.size(), 5); 

	size_t idx = 0;
	for (std::list<IrisData>::iterator iterator = samples.begin(); 
			iterator != samples.end(); 
			++iterator) {

		dataMatrix->data()[idx][0] = iterator->getType();
		dataMatrix->data()[idx][1] = iterator->getPW();
		dataMatrix->data()[idx][2] = iterator->getPL();
		dataMatrix->data()[idx][3] = iterator->getSW();
		dataMatrix->data()[idx][4] = iterator->getSL();
		idx++;
		
	}
	 
	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	if (LDAMethod::evaluate(dataMatrix, classColumnIdx, &eigenValues, &eigenVectors, debug)) {
		delete eigenValues;
		delete eigenVectors;
	}

	delete dataMatrix;

}

/**
 * Ponto de entrada.
 */
int main(int argc, char** argv) {
	
	printHeader();

    bool shouldContinue = true;
    while (shouldContinue) {
        PMENU_OPTION pCommand = pel216::commons::Menu::pickMenuOption(MAIN_MENU);
        shouldContinue = (pCommand && pCommand->iOptionId != EXIT);
        if (shouldContinue) {
            pCommand->pfnFunction();
        }
    }

    printFooter();

}
