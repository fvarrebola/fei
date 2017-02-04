#include <assert.h>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/Matrix.h>
#include <inc/NaiveBayesMethod.h>

#include <inc/tests/SampleDataSets.h>
#include <inc/tests/TestSuite.h>

using namespace pel216::commons;
using namespace pel208::commons;

double precision = 0.01;

/**
 * Verifica se o valor de uma célula está de acordo com o determinado.
 *
 * @param matrix
 * @param row
 * @param columns
 * @param value
 */
PRIVATE static void assertCellValue(Matrix *matrix, size_t row, size_t column, double value = 0.0f) {
	
	if (pel216::commons::Utils::isValidHandle(matrix)) {
		assert((row < matrix->getRows()) && (column < matrix->getColumns()));
		assert((matrix->data()[row][column] - value) < precision);
	}

};

/**
 * Testa a classe BayesNaiveMethod com o conjunto de amostras "play tennis".<br />
 */
PRIVATE void pel208::week4::TestSuite::testNaiveBayesMethodClassUsingPlayTennisDS() {

	Logger::log("Testando o conjunto de dados \"play tennis?\"...\n");

	Matrix *ds = SampleDataSets::getNaiveBayesPlayTennisDS();

	NaiveBayes *nb = new NaiveBayes();
	assert(nb->buildModel(ds, 4));
	delete ds;

	Matrix *m = new Matrix(1, 4);
	m->data()[0][0] = 0; m->data()[0][1] = 2; m->data()[0][2] = 0; m->data()[0][3] = 1;
	
	Matrix *h = NULL;
	assert(nb->evaluate(m, &h));

	assertCellValue(h, 0, 1, 0.02057f);
	assertCellValue(h, 1, 1, 0.00529f);

	delete h;
	delete m;
	delete nb;

};


/**
 * Testa a classe BayesNaiveMethod com o conjunto de amostras "mau pagador".<br />
 */
PRIVATE void pel208::week4::TestSuite::testNaiveBayesMethodClassUsingFirstDS() {

	Logger::log("Testando o conjunto de dados \"mau pagador?\"...\n");

	Matrix *ds = SampleDataSets::getNaiveBayesFirstDS();
	NaiveBayes *nb = new NaiveBayes();
	assert(nb->buildModel(ds, 3));
	delete ds;

	Matrix *m = new Matrix(1, 3);
	m->data()[0][0] = 1; m->data()[0][1] = 2; m->data()[0][2] = 1;

	Matrix *h = NULL;
	assert(nb->evaluate(m, &h));

	assertCellValue(h, 0, 1, 0.00612f);
	assertCellValue(h, 1, 1, 0.10000f);

	delete h;
	delete m;
	delete nb;

};

/**
 * Testa a classe BayesNaiveMethod com o conjunto de amostras "tipo do celular".<br />
 */
PRIVATE void pel208::week4::TestSuite::testNaiveBayesMethodClassUsingSecondDS() {

	Logger::log("Testando o conjunto de dados \"tipo celular?\"...\n");
	
	Matrix *ds = SampleDataSets::getNaiveBayesSecondDS();
	NaiveBayes *nb = new NaiveBayes();
	assert(nb->buildModel(ds, 1));
	delete ds;

	Matrix *m = new Matrix(1, 1);
	m->data()[0][0] = 1;

	Matrix *h = NULL;
	assert(nb->evaluate(m, &h));

	assertCellValue(h, 0, 1, 0.2f);
	assertCellValue(h, 1, 1, 0.4f);

	delete h;
	delete m;
	delete nb;

};

/**
 * Executa todos os testes.
 */
PUBLIC void pel208::week4::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel208::week4::TestSuite::testNaiveBayesMethodClassUsingPlayTennisDS();
	pel208::week4::TestSuite::testNaiveBayesMethodClassUsingFirstDS();
	pel208::week4::TestSuite::testNaiveBayesMethodClassUsingSecondDS();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
