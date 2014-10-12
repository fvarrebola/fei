#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/CSVFileReader.h>

#include <inc/Hald.h>
#include <inc/Matrix.h>
#include <inc/PCAMethod.h>

#include <inc/tests/TestSuite.h>

#define SAMPLES_FILE___INPUT_MSG				"Informe o caminho para as amostras "
#define COMPONENTS___INPUT_MSG					"Informe a quantidade de componentes"
#define DEBUG___INPUT_MSG						"Imprimir o conteudo das matrizes?  "

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week1;
using namespace pel208::week2;

void playWithTestSuiteDataSet();
void playWithHaldDataSet();

// enum de comandos
enum Commands {
	PLAY_WITH_TEST_DATA_SET					= 0,
	PLAY_WITH_HALD_DATA_SET					= 1,
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
		PLAY_WITH_HALD_DATA_SET,
		"Analise do conjunto de dados \"hald\"",
		playWithHaldDataSet,
	},
	{
		RUN_TESTS,
		"Executar testes",
		TestSuite::run
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
    Logger::log("* Semana 2 - PCA\n");
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

	Matrix *matrix = new Matrix(10, 2);
	matrix->data()[0][0] = 2.5f;
	matrix->data()[1][0] = 0.5f;
	matrix->data()[2][0] = 2.2f;
	matrix->data()[3][0] = 1.9f;
	matrix->data()[4][0] = 3.1f;
	matrix->data()[5][0] = 2.3f;
	matrix->data()[6][0] = 2.0f;
	matrix->data()[7][0] = 1.0f;
	matrix->data()[8][0] = 1.5;
	matrix->data()[9][0] = 1.1;
	
	matrix->data()[0][1] = 2.4f;
	matrix->data()[1][1] = 0.7f;
	matrix->data()[2][1] = 2.9f;
	matrix->data()[3][1] = 2.2f;
	matrix->data()[4][1] = 3.0f;
	matrix->data()[5][1] = 2.7f;
	matrix->data()[6][1] = 1.6f;
	matrix->data()[7][1] = 1.1f;
	matrix->data()[8][1] = 1.6f;
	matrix->data()[9][1] = 0.9f;
	
	// obtém os parâmetros de entrada do usuário final
	size_t components = UserParams::getIntParam(COMPONENTS___INPUT_MSG);
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	Logger::log("%s\n", STARS);
	Logger::log("* Componentes: %d\n", components);
	Logger::log("* Debug: %d\n", (debug ? "S" : "N"));
	Logger::log("%s\n", STARS);

	Matrix *pca = NULL;
	if (PCAMethod::evaluate(matrix, &pca, components, debug)) {
		delete pca;
	}

	delete matrix;

}

/**
 * Analise as amostras do conjunto de dados "hald".<br />
 */
void playWithHaldDataSet() {

	std::string filePath = UserParams::getStringParam(SAMPLES_FILE___INPUT_MSG);
	
	// carrega o arquivo de amostras
	std::list<Hald> samples = CSVFileReader::loadAsHald(filePath.c_str());

	Matrix *xMatrix = new Matrix(samples.size(), 4); 
	Matrix *yMatrix = new Matrix(samples.size(), 1); 

	size_t idx = 0;
	for (std::list<Hald>::iterator iterator = samples.begin(); 
			iterator != samples.end(); 
			++iterator) {

		xMatrix->data()[idx][0] = iterator->getX1();
		xMatrix->data()[idx][1] = iterator->getX2();
		xMatrix->data()[idx][2] = iterator->getX3();
		xMatrix->data()[idx][3] = iterator->getX4();
		yMatrix->data()[idx][0] = iterator->getY();
		idx++;
		
	}

	// obtém os parâmetros de entrada do usuário final
	size_t components = UserParams::getIntParam(COMPONENTS___INPUT_MSG);
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	Logger::log("%s\n", STARS);
	Logger::log("* Componentes: %d\n", components);
	Logger::log("* Debug: %d\n", (debug ? "S" : "N"));
	Logger::log("%s\n", STARS);

	Matrix *pca = NULL;
	if (PCAMethod::evaluate(xMatrix, &pca, components, debug)) {
		delete pca;
	}

	delete yMatrix;
	delete xMatrix;

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
