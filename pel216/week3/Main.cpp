#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleSolver.h>
#include <inc/puzzles/8tiles/EightPuzzleBFSSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleDFSSearchEngine.h>

#include <inc/tests/TestSuite.h>

#define INITIAL_STATE_OPT___INPUT_MSG			"Informe o estado inicial (separado por virgula)"
#define GOAL_STATE_OPT__INPUT_MSG				"Informe o estado final (separado por virgula)"
#define MAX_DEPTH_OPT___INPUT_MSG_1				"Informar profundidade maxima?"
#define MAX_DEPTH_OPT___INPUT_MSG_2				"Informe a profundidade maxima permitida"
#define DEBUG_OPT___INPUT_MSG					"Imprimir mensagens?"

void solve8PuzzleWithBFS();
void solve8PuzzleWithDFS();

using namespace pel216::commons;
using namespace pel216::week3;

// enum de comandos
enum Commands {
    SLOVE_8_PUZZLE_WITH_BFS			= 0,
    SLOVE_8_PUZZLE_WITH_DFS			= 1,
    RUN_TESTS                      	= 2,
    EXIT                           	= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		SLOVE_8_PUZZLE_WITH_BFS,
		"Resolver o jogo dos 8 com BFS",
		solve8PuzzleWithBFS
	},
	{
		SLOVE_8_PUZZLE_WITH_DFS,
		"Resolver o jogo dos 8 com DFS",
		solve8PuzzleWithDFS
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
    Logger::log("* Semana 3 - Buscas com BFS e DFS\n");
    Logger::log("%s\n", STARS);
}



/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}



/**
 * Método utilitário para construir um estado para o jogo das 8 peças.
 *
 * @param inputString
 *
 * @return o @link{EightPuzzleState} que representa o estado
 */
EightPuzzleState buildStateFromUserInput(std::string inputMsg) {
	return EightPuzzleState(UserParams::getIntVectorParam(EIGHT_PUZZLE_STATE_LENGTH, inputMsg));
};



/**
 * Resolve o jogo das 8 peças usando o BFS.
 */
void solve8PuzzleWithBFS() {

	EightPuzzleState s = buildStateFromUserInput(INITIAL_STATE_OPT___INPUT_MSG);
	EightPuzzleState g = buildStateFromUserInput(GOAL_STATE_OPT__INPUT_MSG);

	size_t maxDepth = -1;
	if (UserParams::getBoolParam(MAX_DEPTH_OPT___INPUT_MSG_1)) {
		maxDepth = UserParams::getIntParam(MAX_DEPTH_OPT___INPUT_MSG_2);
	}

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	EightPuzzleBFSSearchEngine e = EightPuzzleBFSSearchEngine(maxDepth, debug);
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("Nenhuma solucao foi encontrada\n");
	}

}



/**
 * Resolve o jogo das 8 peças usando o DFS.
 */
void solve8PuzzleWithDFS() {

	EightPuzzleState s = buildStateFromUserInput(INITIAL_STATE_OPT___INPUT_MSG);
	EightPuzzleState g = buildStateFromUserInput(GOAL_STATE_OPT__INPUT_MSG);

	// para o DFS a profundidade máxima permitida é parâmetro obrigatório
	size_t maxDepth = UserParams::getIntParam(MAX_DEPTH_OPT___INPUT_MSG_2);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	EightPuzzleBFSSearchEngine e = EightPuzzleBFSSearchEngine(maxDepth, debug);
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("Nenhuma solucao foi encontrada\n");
	}

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
