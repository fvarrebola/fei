#include <assert.h>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/Matrix.h>
#include <inc/Jacobi.h>
#include <inc/PCAMethod.h>

#include <inc/tests/TestSuite.h>

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week2;

double precision = 0.01;

Matrix *dataset1;
Matrix *dataset2;

/**
 * Inicializa a matriz de amostras com n=2.
 */
PRIVATE void init1stDataSet() {

	dataset1 = new Matrix(10, 2);

	// valores de x
	dataset1->data()[0][0] = 2.5f;
	dataset1->data()[1][0] = 0.5f;
	dataset1->data()[2][0] = 2.2f;
	dataset1->data()[3][0] = 1.9f;
	dataset1->data()[4][0] = 3.1f;
	dataset1->data()[5][0] = 2.3f;
	dataset1->data()[6][0] = 2.0f;
	dataset1->data()[7][0] = 1.0f;
	dataset1->data()[8][0] = 1.5;
	dataset1->data()[9][0] = 1.1;

	// valores de y
	dataset1->data()[0][1] = 2.4f;
	dataset1->data()[1][1] = 0.7f;
	dataset1->data()[2][1] = 2.9f;
	dataset1->data()[3][1] = 2.2f;
	dataset1->data()[4][1] = 3.0f;
	dataset1->data()[5][1] = 2.7f;
	dataset1->data()[6][1] = 1.6f;
	dataset1->data()[7][1] = 1.1f;
	dataset1->data()[8][1] = 1.6f;
	dataset1->data()[9][1] = 0.9f;

}

/**
 * Inicializa a matriz de amostras com n=4.
 */
PRIVATE void init2ndDataSet() {

	dataset2 = new Matrix(13, 4);

	dataset2->data()[0][0] = 7;
	dataset2->data()[0][1] = 26;
	dataset2->data()[0][2] = 6;
	dataset2->data()[0][3] = 60; 
	//dataset2->data()[0][4] = 78.5f;
	dataset2->data()[1][0] =  1;
	dataset2->data()[1][1] =  29;
	dataset2->data()[1][2] =  15;
	dataset2->data()[1][3] =  52; 
	//dataset2->data()[1][4] = 74.3;
	dataset2->data()[2][0] =  11;
	dataset2->data()[2][1] =  56;
	dataset2->data()[2][2] =  8;
	dataset2->data()[2][3] =  20; 
	//dataset2->data()[2][4] = 104.3;
	dataset2->data()[3][0] =  11;
	dataset2->data()[3][1] =  31;
	dataset2->data()[3][2] =  8;
	dataset2->data()[3][3] =  47; 
	//dataset2->data()[3][4] = 87.6;
	dataset2->data()[4][0] =  7;
	dataset2->data()[4][1] =  52;
	dataset2->data()[4][2] =  6;
	dataset2->data()[4][3] =  33; 
	//dataset2->data()[4][4] = 95.9;
	dataset2->data()[5][0] =  11;
	dataset2->data()[5][1] =  55;
	dataset2->data()[5][2] =  9;
	dataset2->data()[5][3] =  22; 
	//dataset2->data()[5][4] = 109.2;
	dataset2->data()[6][0] =  3;
	dataset2->data()[6][1] =  71;
	dataset2->data()[6][2] =  17;
	dataset2->data()[6][3] =  6; 
	//dataset2->data()[6][4] = 102.7;
	dataset2->data()[7][0] =  1;
	dataset2->data()[7][1] =  31;
	dataset2->data()[7][2] =  22;
	dataset2->data()[7][3] =  44; 
	//dataset2->data()[7][4] = 72.5;
	dataset2->data()[8][0] =  2;
	dataset2->data()[8][1] =  54;
	dataset2->data()[8][2] =  18;
	dataset2->data()[8][3] =  22; 
	//dataset2->data()[8][4] = 93.1;
	dataset2->data()[9][0] =  21;
	dataset2->data()[9][1] =  47;
	dataset2->data()[9][2] =  4;
	dataset2->data()[9][3] =  26; 
	//dataset2->data()[9][4] = 115.9;
	dataset2->data()[10][0] =  1;
	dataset2->data()[10][1] =  40;
	dataset2->data()[10][2] =  23;
	dataset2->data()[10][3] =  34; 
	//dataset2->data()[10][4] = 83.8;
	dataset2->data()[11][0] =  11;
	dataset2->data()[11][1] =  66;
	dataset2->data()[11][2] =  9;
	dataset2->data()[11][3] =  12; 
	//dataset2->data()[11][4] = 113.3;
	dataset2->data()[12][0] =  10;
	dataset2->data()[12][1] =  68;
	dataset2->data()[12][2] =  8;
	dataset2->data()[12][3] =  12;
	//dataset2->data()[12][4] = 109.4;

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
		assert((row < matrix->getRows()) && (column < matrix->getColumns()));
		assert((matrix->data()[row][column] - value) < precision);
	}
}

/**
 * Testa matriz com o primeiro conjunto de amostras.<br />
 */
