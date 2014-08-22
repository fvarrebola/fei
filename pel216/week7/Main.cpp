#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/functions/FirstFunctionWeek7.h>
#include <inc/functions/SecondFunctionWeek7.h>
#include <inc/functions/ThirdFunctionWeek7.h>

#include <inc/integration/MonteCarloRule.h>
#include <inc/geometry/ToroidVolumeCalculator.h>

#include <inc/tests/TestSuiteWeek7.h>

#define A___INPUT_MSG							"Informe o ponto inicial (a)    [dbl]"
#define B___INPUT_MSG							"Informe o ponto final   (b)    [dbl]"
#define MAX_SAMPLES__INPUT_MSG					"Informe a qtde max de amostras [int]"
#define STEP_COUNT__INPUT_MSG					"Informe o incremento (am*=inc) [int]"

#define PLEASE_CONSIDER_MORE_SAMPLES_ERROR_MSG	"Por favor considere mais que 10 amostras\n"
#define PLEASE_CONSIDER_FEWER_SAMPLES_ERROR_MSG	"Por favor considere menos que %d amostras\n"
#define PLEASE_CONSIDER_MORE_STEPS_ERROR_MSG	"Por favor considere um incremento maior que %d\n"
#define PLEASE_CONSIDER_FEWER_STEPS_ERROR_MSG	"Por favor considere um incremento menor que %d\n"

void playWithFirstFunction();
void playWithSecondFunction();
void playWithThirdFunction();
void playWithToroidFunction();

using namespace pel216::commons;
using namespace pel216::week6;
using namespace pel216::week7;

// enum de comandos
enum Commands {
	PLAY_WITH_FIRST_FUNCTION		= 0,
	PLAY_WITH_SECOND_FUNCTION		= 1,
	PLAY_WITH_THIRD_FUNCTION		= 2,
	PLAY_WITH_TOROID_FUNCTION		= 3,
    RUN_TESTS                      	= 4,
    EXIT                           	= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_FIRST_FUNCTION,
		"Integrar a funcao sqrt(x)",
		playWithFirstFunction
	},	
	{
		PLAY_WITH_SECOND_FUNCTION,
		"Integrar a funcao 4/(1 + x^2)",
		playWithSecondFunction
	},
	{
		PLAY_WITH_THIRD_FUNCTION,
		"Integrar a funcao sqrt(x + sqrt(x))",
		playWithThirdFunction
	},
	{
		PLAY_WITH_TOROID_FUNCTION,
		"Encontrar o volume do toroide z^2 + (sqrt(x^2 + y^2) - 2)^2 <= 1",
		playWithToroidFunction
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
    Logger::log("* Semana 7 - Metodo de integracao Monte Carlo\n");
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
 * @param intervals 
 *				o <code>size_t</code> que indica a quantidade de intervalos
 */
void printFunctionHeader(Function *function, double a, double b, size_t intervals) {

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Funcao: %s\n", function->toString().c_str());
	Logger::log("*   intervalo [a=%.2f, b=%.2f]\n", a, b);
	Logger::log("*   integracao precisa: %0.12f\n", function->evaluatePreciseIntegration(a, b));
	Logger::log("*   amostras a considerar: %d\n", intervals);
	Logger::log("%s\n", STARS);

}



/**
 * Obtém a quantidade máxima de amostras.
 *
 * @return o <code>size_t</code> que representa a quantidade máxima de amostras
 */
size_t getMaxSamples() {
	
	size_t maxSamples = 0;

	bool isValid = false;
	while (!isValid) {
		maxSamples = UserParams::getIntParam(MAX_SAMPLES__INPUT_MSG);
		if (maxSamples < 10) {
			Logger::log(PLEASE_CONSIDER_MORE_SAMPLES_ERROR_MSG);
		} else if (maxSamples > pel216::week7::MAX_SAMPLES) {
			Logger::log(PLEASE_CONSIDER_FEWER_SAMPLES_ERROR_MSG, pel216::week7::MAX_SAMPLES);
		} else {
			isValid = true;
		}
	}

	return maxSamples;

}
	
	
	
/**
 * Obtém o incremento de amostras.
 * 
 * @param maxSamples
 *				o <code>size_t</code> que representa a quantidade máxima de amostras
 *
 * @return o <code>size_t</code> que representa o incremento de amostras
 */
size_t getStepCount(size_t maxSamples) {
	
	size_t stepCount = 0;

	bool isValid = false;
	while (!isValid) {
		stepCount = UserParams::getIntParam(STEP_COUNT__INPUT_MSG);
		if (stepCount < MIN_STEP_COUNT) {
			Logger::log(PLEASE_CONSIDER_MORE_STEPS_ERROR_MSG, MIN_STEP_COUNT);
		} else if (stepCount >= maxSamples) {
			Logger::log(PLEASE_CONSIDER_FEWER_STEPS_ERROR_MSG, maxSamples);
		} else {
			isValid = true;
		}
	}

	return stepCount;

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
 * @param maxSamples 
 *				o <code>size_t</code> que indica a quantidade máxima de amostras
 * @param stepCount 
 *				o <code>size_t</code> que indica o incremento de amostras
 */
void doNumericalIntegration(IntegrationRule *rule, Function *function, double a, double b, size_t maxSamples = -1, size_t stepCount = 10) {

	Logger::log("> %s\n", rule->toString().c_str());

	Logger::log("  -------- ------------ ------------ ------------\n");
	Logger::log("  QTDE     VALOR        EA           ER          \n");
	Logger::log("  -------- ------------ ------------ ------------\n");

	for (size_t idx = 1; idx < maxSamples + 1; idx *= stepCount) {
		register double result = rule->evaluate(function, a, b, idx);
		Logger::log("  %-8d %012.9f %012.9f %012.9f\n", idx, result, rule->getAbsoluteError(), rule->getRelativeError());
	}

	Logger::log("  -------- ------------ ------------ ------------\n");

}

/**
* Tenta executar a integração numérica para a função @link{FirstFunction}.
*/
void playWithFirstFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	size_t maxSamples = getMaxSamples();
	size_t stepCount = getStepCount(maxSamples);

	MonteCarloRule *rule = new MonteCarloRule();
	FirstFunction *function = new FirstFunction();
	printFunctionHeader(function, a, b, maxSamples);
	doNumericalIntegration(rule, function, a, b, maxSamples, stepCount);

	Logger::log("%s\n", STARS);

	delete rule;
	delete function;

}



/**
 * Tenta executar a integração numérica para a função @link{SecondFunction}.
 */
void playWithSecondFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	size_t maxSamples = getMaxSamples();
	size_t stepCount = getStepCount(maxSamples);

	MonteCarloRule *rule = new MonteCarloRule();
	SecondFunction *function = new SecondFunction();
	printFunctionHeader(function, a, b, maxSamples);
	doNumericalIntegration(rule, function, a, b, maxSamples, stepCount);

	Logger::log("%s\n", STARS);

	delete rule;
	delete function;

}



