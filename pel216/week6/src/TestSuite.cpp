#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/functions/FirstFunction.h>
#include <inc/functions/SecondFunction.h>
#include <inc/functions/ThirdFunction.h>

#include <inc/integration/RectangleRule.h>
#include <inc/integration/TrapezoidalRule.h>
#include <inc/integration/SimpsonRule.h>

#include <inc/tests/TestSuiteWeek6.h>

using namespace pel216::commons;
using namespace pel216::week6;


double a = 0.0f;
double b = 1.0f;
size_t intervals = 10;
double precision = 0.00001f;

/**
 * Verifica se a integra��o num�rica foi bem sucedida.
 *
 * @param rule
 *				o @link{IntegrationRule} que representa a regra a ser utilizada
 * @param function
 *				o @link{Function} que representa a fun��o a ser integrada
 */
void assertNumericalIntegration(IntegrationRule *rule, Function *function, double expectedValue) {
	assert(std::abs(rule->evaluate(function, a, b, intervals) - expectedValue) < precision);
}


/**
 * Testa a classe RectangleRule.
 */
PRIVATE void pel216::week6::TestSuite::testRectangleRuleClass() {

	Logger::log("Testando o metodo do retangulo (classe RectangleRule)...\n");

	RectangleRule *rule = new RectangleRule();
	
	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();
	
	assertNumericalIntegration(rule, first, 1.71757f);
	assertNumericalIntegration(rule, second, 0.788103f);
	assertNumericalIntegration(rule, third, 0.747131f);

	delete rule;
	delete first;
	delete second;
	delete third;

}

/**
 * Testa a classe TrapezoidalRule.
 */
PRIVATE void pel216::week6::TestSuite::testTrapezoidalRuleClass() {

	Logger::log("Testando o metodo do trapezoide (classe TrapezoidalRule)...\n");

	TrapezoidalRule *rule = new TrapezoidalRule();

	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	assertNumericalIntegration(rule, first, 1.71971f);
	assertNumericalIntegration(rule, second, 0.77613f);
	assertNumericalIntegration(rule, third, 0.746211f);

	delete rule;
	delete first;
	delete second;
	delete third;

}

/**
 * Testa a classe SimpsonRule.
 */
PRIVATE void pel216::week6::TestSuite::testSimpsonRuleClass() {

	Logger::log("Testando o metodo de Simpson (classe SimpsonRule)...\n");

	SimpsonRule *rule = new SimpsonRule();

	FirstFunction *first = new FirstFunction();
	SecondFunction *second = new SecondFunction();
	ThirdFunction *third = new ThirdFunction();

	assertNumericalIntegration(rule, first, 1.71828f);
	assertNumericalIntegration(rule, second, 0.784112f);
	assertNumericalIntegration(rule, third, 0.746824f);

	delete rule;
	delete first;
	delete second;
	delete third;

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week6::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week6::TestSuite::testRectangleRuleClass();
	pel216::week6::TestSuite::testTrapezoidalRuleClass();
	pel216::week6::TestSuite::testSimpsonRuleClass();

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
