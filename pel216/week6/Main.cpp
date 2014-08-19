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

#define RULE_PRINT_FORMAT						"> %s = %0.6f, EA=%0.9f, ER=%0.9f\n"

void playWithRectangleRuleFunction();
void playWithTrapezoidalRuleFunction();
void playWithSimpsonRuleFunction();

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
		RUN_TESTS,
		"Executa a integracao baseado na regra do retangulo",
		playWithRectangleRuleFunction
	},	
	{
		RUN_TESTS,
		"Executa a integracao baseado na regra do trapezoide",
		playWithTrapezoidalRuleFunction
	},
	{
		RUN_TESTS,
		"Executa a integracao baseado na regra de Simpson",
		playWithSimpsonRuleFunction
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

	double result = rule->evaluate(function, a, b, intervals);
	Logger::log(RULE_PRINT_FORMAT, function->toString().c_str(), result, rule->getAbsoluteError(), rule->getRelativeError());

}

/**
 * Tenta executar a integração numérica utilizando a regra do retângulo.
 *
 * @see RectangleRule
 */
void playWithRectangleRuleFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	RectangleRule *rule = new RectangleRule();

	Logger::log("%s\n", rule->toString().c_str());
	doNumericalIntegration(rule, first, a, b, intervals);
	doNumericalIntegration(rule, second, a, b, intervals);
	doNumericalIntegration(rule, third, a, b, intervals);

	delete rule;
	delete first;
	delete second;
	delete third;

}



/**
 * Tenta executar a integração numérica utilizando a regra do trapezóide.
 *
 * @see TrapezoidalRule
 */
void playWithTrapezoidalRuleFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	TrapezoidalRule *rule = new TrapezoidalRule();

	Logger::log("%s\n", rule->toString().c_str());
	doNumericalIntegration(rule, first, a, b, intervals);
	doNumericalIntegration(rule, second, a, b, intervals);
	doNumericalIntegration(rule, third, a, b, intervals);

	delete rule;
	delete first;
	delete second;
	delete third;

}



/**
 * Tenta executar a integração numérica utilizando a regra de Simpson.
 *
 * @see SimpsonRule
 */
void playWithSimpsonRuleFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	int intervals = UserParams::getIntParam(INTERVAL__INPUT_MSG);

	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	SimpsonRule *rule = new SimpsonRule();

	Logger::log("%s\n", rule->toString().c_str());
	doNumericalIntegration(rule, first, a, b, intervals);
	doNumericalIntegration(rule, second, a, b, intervals);
	doNumericalIntegration(rule, third, a, b, intervals);

	delete rule;
	delete first;
	delete second;
	delete third;

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
