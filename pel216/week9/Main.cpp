#include <mpi.h>

#include <assert.h>

#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

// pel216::week6
#include <inc/functions/FirstFunction.h>
#include <inc/functions/SecondFunction.h>
#include <inc/functions/ThirdFunction.h>

#include <inc/integration/RectangleRule.h>
#include <inc/integration/TrapezoidalRule.h>
#include <inc/integration/SimpsonRule.h>
#include <inc/integration/AdaptativeQuadrature.h>

// pel216::week7
#include <inc/functions/FirstFunctionWeek7.h>
#include <inc/functions/SecondFunctionWeek7.h>
#include <inc/functions/ThirdFunctionWeek7.h>

#include <inc/integration/MonteCarloRule.h>
#include <inc/geometry/ToroidVolumeCalculator.h>

#define MASTER								0

#define NEWTON_COATES_STRING_FORMAT			"RANK #%-2d:\t%-26s\t%-26s\t%.9f\n"
#define MONTE_CARLO_STRING_FORMAT			"RANK #%-2d:\t%-26s\t%.9f\n"
#define TOROID_MC_STRING_FORMAT				"RANK #%-2d:\t%06.2f%%\t%08.6f\t%012.9f\n"
#define RESULT_STRING_FORMAT				"> %-61s %015.12f\n"

// o intervalo de integração [a, b]
static double a = 0;
static double b = 1;

// a quantidade de intervalos para os métodos Newton-Coates
static double INTERVALS = std::pow(10, 6);

// a quantidade de amostras para os métodos de Monte Carlo
static double SAMPLES = std::pow(10, 6);

// variáveis globais de identificação do rank do nó e do número de tarefas
int rank = -1;
int tasks = 0;

using namespace pel216::commons;
using namespace pel216::week6;
using namespace pel216::week7;

/**
 * Imprime o cabecalho.
 */