PRIVATE void pel208::week2::TestSuite::testMatrixClassUsing1stDataSet() {

	Logger::log("Testando classe MatrixMethod  com dataset #1...\n");

	// calculando a matriz de covariância
	Matrix *adjusted = NULL;
	Matrix *covariate = dataset1->covariate(&adjusted);

	assertCellValue(adjusted, 0, 0, 0.69f);
	assertCellValue(adjusted, 0, 1, 0.49f);

	assertCellValue(covariate, 0, 0, 0.6165f);
	assertCellValue(covariate, 0, 1, 0.6154f);
	assertCellValue(covariate, 1, 0, 0.6165f);
	assertCellValue(covariate, 1, 1, 0.7165f);

	// calculando as matrizes de auto valores e auto vetores
	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	assert(Jacobi::evaluate(covariate, &eigenValues, &eigenVectors));

	assertCellValue(eigenValues,  0, 0,  1.2840f);
	assertCellValue(eigenValues,  1, 0,	 0.0490f);
	assertCellValue(eigenVectors, 0, 0,  0.6778f);
	assertCellValue(eigenVectors, 0, 1,  0.7351f);
	assertCellValue(eigenVectors, 1, 0,  0.7351f);
	assertCellValue(eigenVectors, 1, 1,  -0.6778f);

	delete eigenVectors;
	delete eigenValues;
	delete covariate;
	delete adjusted;

}

/**
 * Testa matriz com o segundo conjunto de amostras.<br />
 */
PRIVATE void pel208::week2::TestSuite::testMatrixClassUsing2ndDataSet() {

	Logger::log("Testando classe MatrixMethod com dataset #2...\n");

	// calculando a matriz de covariância
	Matrix *adjusted = NULL;
	Matrix *covariate = dataset2->covariate(&adjusted);

	assertCellValue(covariate, 0, 0, 34.6026f);
	assertCellValue(covariate, 1, 1, 242.1410f);
	assertCellValue(covariate, 2, 2, 41.0256f);
	assertCellValue(covariate, 3, 3, 280.1667f);

	// calculando as matrizes de auto valores e auto vetores
	Matrix *eigenValues = NULL;
	Matrix *eigenVectors = NULL;
	assert(Jacobi::evaluate(covariate, &eigenValues, &eigenVectors));

	assertCellValue(eigenValues,  3, 0,	 0.23715f);
	assertCellValue(eigenValues,  2, 0,  12.40543f);
	assertCellValue(eigenValues,  1, 0,	 67.49644f);
	assertCellValue(eigenValues,  0, 0,  517.79688f);

	assertCellValue(eigenVectors, 3, 3,  0.506180f);
	assertCellValue(eigenVectors, 2, 2,  0.543969f);
	assertCellValue(eigenVectors, 1, 1,  0.755310f);
	assertCellValue(eigenVectors, 0, 0,  0.730874f);

	delete eigenVectors;
	delete eigenValues;
	delete covariate;
	delete adjusted;

}

/**
 * Testa a classe PCAMethod com o primeiro conjunto de amostras.
 */
PRIVATE void pel208::week2::TestSuite::testPCAMethodClassUsing1stDataSet() {

	Logger::log("Testando classe PCAMethod usando dataset #1...\n");

	Matrix *pca = NULL;
	assert(PCAMethod::evaluate(dataset1, &pca));

	assertCellValue(pca,  0,  0,  0.82797f);
	assertCellValue(pca,  0,  1,  0.17512f);
	assertCellValue(pca,  9,  0, -1.22382f); 
	assertCellValue(pca,  9,  1,  0.16268f);

	delete pca;

}

/**
 * Testa a classe PCAMethod com o segundo conjunto de amostras.
 */
PRIVATE void pel208::week2::TestSuite::testPCAMethodClassUsing2ndDataSet() {

	Logger::log("Testando classe PCAMethod usando dataset #2...\n");

	Matrix *pca = NULL;
	assert(PCAMethod::evaluate(dataset2, &pca));

	assertCellValue(pca,  0,  0,  32.80144f);
	assertCellValue(pca,  0,  1,  12.41585f);    
	assertCellValue(pca,  0,  2,   1.04881f);   
	assertCellValue(pca,  0,  3,  13.89613f);

	assertCellValue(pca,  12,  0, -19.96598f);
	assertCellValue(pca,  12,  1, -13.04835f);
	assertCellValue(pca,  12,  2,   7.30453f);
	assertCellValue(pca,  12,  3, -10.78262f);

	delete pca;

}

/**
 * Executa todos os testes.
 */
PUBLIC void pel208::week2::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	init1stDataSet();
	init2ndDataSet();
	
	pel208::week2::TestSuite::testMatrixClassUsing1stDataSet();
	pel208::week2::TestSuite::testMatrixClassUsing2ndDataSet();

	pel208::week2::TestSuite::testPCAMethodClassUsing1stDataSet();
	pel208::week2::TestSuite::testPCAMethodClassUsing2ndDataSet();

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
