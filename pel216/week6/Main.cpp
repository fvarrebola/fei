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
#include <inc/integration/AdaptativeQuadrature.h>

#include <inc/tests/TestSuiteWeek6.h>

#define A___INPUT_MSG							"Informe o ponto inicial (a) (double)"
#define B___INPUT_MSG							"Informe o ponto final (b) (double)"
#define INTERVAL__INPUT_MSG						"Informe a quantidade de intervalos (int)"

#define RULE_PRINT_FORMAT						

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
 * Imprime o cabeçalho de uma função.
 *
 * @param function
 *				o @link{Function} que representa a função a ser integrada
 * @param a
 *				o <code>double</code> que representa o valor do limite inferior da integração
 * @param b
 *				o <code>double</code> que representa o valor do limite superior da integração
 */
void printFunctionHeader(Function *function, double a, double b) {

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Funcao: %s\n", function->toString().c_str());
	Logger::log("*   Integral entre [a=%.2f, b=%.2f]: %0.12f\n", a, b, function->evaluatePreciseIntegration(a, b));
	Logger::log("%s\n", STARS);

}



/**
 * Executa a integração numérica registrando o resultado.
 *
 * @param rule
 *				o @link{IntegrationRule} que representa a regra a ser utilizada
 * @param function
 *				o @link{Function} que representa a função a ser integrada
 * @param a
 *				o <code>double</code> que representa o valor do limite inferior da integração
 * @param b
 *				o <code>double</code> que representa o valor do limite superior da integração
 * @param intervals 
 *				o <code>size_t</code> que indica a quantidade de intervalos
 */
void doNumericalIntegration(IntegrationRule *rule, Function *function, double a, double b, size_t intervals = -1) {

	double ruleResult = rule->evaluate(function, a, b, intervals);
	Logger::log("> %s\n", rule->toString().c_str());
	Logger::log("  > integral = %0.12f, EA=%0.12f, ER=%0.12f\n", ruleResult, rule->getAbsoluteError(), rule->getRelativeError());

	AdaptativeQuadrature *adapQuad = new AdaptativeQuadrature();
	double adapQuadResult = adapQuad->evaluate(rule, function, a, b);
	Logger::log("  > quadadap = %0.12f, EA=%0.12f, ER=%0.12f\n", adapQuadResult, adapQuad->getAbsoluteError(), adapQuad->getRelativeError());
	Logger::log("\n");

}

/**
* Tenta executar a integração numérica para a função @link{FirstFunction}.
*/
void playWithFirstFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	FirstFunction *function = new FirstFunction();
	printFunctionHeader(function, a, b);

	RectangleRule *rule1 = new RectangleRule();
	TrapezoidalRule *rule2 = new TrapezoidalRule();
	SimpsonRule *rule3 = new SimpsonRule();
	
	doNumericalIntegration(rule1, function, a, b, intervals);
	doNumericalIntegration(rule2, function, a, b, intervals);	
	doNumericalIntegration(rule3, function, a, b, intervals);
	
	Logger::log("%s\n", STARS);

	delete rule1;
	delete rule2;
	delete rule3;
	delete function;

}



/**
 * Tenta executar a integração numérica para a função @link{SecondFunction}.
 */
void playWithSecondFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	SecondFunction *function = new SecondFunction();
	printFunctionHeader(function, a, b);

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
 * Tenta executar a integração numérica para a função @link{ThirdFunction}.
 */
void playWithThirdFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	ThirdFunction *function = new ThirdFunction();
	printFunctionHeader(function, a, b);

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
