#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/Matrix.h>
#include <inc/NaiveBayesMethod.h>

#include <inc/tests/SampleDataSets.h>
#include <inc/tests/TestSuite.h>

#define OUTLOOK___INPUT_MSG						"Tempo ensolarado (0), nublado (1) ou chuvoso (2)?"
#define TEMP___INPUT_MSG						"Temperatura quente (0), media (1) ou fria (2)?"
#define HUMIDITY___INPUT_MSG					"Umidade alta (0) ou normal (1)?"
#define WIND___INPUT_MSG						"Vento fraco (0) ou forte (1)?"
#define PLAY_TENNIS_RESULT						"Nao jogar (0) ou jogar (1)"

#define HOUSE_OWNER___INPUT_MSG					"Casa propria (0) ou nao (1)?"
#define MARTIAL_STATS___INPUT_MSG				"Solteiro (0), casado (1) ou divorciado (2)?"
#define INCOME___INPUT_MSG						"Alto (0), medio (1) ou baixo (2)?"
#define RISK_RESULT								"Bom pagador (0) ou mau pagador (1)"

#define LAPTOP___INPUT_MSG						"PC (0) ou MAC (1)?"
#define PHONE_RESULT							"Android (0), iPhone (1)?"

#define DEBUG___INPUT_MSG						"Imprimir o conteudo das matrizes?"

using namespace pel216::commons;
using namespace pel208::commons;
using namespace pel208::week4;

void playWithTennisDataSet();
void playWithFirstDataSet();
void playWithSecondDataSet();

// enum de comandos
enum Commands {
	PLAY_WITH_TENNIS_DATA_SET				= 0,
	PLAY_WITH_FIRST_DATA_SET				= 1,
	PLAY_WITH_SECOND_DATA_SET				= 2,
    RUN_TESTS                      			= 3,
    EXIT                           			= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_TENNIS_DATA_SET,
		"Analise do conjunto de dados do \"play tennis\"",
		playWithTennisDataSet,
	},
	{
		PLAY_WITH_FIRST_DATA_SET,
		"Analise do conjunto de dados do \"mau pagador\"",
		playWithFirstDataSet,
	},
	{
		PLAY_WITH_SECOND_DATA_SET,
		"Analise do conjunto de dados do \"tipo do celular\"",
		playWithSecondDataSet,
	},
	{
		RUN_TESTS,
		"Executar testes",
		pel208::week4::TestSuite::run
	},
    {
        EXIT,        
        "Sair",                
        NULL
    },
    {-1, NULL, NULL}
};

/**
 * Imprime o cabecalho.
 */
void printHeader() {
    Logger::log("%s\n", STARS);
    Logger::log("* PEL208\n");
    Logger::log("* Semana 4 - Naive Bayes\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Analise as amostras do conjunto de dados do "mau pagador".<br />
 */
void playWithTennisDataSet() {

	Matrix *m = new Matrix(1, 4);
	m->data()[0][0] = UserParams::getIntParam(OUTLOOK___INPUT_MSG);
	m->data()[0][1] = UserParams::getIntParam(TEMP___INPUT_MSG);
	m->data()[0][2] = UserParams::getIntParam(HUMIDITY___INPUT_MSG);
	m->data()[0][3] = UserParams::getIntParam(WIND___INPUT_MSG);

	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	NaiveBayes *nb = new NaiveBayes();
	Matrix *ds = SampleDataSets::getNaiveBayesPlayTennisDS();
	nb->buildModel(ds, 4, debug);

	Matrix *h = NULL;
	nb->evaluate(m, &h, debug);

	h->dump(PLAY_TENNIS_RESULT);

	delete h;
	delete m;
	delete nb;

}

/**
 * Analise as amostras do conjunto de dados do "mau pagador".<br />
 */
void playWithFirstDataSet() {

	Matrix *m = new Matrix(1, 3);
	m->data()[0][0] = UserParams::getIntParam(HOUSE_OWNER___INPUT_MSG);
	m->data()[0][1] = UserParams::getIntParam(MARTIAL_STATS___INPUT_MSG);
	m->data()[0][2] = UserParams::getIntParam(INCOME___INPUT_MSG);

	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	NaiveBayes *nb = new NaiveBayes();
	Matrix *ds = SampleDataSets::getNaiveBayesFirstDS();
	nb->buildModel(ds, 3, debug);

	Matrix *h = NULL;
	nb->evaluate(m, &h, debug);

	h->dump(RISK_RESULT);

	delete h;
	delete m;
	delete nb;

}

/**
 * Analise as amostras do conjunto de dados do "tipo do celular".<br />
 */
void playWithSecondDataSet() {

	Matrix *m = new Matrix(1, 1);
	m->data()[0][0] = UserParams::getIntParam(LAPTOP___INPUT_MSG);

	bool debug = UserParams::getBoolParam(DEBUG___INPUT_MSG);

	NaiveBayes *nb = new NaiveBayes();
	Matrix *ds = SampleDataSets::getNaiveBayesSecondDS();
	nb->buildModel(ds, 1, debug);

	Matrix *h = NULL;
	nb->evaluate(m, &h, debug);

	h->dump(PHONE_RESULT);

	delete h;
	delete m;
	delete nb;

}

/**
 * Ponto de entrada.
 */
int main(int argc, char** argv) {
	
	printHeader();

    bool shouldContinue = true;
    while (shouldContinue) {
	        PMENU_OPTION pCommand = pel216::commons::Menu::pickMenuOption(MAIN_MENU);
        shouldContinue = (pCommand && pCommand->iOptionId != EXIT);
        if (shouldContinue) {
            pCommand->pfnFunction();
        }
    }

    printFooter();

}
