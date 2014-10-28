#include <assert.h>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/Matrix.h>
#include <inc/LDAMethod.h>

#include <inc/tests/SampleDataSets.h>
#include <inc/tests/TestSuite.h>

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week2;

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
}

/**
 * Testa a classe LDAMethod com o primeiro conjunto de amostras.
 */
PRIVATE void pel208::week3::TestSuite::testLDAMethodClassUsingSimpleDataSet() {

	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	
	Logger::log("Testando a classe LDAMethod com as amostras de um conjunto simples...\n");

	if (LDAMethod::evaluate(SampleDataSets::getLDASimpleDS(), 0, &eigenValues, &eigenVectors)) {

		assertCellValue(eigenValues, 0, 0, 12.20066f);
		assertCellValue(eigenValues, 1, 0, 0.0f);

		assertCellValue(eigenVectors, 0, 0, 0.81781);
		assertCellValue(eigenVectors, 0, 1, -0.5759);
		assertCellValue(eigenVectors, 1, 0, 0.5759);
		assertCellValue(eigenVectors, 1, 1, 0.81781);

		delete eigenValues;
		delete eigenVectors;

	}

}

/**
 * Testa a classe LDAMethod com o segundo conjunto de amostras.<br />
 */
PRIVATE void pel208::week3::TestSuite::testLDAMethodClassUsingIrisDataSet() {

	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	
	Logger::log("Testando a classe LDAMethod com as amostras do conjunto iris...\n");

	if (LDAMethod::evaluate(SampleDataSets::getLDAIrisDS(), 0, &eigenValues, &eigenVectors)) {

		assertCellValue(eigenValues, 0, 0, 126.50607f);
		assertCellValue(eigenValues, 1, 0, 1.08806f);
		assertCellValue(eigenValues, 2, 0, 0.0f);
		assertCellValue(eigenValues, 3, 0, 0.0f);

		assertCellValue(eigenVectors, 0, 0, 0.06461f);
		assertCellValue(eigenVectors, 1, 1, 0.78520f);
		assertCellValue(eigenVectors, 2, 2, 0.29407f);
		assertCellValue(eigenVectors, 3, 3, 0.86756f);

		delete eigenValues;
		delete eigenVectors;

	}

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel208::week3::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel208::week3::TestSuite::testLDAMethodClassUsingSimpleDataSet();
	pel208::week3::TestSuite::testLDAMethodClassUsingIrisDataSet();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