/**
 * Tenta executar a integração numérica para a função @link{ThirdFunction}.
 */
void playWithThirdFunction() {

	double a = UserParams::getDoubleParam(A___INPUT_MSG);
	double b = UserParams::getDoubleParam(B___INPUT_MSG);
	size_t maxSamples = getMaxSamples();
	size_t stepCount = getStepCount(maxSamples);

	MonteCarloRule *rule = new MonteCarloRule();
	ThirdFunction *function = new ThirdFunction();
	printFunctionHeader(function, a, b, maxSamples);
	doNumericalIntegration(rule, function, a, b, maxSamples, stepCount);

	Logger::log("%s\n", STARS);

	delete rule;
	delete function;

}



/**
 * Tenta executar o cálculo de volume com a função @link{ToroidFunction}.
 */
void playWithToroidFunction() {

	size_t maxSamples = getMaxSamples();
	size_t stepCount = getStepCount(maxSamples);

	ToroidFunction *function = new ToroidFunction();
	ToroidVolumeCalculator *calculator = new ToroidVolumeCalculator();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Funcao: %s\n", function->toString().c_str());
	Logger::log("*   intervalo da aproximacao [a=%d, b=%d]\n", 10, maxSamples);
	Logger::log("*   incremento (amostras *= incremento): %d\n", stepCount);
	Logger::log("%s\n", STARS);

	Logger::log(" -------- ------- --------- -------- ------------------------------------\n");
	Logger::log(" QTDE     %%       VALOR     ERRO     CENTRO DE MASSA                      \n");
	Logger::log(" -------- ------- --------- -------- ------------------------------------\n");

	for (size_t idx = 10; idx < maxSamples + 1; idx *= stepCount) {

		calculator->evaluate(
				function, DEFAULT_TOROID_ENCLOSING_CUBE_VOLUME, DEFAULT_TOROID_BOUNDS, idx);

		register double mass = calculator->getMass();
		register double error = calculator->getError();
		register double hitCount = calculator->getHitCountAsPercentage();
		pel216::week7::CENTER_OF_MASS centerOfMass = calculator->getCenterOfMass();

		Logger::log(" %-8d %06.2f%% %08.6f %08.6f (x=%+8.6f,y=%+8.6f,z=%+8.6f)\n", 
				idx, hitCount, mass, error, centerOfMass.x, centerOfMass.y, centerOfMass.z);

	}
	Logger::log(" -------- ------- --------- -------- ------------------------------------\n");

	Logger::log("%s\n", STARS);

	delete calculator;
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
