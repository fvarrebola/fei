#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/functions/FirstFunction.h>
#include <inc/functions/SecondFunction.h>
#include <inc/functions/ThirdFunction.h>

#include <inc/integration/RectangleRule.h>
#include <inc/integration/TrapezoidalRule.h>
#include <inc/integration/SimpsonRule.h>

#include <inc/tests/TestSuiteWeek6.h>

#define A___INPUT_MSG							"Informe o ponto inicial (a) (double)"
#define B___INPUT_MSG							"Informe o ponto final (b) (double)"
#define INTERVAL__INPUT_MSG						"Informe a quantidade de intervalos (int)"
#define PRECISION__INPUT_MSG					"Informe a precisao para a quadratura adaptativa (double)"

#define RULE_PRINT_FORMAT						"> %s = %0.6f, EA=%0.9f, ER=%0.9f\n"

void playWithFirstFunction();
void playWithSecondFunction();
void playWithThirdFunction();

using namespace pel216::commons;
using namespace pel216::week6;

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
		"Considere a funcao e^x",
		playWithFirstFunction
	},	
	{
		PLAY_WITH_SECOND_FUNCTION,
		"Considere a funcao sqrt(1 - x^2)",
		playWithSecondFunction
	},
	{
		PLAY_WITH_THIRD_FUNCTION,
		"Considere a funcao e^(-x^2)",
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
 * Imprime o cabecalho.
 */
void printHeader() {
    Logger::log("%s\n", STARS);
    Logger::log("* PEL216\n");
    Logger::log("* Semana 6 - Metodo de integracao numerica\n");
    Logger::log("%s\n", STARS);
}



/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}



/**
 * Executa a integra��o num�rica registrando o resultado.
 *
 * @param rule
 *				o @link{IntegrationRule} que representa a regra a ser utilizada
 * @param function
 *				o @link{Function} que representa a fun��o a ser integrada
 * @param a
 *				o <code>double</code> que representa o valor do limite inferior da integra��o
 * @param b
 *				o <code>double</code> que representa o valor do limite superior da integra��o
 * @param intervals 
 *				o <code>size_t</code> que indica a quantidade de intervalos
 */
void doNumericalIntegration(IntegrationRule *rule, Function *function, double a, double b, size_t intervals = -1) {

	double result = rule->evaluate(function, a, b, intervals);

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("%s\n", rule->toString().c_str());
	Logger::log("%s\n", STARS);
	Logger::log(RULE_PRINT_FORMAT, function->toString().c_str(), result, rule->getAbsoluteError(), rule->getRelativeError());
	Logger::log("%s\n", STARS);

}

/**
* Tenta executar a integra��o num�rica para a fun��o @link{FirstFunction}.
*/
void playWithFirstFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);

	FirstFunction *function = new FirstFunction();

	RectangleRule *rule1 = new RectangleRule();
	TrapezoidalRule *rule2 = new TrapezoidalRule();
	SimpsonRule *rule3 = new SimpsonRule();

	doNumericalIntegration(rule1, function, a, b, intervals);
	doNumericalIntegration(rule2, function, a, b, intervals);
	doNumericalIntegration(rule3, function, a, b, intervals);

	delete rule1;
	delete rule2;
	delete rule3;
	delete function;

}



/**
 * Tenta executar a integra��o num�rica para a fun��o @link{SecondFunction}.
 */
void playWithSecondFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);

	SecondFunction *function = new SecondFunction();

	RectangleRule *rule1 = new RectangleRule();
	TrapezoidalRule *rule2 = new TrapezoidalRule();
	SimpsonRule *rule3 = new SimpsonRule();

	doNumericalIntegration(rule1, function, a, b, intervals);
	doNumericalIntegration(rule2, function, a, b, intervals);
	doNumericalIntegration(rule3, function, a, b, intervals);

	delete rule1;
	delete rule2;
	delete rule3;
	delete function;

}



/**
 * Tenta executar a integra��o num�rica para a fun��o @link{ThirdFunction}.
 */
void playWithThirdFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);
	double precision = UserParams::getDoubleParam(PRECISION__INPUT_MSG);

	ThirdFunction *function = new ThirdFunction();

	RectangleRule *rule1 = new RectangleRule();
	TrapezoidalRule *rule2 = new TrapezoidalRule();
	SimpsonRule *rule3 = new SimpsonRule();

	doNumericalIntegration(rule1, function, a, b, intervals);
	doNumericalIntegration(rule2, function, a, b, intervals);
	doNumericalIntegration(rule3, function, a, b, intervals);

	delete rule1;
	delete rule2;
	delete rule3;
	delete function;

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
