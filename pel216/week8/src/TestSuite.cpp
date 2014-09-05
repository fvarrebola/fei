#include <assert.h>
#include <vector>
#include <cstdlib>

#include <inc/Utils.h>
#include <inc/Logger.h>

#include <inc/BookAttendGrade.h>
#include <inc/CSVFileReader.h>
#include <inc/NearestNeighbor.h>

#include <inc/tests/TestSuite.h>

using namespace pel216::commons;
using namespace pel216::week8;

static double precision = 0.1f;

static std::list<BookAttendGrade> SAMPLES;

/**
 * Constrói uma lista de amostras.
 */
void buildSamples() {
	SAMPLES.push_back(BookAttendGrade(0, 9, 45));
	SAMPLES.push_back(BookAttendGrade(1, 15, 57));
	SAMPLES.push_back(BookAttendGrade(0, 10, 45));
	SAMPLES.push_back(BookAttendGrade(2, 16, 51));
	SAMPLES.push_back(BookAttendGrade(4, 10, 65));
	SAMPLES.push_back(BookAttendGrade(4, 20, 88));
	SAMPLES.push_back(BookAttendGrade(1, 11, 44));
	SAMPLES.push_back(BookAttendGrade(4, 20, 87));
	SAMPLES.push_back(BookAttendGrade(3, 15, 89));
	SAMPLES.push_back(BookAttendGrade(0, 15, 59));
	SAMPLES.push_back(BookAttendGrade(2, 8, 66));
	SAMPLES.push_back(BookAttendGrade(1, 13, 65));
	SAMPLES.push_back(BookAttendGrade(4, 18, 56));
	SAMPLES.push_back(BookAttendGrade(1, 10, 47));
	SAMPLES.push_back(BookAttendGrade(0, 8, 66));
	SAMPLES.push_back(BookAttendGrade(1, 10, 41));
	SAMPLES.push_back(BookAttendGrade(3, 16, 56));
	SAMPLES.push_back(BookAttendGrade(0, 11, 37));
	SAMPLES.push_back(BookAttendGrade(1, 19, 45));
	SAMPLES.push_back(BookAttendGrade(4, 12, 58));
	SAMPLES.push_back(BookAttendGrade(4, 11, 47));
	SAMPLES.push_back(BookAttendGrade(0, 19, 64));
	SAMPLES.push_back(BookAttendGrade(2, 15, 97));
	SAMPLES.push_back(BookAttendGrade(3, 15, 55));
	SAMPLES.push_back(BookAttendGrade(1, 20, 51));
	SAMPLES.push_back(BookAttendGrade(0, 6, 61));
	SAMPLES.push_back(BookAttendGrade(3, 15, 69));
	SAMPLES.push_back(BookAttendGrade(3, 19, 79));
	SAMPLES.push_back(BookAttendGrade(2, 14, 71));
	SAMPLES.push_back(BookAttendGrade(2, 13, 62));
	SAMPLES.push_back(BookAttendGrade(3, 17, 87));
	SAMPLES.push_back(BookAttendGrade(2, 20, 54));
	SAMPLES.push_back(BookAttendGrade(2, 11, 43));
	SAMPLES.push_back(BookAttendGrade(3, 20, 92));
	SAMPLES.push_back(BookAttendGrade(4, 20, 83));
	SAMPLES.push_back(BookAttendGrade(4, 20, 94));
	SAMPLES.push_back(BookAttendGrade(3, 9, 60));
	SAMPLES.push_back(BookAttendGrade(1, 8, 56));
	SAMPLES.push_back(BookAttendGrade(2, 16, 88));
	SAMPLES.push_back(BookAttendGrade(0, 10, 62));
};

/**
 * Verifica se a integração numérica foi bem sucedida.
 *
 * @param rule
 *				o @link{NearestNeighbor} que representa a regra a ser utilizada
 * @param function
 *				o @link{Function} que representa a função a ser integrada
 * @param expectedValue
 *				o <code>double</code> que representa o valor esperado para a integração
 */
void assertKNN(NearestNeighbor *method, BookAttendGrade *target, size_t neighbors = 1, double expectedValue = 0.0f) {

	double result = method->evaluate((*target), neighbors);
	bool assertion = (std::abs(result - expectedValue) < precision);

	Logger::log(" %s %2d %02.9f [%s]\n", target->toString().c_str(), neighbors, result, (assertion) ? "OK" : "FALHA");

	assert(assertion);

};


PRIVATE void pel216::week8::TestSuite::testNearestNeighborClass() {

	Logger::log("Testando o metodo de Nearest Neighbor (classe NearestNeighbor)...\n");

	buildSamples();

	NearestNeighbor *method = new NearestNeighbor(SAMPLES);

	const int TARGETS = 4;
	const int NEIGHBOR_COUNT = 5;
	size_t neighbors[NEIGHBOR_COUNT] = {1, 2, 3, 5, 10};

	Logger::log("\n");
	Logger::log(" ALVO         K  VALOR        RESULTADO\n");
	Logger::log(" ------------ -- ------------ ----------\n");

	BookAttendGrade target_0_5(0, 5);
	double expectedValues[TARGETS][NEIGHBOR_COUNT] = {
		{61.00f, 63.50f, 61.00f, 58.80f, 54.90f},
		{88.00f, 87.50f, 86.00f, 88.80f, 77.10f},
		{47.00f, 44.00f, 43.60f, 47.00f, 51.80f},
		{89.00f, 72.00f, 71.00f, 73.20f, 72.50f}
	};

	for (size_t idx = 0; idx < NEIGHBOR_COUNT; idx++) {
		assertKNN(method, &target_0_5, neighbors[idx], expectedValues[0][idx]);			
	}

	BookAttendGrade target_4_20(4, 20);
	for (size_t idx = 0; idx < NEIGHBOR_COUNT; idx++) {
		assertKNN(method, &target_4_20, neighbors[idx],expectedValues[1][idx]);			
	}

	BookAttendGrade target_2_10(2, 10);
	for (size_t idx = 0; idx < NEIGHBOR_COUNT; idx++) {
		assertKNN(method, &target_2_10, neighbors[idx], expectedValues[2][idx]);			
	}

	BookAttendGrade target_4_15(4, 15);
	for (size_t idx = 0; idx < NEIGHBOR_COUNT; idx++) {
		assertKNN(method, &target_4_15, neighbors[idx], expectedValues[3][idx]);			
	}

	Logger::log(" ------------ -- ------------ ----------\n");

	delete method;

};


/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week8::TestSuite::run() {
	
	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("Iniciando execucao dos testes unitarios...\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

	pel216::week8::TestSuite::testNearestNeighborClass();

	Logger::log("%s\n", STARS);
	Logger::log("Todos os testes foram executados com sucesso\n");
	Logger::log("%s\n", STARS);
	Logger::log("\n");

}
