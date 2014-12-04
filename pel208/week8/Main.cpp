#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/Matrix.h>

#include <inc/QLearningOffPolicyTDControl.h>

#define GRID_SIZE___INPUT_MSG					"Informe as dimensoes do grid..........."
#define ITERATIONS___INPUT_MSG					"Informe a quantidade de iteracoes......"
#define EPISLON___INPUT_MSG						"Informe o epsilon......................"
#define DISCOUNT_RATE___GAMMA___INPUT_MSG		"Informe a taxa de desconto............."

#define DEBUG___INPUT_MSG						"Imprimir mensagens de progresso? "

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
 * Analise de programa��o din�mica para o problema do <i>small grid world</i>.<br />
 * Utiliza o m�todo Q Learning.<br />
 *
 * @see QLearningOffPolicyTDControl
 */
void playWithQLearning() {

	size_t states =  0;
	size_t root = 0;
	while (states == 0  || !SmallGridWorld::isPerfectSquare(states, &root)) {
		states = UserParams::getIntParam(GRID_SIZE___INPUT_MSG);
	}

	size_t iterations = UserParams::getIntParam(ITERATIONS___INPUT_MSG);
	
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	SmallGridWorld *world = new SmallGridWorld(states);
	world->dump();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando avaliacao utilizando Q learning...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	SmallGridWorld *goal = NULL;
	if (QLearningOffPolicyTDControl::evaluate(world, &goal, iterations, debug)) {
		goal->dump();
		delete goal;
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
