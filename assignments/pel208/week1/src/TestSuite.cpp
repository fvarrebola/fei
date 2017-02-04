#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/Matrix.h>
#include <inc/LeastSquaresMethod.h>

#include <inc/tests/TestSuite.h>

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week1;

double precision = 0.01;
double bias = 1;

Matrix *xMatrix;
Matrix *yMatrix;

/**
 * Inicializa a matriz de amostras.
 */
PRIVATE void initialize() {

	// valores de x
	xMatrix = new Matrix(10, 2);

	xMatrix->setColumnCellsValue(0, bias);

	xMatrix->data()[0][1] = 69;
	xMatrix->data()[1][1] = 67;
	xMatrix->data()[2][1] = 71;
	xMatrix->data()[3][1] = 65;
	xMatrix->data()[4][1] = 72;
	xMatrix->data()[5][1] = 68;
	xMatrix->data()[6][1] = 74;
	xMatrix->data()[7][1] = 65;
	xMatrix->data()[8][1] = 66;
	xMatrix->data()[9][1] = 72;

	// valores de y
	yMatrix = new Matrix(10, 1);

	yMatrix->data()[0][0] = 9.5;
	yMatrix->data()[1][0] = 8.5;
	yMatrix->data()[2][0] = 11.5;
	yMatrix->data()[3][0] = 10.5;
	yMatrix->data()[4][0] = 11;
	yMatrix->data()[5][0] = 7.5;
	yMatrix->data()[6][0] = 12;
	yMatrix->data()[7][0] = 7;
	yMatrix->data()[8][0] = 7.5;
	yMatrix->data()[9][0] = 13;

}

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
		assert((matrix->data()[row][column] - value) < precision);
	}
}

/**
 * Testa a classe @link{Matrix}.
 */
PRIVATE void pel208::week1::TestSuite::testMatrixClass() {

	Logger::log("Testando classe Matrix...\n");

	initialize();

	// X^T
	Matrix *x_t = xMatrix->transpose();

	// X * X^T
	Matrix *x___times___x_t = x_t->multiply(xMatrix);
	assertCellValue(x___times___x_t, 0, 0, 10);
	assertCellValue(x___times___x_t, 0, 1, 689);
	assertCellValue(x___times___x_t, 1, 0, 689);
	assertCellValue(x___times___x_t, 1, 1, 47565);

	// X^T * Y
	Matrix *x_t___times___y = x_t->multiply(yMatrix);
	assertCellValue(x_t___times___y, 0, 0, 98);
	assertCellValue(x_t___times___y, 1, 0, 6800);

	// (X * X^T) ^ -1
	Matrix *inverted = NULL;
	x___times___x_t->invert(&inverted);
	assertCellValue(inverted, 0, 0, 51.2);
	assertCellValue(inverted, 0, 1, -0.7417);
	assertCellValue(inverted, 1, 0, -0.7417);
	assertCellValue(inverted, 1, 1, 0.0108);

	// B
	Matrix *beta_approx = inverted->multiply(x_t___times___y);
	assertCellValue(beta_approx, 0, 0, -25.65);
	assertCellValue(beta_approx, 1, 0, 0.5145);

	// 60-feet estimation
	Matrix target(1, 2);
	target.data()[0][0] = 1;
	target.data()[0][1] = 60;

	Matrix *estimate = target.multiply(beta_approx);
	assertCellValue(estimate, 0, 0, 5.22);

	delete beta_approx;
	delete inverted;
	delete x_t___times___y;
	delete x___times___x_t;
	delete x_t;
	delete xMatrix;
	delete yMatrix;

}

/**
 * Testa a classe @link{LeastSquaresMethod}.
 */
PRIVATE void pel208::week1::TestSuite::testLeastSquaresMethodClass() {

	Logger::log("Testando classe LeastSquaresMethod...\n");

	initialize();

	Matrix target(1, 1);
	target.data()[0][0] = 60;

	LeastSquaresMethod *lsm = new LeastSquaresMethod(xMatrix, yMatrix);
	assert((lsm->evaluate(&target) -  5.22) < precision);

	delete lsm;

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel208::week1::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel208::week1::TestSuite::testMatrixClass();
	pel208::week1::TestSuite::testLeastSquaresMethodClass();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
