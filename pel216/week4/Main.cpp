#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/puzzles/8tiles/EightPuzzleState.h>
#include <inc/puzzles/8tiles/EightPuzzleSolver.h>
#include <inc/puzzles/8tiles/EightPuzzleBestFirstSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleHillClimbingSearchEngine.h>
#include <inc/puzzles/8tiles/EightPuzzleAStarSearchEngine.h>

#include <inc/tests/TestSuiteWeek4.h>

#define INITIAL_STATE_OPT___INPUT_MSG			"Informe o estado inicial (separado por virgula)"
#define GOAL_STATE_OPT__INPUT_MSG				"Informe o estado final (separado por virgula)"
#define MAX_DEPTH_OPT___INPUT_MSG_1				"Informar profundidade maxima?"
#define MAX_DEPTH_OPT___INPUT_MSG_2				"Informe a profundidade maxima permitida"
#define DEBUG_OPT___INPUT_MSG					"Imprimir mensagens?"

void solve8PuzzleWithHillClimbing();
void solve8PuzzleWithBestFirstSearch();
void solve8PuzzleWithAStar();

using namespace pel216::commons;
using namespace pel216::week3;
using namespace pel216::week4;

// enum de comandos
enum Commands {
    SLOVE_8_PUZZLE_WITH_HILL		= 0,
    SLOVE_8_PUZZLE_WITH_BEST		= 1,
    SLOVE_8_PUZZLE_WITH_A_START		= 2,
    RUN_TESTS                      	= 3,
    EXIT                           	= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		SLOVE_8_PUZZLE_WITH_HILL,
		"Resolver o jogo dos 8 com Hill Climbing",
		solve8PuzzleWithHillClimbing
	},
	{
		SLOVE_8_PUZZLE_WITH_BEST,
		"Resolver o jogo dos 8 com Best First Search",
		solve8PuzzleWithBestFirstSearch
	},
	{
		SLOVE_8_PUZZLE_WITH_A_START,
		"Resolver o jogo dos 8 com A*",
		solve8PuzzleWithAStar
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
    Logger::log("* Semana 4 - Buscas Hill Climbing, Best First Search e A*\n");
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
 * Resolve o jogo das 8 peças usando o Hill Climbing.
 */
void solve8PuzzleWithHillClimbing() {

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
	
	EightPuzzleHillClimbingSearchEngine e = EightPuzzleHillClimbingSearchEngine(maxDepth, debug);
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("%s\n", ex->what());
	}

}



/**
 * Resolve o jogo das 8 peças usando o Best First Search.
 */
void solve8PuzzleWithBestFirstSearch() {

	EightPuzzleState s = buildStateFromUserInput(INITIAL_STATE_OPT___INPUT_MSG);
	EightPuzzleState g = buildStateFromUserInput(GOAL_STATE_OPT__INPUT_MSG);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	EightPuzzleBestFirstSearchEngine e = EightPuzzleBestFirstSearchEngine();
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("%s\n", ex->what());
	}

}



/**
 * Resolve o jogo das 8 peças usando o Best First Search.
 */
void solve8PuzzleWithAStar() {

	EightPuzzleState s = buildStateFromUserInput(INITIAL_STATE_OPT___INPUT_MSG);
	EightPuzzleState g = buildStateFromUserInput(GOAL_STATE_OPT__INPUT_MSG);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	EightPuzzleAStarSearchEngine e = EightPuzzleAStarSearchEngine();
	EightPuzzleSolver solver(&e, &s, &g);
	
	try {
		solver.solve();
	} catch (pel216::week3::SolutionNotFoundException *ex) {
		Logger::log("%s\n", ex->what());
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
