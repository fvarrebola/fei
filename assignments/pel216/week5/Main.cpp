#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/functions/FirstFunction.h>
#include <inc/functions/SecondFunction.h>
#include <inc/functions/ThirdFunction.h>

#include <inc/optimization/GradientDescent.h>

#include <inc/tests/TestSuiteWeek5.h>

#define X0___INPUT_MSG							"Informe o estado inicial (x0)"
#define Y0___INPUT_MSG							"Informe o estado inicial (y0)"
#define LAMBDA__INPUT_MSG						"Informe o lambda"
#define PRECISION__INPUT_MSG					"Informe a precisao"
#define MAX_ITERATIONS__INPUT_MSG				"Informe a quantidade maxima de iteracoes"
#define DEBUG_OPT___INPUT_MSG					"Imprimir mensagens?"

void playWithFirstFunction();
void playWithSecondFunction();
void playWithThirdFunction();

using namespace pel216::commons;
using namespace pel216::week5;


// enum de comandos
enum Commands {
	PLAY_WITH_FIRST_FUNCTION		= 0,
	PLAY_WITH_SECOND_FUNCTION		= 1,
	PLAY_WITH_THIRD_FUNCTION		= 2,
    RUN_TESTS                      	= 3,
    EXIT                           	= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_FIRST_FUNCTION,
		"Executa a descida de grandiente em f(x) = x^2",
		playWithFirstFunction
	},	
	{
		PLAY_WITH_SECOND_FUNCTION,
		"Executa a descida de gradiente em f(x) = x^3 - 2x^2 + 2",
		playWithSecondFunction
	},
	{
		PLAY_WITH_THIRD_FUNCTION,
		"Executa a descida de gradiente em f(x, y) = (1 - x)^2 + 100(x - y^2)^2",
		playWithThirdFunction
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
 * Imprime o cabecalho.<br />
 */
void printHeader() {
    Logger::log("%s\n", STARS);
    Logger::log("* PEL216\n");
    Logger::log("* Semana 5 - Metodo de descida de gradiente\n");
    Logger::log("%s\n", STARS);
}



/**
 * Imprime o rodape.<br />
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}



/**
 * Tenta executar o algoritmo de descida de gradiente com a funcao f(x) = x^2.<br />
 *
 * @see FirstFunction
 */
void playWithFirstFunction() {

	double x0 = UserParams::getDoubleParam(X0___INPUT_MSG);
	double lambda = UserParams::getDoubleParam(LAMBDA__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);
	size_t max_iterations = UserParams::getIntParam(MAX_ITERATIONS__INPUT_MSG);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	FirstFunction *f = new FirstFunction(x0);
	GradientDescent *gd = new GradientDescent(debug);
	gd->evaluate(f, lambda, precision, max_iterations);

}



/**
 * Tenta executar o algoritmo de descida de gradiente com a funcao f(x) = x^3 - 2x^2 + 2.<br />
 *
 * @see SecondFunction
 */
void playWithSecondFunction() {

	double x0 = UserParams::getDoubleParam(X0___INPUT_MSG);
	double lambda = UserParams::getDoubleParam(LAMBDA__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);
	size_t max_iterations = UserParams::getIntParam(MAX_ITERATIONS__INPUT_MSG);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	SecondFunction *f = new SecondFunction(x0);
	GradientDescent *gd = new GradientDescent(debug);
	gd->evaluate(f, lambda, precision, max_iterations);

}



/**
 * Tenta executar o algoritmo de descida de gradiente com a funcao f(y, x) = (1 - y)^2 + 100(x - y^2)^2.<br />
 *
 * @see ThirdFunction
 */
void playWithThirdFunction() {

	double x0 = UserParams::getDoubleParam(X0___INPUT_MSG);
	double y0 = UserParams::getDoubleParam(Y0___INPUT_MSG);
	double lambda = UserParams::getDoubleParam(LAMBDA__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);
	size_t max_iterations = UserParams::getIntParam(MAX_ITERATIONS__INPUT_MSG);

	bool debug = false;
	if (UserParams::getBoolParam(DEBUG_OPT___INPUT_MSG)) {
		debug = true;
	}

	ThirdFunction *f = new ThirdFunction(x0, y0);
	GradientDescent *gd = new GradientDescent(debug);
	gd->evaluate(f, lambda, precision, max_iterations);

}



/**
 * Ponto de entrada.<br />
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
