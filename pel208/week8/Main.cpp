#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/Matrix.h>

#include <inc/QLearningOffPolicyTDControl.h>

#define GRID_SIZE___INPUT_MSG					"Informe as dimensoes do grid..........."
#define EPISODES___INPUT_MSG					"Informe a quantidade de iteracoes......"
#define LEARNING_RATE___ALPHA___INPUT_MSG		"Informe a taxa de aprendizado.........."
#define DISCOUNT_RATE___GAMMA___INPUT_MSG		"Informe a taxa de desconto............."

#define DEBUG___INPUT_MSG						"Imprimir mensagens de progresso? "

#define PRINT_R___INPUT_MSG						"Imprimir matriz R dos episodios? "
#define EPISODES_TO_PRINT___INPUT_MSG			"Informe a qtde de episodios (0 = todos)"

using namespace pel216::commons;
using namespace pel208::commons;
using namespace pel208::week8;

void playWithQLearning();

// enum de comandos
enum Commands {
	PLAY_WITH_Q_LEARNING								= 0,
    EXIT                           						= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_Q_LEARNING,
		"Analise do Q Learning para o \"small world grid\"",
		playWithQLearning,
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
    Logger::log("* Semana 8 - Metodo Q LEarning Off-Policy TD Control\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Analise de programação dinâmica para o problema do <i>small grid world</i>.<br />
 * Utiliza o método Q Learning.<br />
 *
 * @see QLearningOffPolicyTDControl
 */
void playWithQLearning() {

	size_t states =  0;
	size_t root = 0;
	while (states == 0  || !SmallGridWorld::isPerfectSquare(states, &root)) {
		states = UserParams::getIntParam(GRID_SIZE___INPUT_MSG);
	}

	size_t episodes = UserParams::getIntParam(EPISODES___INPUT_MSG);
	double alpha= UserParams::getDoubleParam(LEARNING_RATE___ALPHA___INPUT_MSG);
	double gamma = UserParams::getDoubleParam(DISCOUNT_RATE___GAMMA___INPUT_MSG);
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	SmallGridWorld *world = new SmallGridWorld(states);
	world->dump();
	if (debug) {
		world->dumpToFile();
	}

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando avaliacao utilizando Q learning...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	SmallGridWorld *goal = NULL;
	Matrix *R = NULL;
	if (QLearningOffPolicyTDControl::evaluate(world, &goal, &R, episodes, alpha, gamma, debug)) {
		
		goal->dump();
		if (debug) {
			goal->dumpToFile();
		}
		delete goal;

		Logger::log("\n");
		if (UserParams::getBoolParam(PRINT_R___INPUT_MSG)) {
			R->dumpToFile(UserParams::getIntParam(EPISODES_TO_PRINT___INPUT_MSG));
		}
		delete R;

	}

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	delete world;

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
