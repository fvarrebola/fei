#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/tests/TestSuiteWeek5.h>

#include <inc/functions/FirstFunction.h>
#include <inc/functions/SecondFunction.h>
#include <inc/functions/ThirdFunction.h>

#include <inc/optimization/GradientDescent.h>

using namespace pel216::commons;
using namespace pel216::week5;

/**
 * Testa a classe FirstFunction.
 */
PRIVATE void pel216::week5::TestSuite::testFirstFunctionClass() {

	double x0 = 2.0f;

	GradientDescent *gd = new GradientDescent();
	FirstFunction *func = new FirstFunction(x0);
	double beta = 0.1f;
	while (beta < 1.01f) {
		gd->evaluate(func, beta);
		beta += 0.1f;
	}

}

/**
 * Testa a classe SecondFunction.
 */
PRIVATE void pel216::week5::TestSuite::testSecondFunctionClass() {

	double x0 = 2.0f;

	GradientDescent *gd = new GradientDescent();
	SecondFunction *func = new SecondFunction(x0);
	double beta = 0.1f;
	while (beta < 1.01f) {
		gd->evaluate(func, beta);
		beta += 0.1f;
	}

}

/**
 * Testa a classe ThirdFunction.
 */
PRIVATE void pel216::week5::TestSuite::testThirdFunctionClass() {

	double x0 = 0.0f;
	double y0 = 0.5f;

	GradientDescent *gd = new GradientDescent();
	ThirdFunction  *func = new ThirdFunction (x0, y0);
	double beta = 0.1f;
	while (beta < 1.01f) {
		gd->evaluate(func, beta);
		beta += 0.1f;
	}

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week5::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week5::TestSuite::testFirstFunctionClass();
	pel216::week5::TestSuite::testSecondFunctionClass();
	pel216::week5::TestSuite::testThirdFunctionClass();

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