void printHeader() {

	if (rank != MASTER) {
		return;
	}

    Logger::log("%s\n", STARS);
    Logger::log("* PEL216\n");
    Logger::log("* Semana 9 - Uso de MPI na integracao numerica\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {

	if (rank != MASTER) {
		return;
	}

	Logger::log("%s\n", STARS);

}

/**
 * Determina se um código de retorno da biblioteca MPI é <code>MPI_SUCCESS</code>.<br />
 *
 * @param rc
 *				o <code>int</code> que representa o código de erro
 */
static void assertMPIReturnCode(int rc) {
	assert(rc == MPI_SUCCESS);
}

/**
 * Tenta executar a integração numérica utilizando os métodos de Newton-Coates.<br />
 * Aqui, os nós executam seus cálculos de maneira independente, cada um para um pedaço do intervalo e, ao final, o nó mestre armazena a somatória.<br />
 * 
 * @param function
 *				o @link{pel216::week6::Function} que representa a função a ser integrada
 * @param debug
 *				indica se os valores obtidos em cada um dos nós deve ser salvo em arquivo
 */
void playWithNewtonCoatesIntegration(pel216::week6::Function *function, bool debug = false) {
	
	double interval = (b - a);
	double increment = (interval / (tasks * 1.0f));
	double a_prime = a + (increment * rank);
	double b_prime = a_prime + increment;

	double rectRuleSum = 0.0f;
	double trapRuleSum = 0.0f;
	double simpsonRuleSum = 0.0f;

	RectangleRule *rectRule = new RectangleRule();
	double rectRuleResult = rectRule->evaluate(function, a_prime, b_prime, INTERVALS);
	assertMPIReturnCode(MPI_Reduce(&rectRuleResult, &rectRuleSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	TrapezoidalRule *trapRule = new TrapezoidalRule();
	double trapRuleResult = trapRule->evaluate(function, a_prime, b_prime, INTERVALS);
	assertMPIReturnCode(MPI_Reduce(&trapRuleResult, &trapRuleSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	SimpsonRule *simpsonRule = new SimpsonRule();
	double simpsonRuleResult = simpsonRule->evaluate(function, a_prime, b_prime, INTERVALS);
	assertMPIReturnCode(MPI_Reduce(&simpsonRuleResult, &simpsonRuleSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	if (debug) {
		Logger::logToFile(NEWTON_COATES_STRING_FORMAT, 
				rank, function->toString().c_str(), rectRule->toString().c_str(), rectRuleResult);
		Logger::logToFile(NEWTON_COATES_STRING_FORMAT, 
				rank, function->toString().c_str(), trapRule->toString().c_str(), trapRuleResult);
		Logger::logToFile(NEWTON_COATES_STRING_FORMAT, 
				rank, function->toString().c_str(), simpsonRule->toString().c_str(), simpsonRuleResult);
	}

	if (rank == MASTER) {
		Logger::log("\n");
		Logger::log("Integracao numerica Newton-Coates:\n");
		Logger::log("> Funcao: %s\n", function->toString().c_str());
		Logger::log(RESULT_STRING_FORMAT, rectRule->toString().c_str(), rectRuleSum);
		Logger::log(RESULT_STRING_FORMAT, trapRule->toString().c_str(), trapRuleSum);
		Logger::log(RESULT_STRING_FORMAT, simpsonRule->toString().c_str(), rectRuleSum);
		Logger::log("\n");
	}

	delete rectRule;
	delete trapRule;
	delete simpsonRule;

}

/**
 * Tenta executar a integração numérica utilizando os métodos de Newton-Coates.<br />
 *
 * @param debug
 *				indica se os valores obtidos em cada um dos nós deve ser salvo em arquivo
 */
void playWithNewtonCoatesIntegration(bool debug = false) {

	Function *f1 = new pel216::week6::FirstFunction();
	playWithNewtonCoatesIntegration(f1, debug);
	delete f1;

	Function *f2 = new pel216::week6::SecondFunction();
	playWithNewtonCoatesIntegration(f2, debug);
	delete f2;

	Function *f3 = new pel216::week6::ThirdFunction();
	playWithNewtonCoatesIntegration(f3, debug);
	delete f3;

}

/**
 * Tenta executar a integração numérica utilizando os métodos de Monte Carlo.<br />
 * Aqui, os nós executam seus cálculos de maneira independente e, ao final, o nó mestre calcula um média simples.<br />
 *
 * @param debug
 *				indica se os valores obtidos em cada um dos nós deve ser salvo em arquivo
 */
void playWithMonteCarloIntegration(bool debug = false) {

	double f1MCSum = 0.0f;
	double f2MCSum = 0.0f;
	double f3MCSum = 0.0f;

	MonteCarloRule *rule = new MonteCarloRule();

	Function *f1 = new pel216::week7::FirstFunction();
	double f1Result = rule->evaluate(f1, a, b, SAMPLES);
	assertMPIReturnCode(MPI_Reduce(&f1Result, &f1MCSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	Function *f2 = new pel216::week7::SecondFunction();
	double f2Result = rule->evaluate(f2, a, b, SAMPLES);
	assertMPIReturnCode(MPI_Reduce(&f2Result, &f2MCSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	Function *f3 = new pel216::week7::ThirdFunction();
	double f3Result = rule->evaluate(f3, a, b, SAMPLES);
	assertMPIReturnCode(MPI_Reduce(&f3Result, &f3MCSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	if (debug) {
		Logger::logToFile(MONTE_CARLO_STRING_FORMAT, rank, f1->toString().c_str(), f1Result);
		Logger::logToFile(MONTE_CARLO_STRING_FORMAT, rank, f2->toString().c_str(), f2Result);
		Logger::logToFile(MONTE_CARLO_STRING_FORMAT, rank, f3->toString().c_str(), f3Result);
	}

	if (rank == MASTER) {
		Logger::log("\n");
		Logger::log("Integracao numerica Monte Carlo:\n");
		Logger::log("> Metodo: %s\n", rule->toString().c_str());
		Logger::log(RESULT_STRING_FORMAT, f1->toString().c_str(), (f1MCSum / (tasks * 1.0f)));
		Logger::log(RESULT_STRING_FORMAT, f2->toString().c_str(), (f2MCSum / (tasks * 1.0f)));
		Logger::log(RESULT_STRING_FORMAT, f3->toString().c_str(), (f3MCSum / (tasks * 1.0f)));
		Logger::log("\n");
	}

	delete f1;
	delete f2;
	delete f3;
}

/**
 * Tenta executar o cálculo de volume de um toróide.<br />
 * Aqui, os nós executam seus cálculos de maneira independente e, ao final, o nó mestre calcula um média simples.<br />
 *
 * @param debug
 *				indica se os valores obtidos em cada um dos nós deve ser salvo em arquivo
 */
void playWithToroidVolumeCalculation(bool debug = false) {

	double massSum = 0.0f;
	double errorSum = 0.0f;
	double hitCountSum = 0.0f;

	ToroidVolumeCalculator *rule = new ToroidVolumeCalculator();
	Function *function = new pel216::week7::ToroidFunction();
	rule->evaluate(function, DEFAULT_TOROID_ENCLOSING_CUBE_VOLUME, DEFAULT_TOROID_BOUNDS, SAMPLES);

	double mass = rule->getMass();
	double error = rule->getError();
	double hitCount = rule->getHitCountAsPercentage();

	assertMPIReturnCode(MPI_Reduce(&mass, &massSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));
	assertMPIReturnCode(MPI_Reduce(&error, &errorSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));
	assertMPIReturnCode(MPI_Reduce(&hitCount, &hitCountSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD));

	if (debug) {
		Logger::logToFile(TOROID_MC_STRING_FORMAT, rank, hitCount, mass, error);
	}

	if (rank == MASTER) {
		Logger::log("\n");
		Logger::log("Calculo do volume do toroide:\n");
		Logger::log("> Funcao: %s\n", function->toString().c_str());
		Logger::log(RESULT_STRING_FORMAT, "Massa", (massSum / (tasks * 1.0f)));
		Logger::log(RESULT_STRING_FORMAT, "Erro", (errorSum / (tasks * 1.0f)));
		Logger::log(RESULT_STRING_FORMAT, "Acertos", (hitCountSum / (tasks * 1.0f)));
		Logger::log("\n");
	}

	delete function;

}

/*
 * Ponto de entrada.
 */
int main(int argc, char** argv) {

	// inicializando a biblioteca MPI
	assertMPIReturnCode(MPI_Init(&argc, &argv));

	// obtendo o id atual
	assertMPIReturnCode(MPI_Comm_rank(MPI_COMM_WORLD, &rank));
	assertMPIReturnCode(MPI_Comm_size(MPI_COMM_WORLD, &tasks));

    printHeader();

	// realiza as integrações para as funções 1, 2 e 3 da week6
	playWithNewtonCoatesIntegration(true);

	// realiza as integrações para as funções 1, 2 e 3 da week7
	playWithMonteCarloIntegration(true);

	// realiza o cálculo de volume para o toróide
	playWithToroidVolumeCalculation(true);

	// finalizando a biblioteca MPI
	assertMPIReturnCode(MPI_Finalize());

	printFooter();

}
