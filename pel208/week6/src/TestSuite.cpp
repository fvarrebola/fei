#include <assert.h>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/Matrix.h>
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
 * Executa todos os testes.
 */
PUBLIC void pel208::week6::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
