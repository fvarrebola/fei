#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/BookAttendGrade.h>
#include <inc/CSVFileReader.h>
#include <inc/NearestNeighbor.h>

#include <inc/tests/TestSuite.h>

#define SAMPLES_FILE___INPUT_MSG				"Informe o caminho para as amostras "
#define BOOKS___INPUT_MSG						"Informe a quantidade de livros     "
#define CLASSES___INPUT_MSG						"Informe a quantidade de aulas      "
#define NEIGHBORS___INPUT_MSG					"Informe a quantidade de vizinhos (K)"

void playWithNearestNeighborFunction();

using namespace pel216::commons;
using namespace pel216::week8;

// enum de comandos
enum Commands {
	PLAY_WITH_KNN_FUNCTION			= 0,
    RUN_TESTS                      	= 1,
    EXIT                           	= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_KNN_FUNCTION,
		"Estimar com K-NN",
		playWithNearestNeighborFunction
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
    Logger::log("* PEL216\n");
    Logger::log("* Semana 8 - Estimativas com o Nearest Neighbor\n");
    Logger::log("%s\n", STARS);
}



/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
* Tenta executar a integração numérica para a função @link{FirstFunction}.
*/
void playWithNearestNeighborFunction() {

	std::string filePath = UserParams::getStringParam(SAMPLES_FILE___INPUT_MSG);
	int books = UserParams::getIntParam(BOOKS___INPUT_MSG);
	int classes = UserParams::getIntParam(CLASSES___INPUT_MSG);
	int neighbors = UserParams::getIntParam(NEIGHBORS___INPUT_MSG);

	NearestNeighbor *method = new NearestNeighbor(CSVFileReader::load(filePath.c_str()));
	
	BookAttendGrade target(books, classes);

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Alvo: %s\n", target.toString().c_str());
	Logger::log("*   K: %d\n", neighbors);
	Logger::log("%s\n", STARS);

	Logger::log(" NOTA: %02.9f\n", method->evaluate(target, neighbors));

	Logger::log("%s\n", STARS);

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
