#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/Matrix.h>

#include <inc/SmallGridWorld.h>
#include <inc/OnPolicyMonteCarlo.h>

#define GRID_SIZE___INPUT_MSG					"Informe as dimensoes do grid..........."
#define ITERATIONS___INPUT_MSG					"Informe a quantidade de iteracoes......"
#define EPISLON___INPUT_MSG						"Informe o epsilon......................"
#define UNIQUE_Q___INPUT_MSG					"Atualizar politicas com Q unico? "

#define DEBUG___INPUT_MSG						"Imprimir mensagens de progresso? "

using namespace pel216::commons;
using namespace pel208::commons;
using namespace pel208::week7;

void playWithSmallGridWorldUsingOnPolicyMC();

// enum de comandos
enum Commands {
	PLAY_WITH_SMALL_GRID_WORLD_USING_ON_POLICY_MC		= 0,
    EXIT                           						= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_SMALL_GRID_WORLD_USING_ON_POLICY_MC,
		"Analise do \"small grid world\" com on-policy MC",
		playWithSmallGridWorldUsingOnPolicyMC,
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
    Logger::log("* Semana 7 - Metodo On-Policy Monte Carlo Control\n");
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
 * Utiliza o método On-Policy Monte Carlo Control.<br />
 *
 * @see OnPolicyMonteCarlo
 */
void playWithSmallGridWorldUsingOnPolicyMC() {

	size_t states =  0;
	size_t root = 0;
	while (states == 0  || !SmallGridWorld::isPerfectSquare(states, &root)) {
		states = UserParams::getIntParam(GRID_SIZE___INPUT_MSG);
	}

	size_t iterations = UserParams::getIntParam(ITERATIONS___INPUT_MSG);
	
	double epsilon = UserParams::getDoubleParam(EPISLON___INPUT_MSG);
	bool uniqueQ = UserParams::getBoolParam(UNIQUE_Q___INPUT_MSG);
	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	SmallGridWorld *world = new SmallGridWorld(states);
	world->dump();
	if (debug) {
		world->dumpToFile();
	}

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando avaliacao utilizando monte carlo...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	SmallGridWorld *goal = NULL;
	if (OnPolicyMonteCarlo::evaluate(world, &goal, iterations, epsilon, uniqueQ, debug)) {
		goal->dump();
		if (debug) {
			goal->dumpToFile();
		}
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
