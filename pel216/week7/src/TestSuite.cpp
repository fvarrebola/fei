#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/functions/FirstFunctionWeek7.h>
#include <inc/functions/SecondFunctionWeek7.h>
#include <inc/functions/ThirdFunctionWeek7.h>
#include <inc/functions/ToroidFunction.h>

#include <inc/integration/MonteCarloRule.h>
#include <inc/geometry/ToroidVolumeCalculator.h>

#include <inc/tests/TestSuiteWeek7.h>

using namespace pel216::commons;
using namespace pel216::week6;
using namespace pel216::week7;

// qtde m�xima de amostras para os testes
static const double maxTestSamples = std::pow(10, 6);

// constantes para os testes com a integra��o num�rica de fun��es
static double a = 0.0f;
static double b = 1.0f;
static double precision = 0.6f;
static double toroid_precision = 5.0f;

/**
 * Verifica se a integra��o num�rica foi bem sucedida.
 *
 * @param rule
 *				o @link{IntegrationRule} que representa a regra a ser utilizada
 * @param function
 *				o @link{Function} que representa a fun��o a ser integrada
 * @param expectedValue
 *				o <code>double</code> que representa o valor esperado para a integra��o
 */
void assertNumericalIntegration(IntegrationRule *rule, Function *function, double expectedValue = 0.0f) {
	
	Logger::log("> Funcao: %s\n", function->toString().c_str());
	Logger::log("  > intervalo [a=%.2f, b=%.2f]\n", a, b);
	Logger::log("  > integracao precisa: %02.9f\n", function->evaluatePreciseIntegration(a, b));

	Logger::log("  ------- ------------ ------------ ------------ ----------\n");
	Logger::log("  QTDE    VALOR        EA           ER           RESULTADO\n");
	Logger::log("  ------- ------------ ------------ ------------ ----------\n");

	for (double samples = 10.0f; samples < maxTestSamples; samples *= 10.0f) {
		register double result = rule->evaluate(function, a, b, samples);
		register bool expression = (std::abs(result - expectedValue) < precision);
		Logger::log("  %-7.0f %012.9f %012.9f %012.9f ", samples, result, rule->getAbsoluteError(), rule->getRelativeError());
		Logger::logWithoutTimestamp("[%s]\n", expression ? "OK" : "FALHA");
		assert(expression);
	}
	
	Logger::log("  ------- ------------ ------------ ------------ ----------\n");
	Logger::log("\n");

}

/**
 * Testa a classe MonteCarloRule.
 */
PRIVATE void pel216::week7::TestSuite::testMonteCarloRuleClass() {

	Logger::log("Testando o metodo de Monte Carlo (classe MonteCarloRule)...\n");

	MonteCarloRule *rule = new MonteCarloRule();
	
	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	assertNumericalIntegration(rule, first, 0.6f);
	assertNumericalIntegration(rule, second, 3.0f);
	assertNumericalIntegration(rule, third, 1.0f);

	delete rule;
	delete first;
	delete second;
	delete third;

	Logger::log("\n");
	
}

/**
 * Testa a classe ToroidVolumeCalculator.
 */
PRIVATE void pel216::week7::TestSuite::testToroidVolumeCalculatorClass() {

	Logger::log("Testando o calculo de volume do toroide (classe ToroidVolumeCalculator)...\n");

	ToroidFunction *function = new ToroidFunction();
	ToroidVolumeCalculator *calculator = new ToroidVolumeCalculator();

	// o valor preciso � inferior a (V/2 - 2*pi)
	// onde V = 2 * pi^2 * R * r^2, com R = 3 e r = 1
	double approxExpectedValue = ((std::pow(pel216::commons::pi, 2.0f) * 3.0f) - (2.0f * pel216::commons::pi));

	Logger::log("\n");
	Logger::log("> Funcao: %s\n", function->toString().c_str());
	Logger::log("  ------- ------- --------- -------- ----------------------------- ----------\n");
	Logger::log("  QTDE    %%       VOLUME    ERRO     CENTRO DE MASSA               RESULTADO\n");
	Logger::log("  ------- ------- --------- -------- ----------------------------- ----------\n");

	for (double samples = 10.0f; samples < maxTestSamples; samples *= 10.0f) {

		calculator->evaluate(function, DEFAULT_TOROID_ENCLOSING_CUBE_VOLUME, DEFAULT_TOROID_BOUNDS, samples);

		register double mass = calculator->getMass();
		register double error = calculator->getError();
		register double hitCount = calculator->getHitCountAsPercentage();
		pel216::week7::CENTER_OF_MASS centerOfMass = calculator->getCenterOfMass();

		// o resultado obtido � verificado apenas se o hit count for maior do que 50%
		register bool expression = (hitCount > 50.0f) ? ((std::abs(mass - approxExpectedValue) < toroid_precision) ? true : false) : true;

		Logger::log("  %-7.0f %06.2f%% %08.6f %08.6f %+8.6f,%+8.6f,%+8.6f ", 
				samples, hitCount, mass, error, centerOfMass.x, centerOfMass.y, centerOfMass.z);
		Logger::logWithoutTimestamp("[%s]\n", expression ? "OK" : "FALHA");

		assert(expression);

	}

	Logger::log("  ------- ------- --------- -------- ----------------------------- ----------\n");

	delete calculator;

	Logger::log("\n");
	
}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week7::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week7::TestSuite::testMonteCarloRuleClass();
	pel216::week7::TestSuite::testToroidVolumeCalculatorClass();

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
