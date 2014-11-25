#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/Matrix.h>

#include <inc/SmallGridWorld.h>
#include <inc/DynamicProgramming.h>

#define GRID_SIZE___INPUT_MSG					"Informe as dimensoes do grid..........."
#define PRECISION____THETA___INPUT_MSG			"Informe o theta (precisao)............."
#define DISCOUNT_RATE___GAMMA___INPUT_MSG		"Informe a taxa de desconto............."

#define DEBUG___INPUT_MSG						"Imprimir mensagens de progresso? "

using namespace pel216::commons;
using namespace pel208::commons;
using namespace pel208::week6;

void playWithSmallGridWorldUsingPolicyIteration();
void playWithSmallGridWorldUsingValueIteration();

// enum de comandos
enum Commands {
	PLAY_WITH_SMALL_GRID_WORLD_USING_POLICY_ITERATION	= 0,
	PLAY_WITH_SMALL_GRID_WORLD_USING_VALUE_ITERATION	= 1,
    EXIT                           						= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_SMALL_GRID_WORLD_USING_POLICY_ITERATION,
		"Analise do \"small grid world\" com iteracao de politica",
		playWithSmallGridWorldUsingPolicyIteration,
	},
	{
		PLAY_WITH_SMALL_GRID_WORLD_USING_VALUE_ITERATION,
		"Analise do \"small grid world\" com iteracao de valor",
		playWithSmallGridWorldUsingValueIteration,
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
    Logger::log("* Semana 6 - Programacao dinamica\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Analise de programação dinâmica para o problema do <i>small grid world</i> utilizando iteração de política.<br />
 */
void playWithSmallGridWorldUsingPolicyIteration() {

	size_t states = 0;
	size_t root = 0;
	while (states == 0  || !SmallGridWorld::isPerfectSquare(states, &root)) {
		states = UserParams::getIntParam(GRID_SIZE___INPUT_MSG);
	}

	double theta = UserParams::getDoubleParam(PRECISION____THETA___INPUT_MSG); // 0.000001f
	double gamma =UserParams::getDoubleParam(DISCOUNT_RATE___GAMMA___INPUT_MSG); // 1.0f
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	SmallGridWorld *world = new SmallGridWorld(states);

	size_t iteractions = 0;
	SmallGridWorld *newWorld = NULL;

	Logger::log("Iniciando avaliacao utilizando iteracao de politica...\n");
	if (DynamicProgramming::evaluateUsingPolicyIteration(world, &newWorld, &iteractions, theta, gamma, debug)) {

		Logger::log("Convergencia atingida apos %d iteracoes\n", iteractions);
		Logger::log("Estado Valor  Politica\n");
		Logger::log("------ ------ ---------------------------------------------------------------\n");

		for (size_t stateIdx = 0; stateIdx < states; stateIdx++) {
			newWorld->getState(stateIdx)->dump();
		}

		delete newWorld;

	}

	delete world;

}

/**
 * Analise de programação dinâmica para o problema do <i>small grid world</i> utilizando iteração de valor.<br />
 */
void playWithSmallGridWorldUsingValueIteration() {

	size_t states = 0;
	size_t root = 0;
	while (states == 0  || !SmallGridWorld::isPerfectSquare(states, &root)) {
		states = UserParams::getIntParam(GRID_SIZE___INPUT_MSG);
	}

	double theta = UserParams::getDoubleParam(PRECISION____THETA___INPUT_MSG); // 0.000001f
	double gamma =UserParams::getDoubleParam(DISCOUNT_RATE___GAMMA___INPUT_MSG); // 1.0f
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	SmallGridWorld *world = new SmallGridWorld(states);

	size_t iteractions = 0;
	SmallGridWorld *newWorld = NULL;

	Logger::log("Iniciando avaliacao utilizando iteracao de valor...\n");
	if (DynamicProgramming::evaluateUsingValueIteration(world, &newWorld, &iteractions, theta, gamma, debug)) {

		Logger::log("Convergencia atingida apos %d iteracoes\n", iteractions);

		Logger::log("Estado Valor  Politica\n");
		Logger::log("------ ------ ---------------------------------------------------------------\n");

		for (size_t stateIdx = 0; stateIdx < states; stateIdx++) {
			newWorld->getState(stateIdx)->dump();
		}

		delete newWorld;

	}

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
