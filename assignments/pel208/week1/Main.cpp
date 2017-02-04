#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/UserParams.h>

#include <inc/BookAttendGrade.h>
#include <inc/CSVFileReader.h>

#include <inc/Matrix.h>
#include <inc/LeastSquaresMethod.h>

#include <inc/tests/TestSuite.h>

#define SAMPLES_FILE___INPUT_MSG				"Informe o caminho para as amostras "
#define BOILING_POINT___INPUT_MSG				"Informe a temperatura de ebulicao  "
#define BOOKS___INPUT_MSG						"Informe a quantidade de livros     "
#define CLASSES___INPUT_MSG						"Informe a quantidade de aulas      "

using namespace pel216::commons;

using namespace pel208::commons;
using namespace pel208::week1;

void playWithAlpsWater();
void playWithBooksAttendanceAndGrades();

// enum de comandos
enum Commands {
	PLAY_WITH_ALPS_WATER					= 0,
	PLAY_WITH_BOOKS_ATTENDANCE_AND_GRADES	= 1,
    RUN_TESTS                      			= 2,
    EXIT                           			= 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_ALPS_WATER,
		"Solucionar problema do ponto de ebulicao e pressao",
		playWithAlpsWater,
	},	
	{
		PLAY_WITH_BOOKS_ATTENDANCE_AND_GRADES,
		"Solucionar problema de livros, presencas e notas",
		playWithBooksAttendanceAndGrades,
	},
	{
		RUN_TESTS,
		"Executar testes",
		TestSuite::run
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
    Logger::log("* Semana 1 - Least Squares Method\n");
    Logger::log("%s\n", STARS);
}

/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
}

/**
 * Manipula os dados de temperatura e pressão da ebulição da água nos Alpes.
 */
void playWithAlpsWater() {

	std::string filePath = UserParams::getStringParam(SAMPLES_FILE___INPUT_MSG);

	// carrega o arquivo de amostras
	std::list<BoiolingPointPressure> samples = CSVFileReader::loadAsBoiolingPointPressure(filePath.c_str());
	if (samples.size() == 0) {
		return;
	}

	Matrix *xMatrix = new Matrix(samples.size(), 2); 
	Matrix *yMatrix = new Matrix(samples.size(), 1); 

	size_t idx = 0;
	for (std::list<BoiolingPointPressure>::iterator iterator = samples.begin(); 
			iterator != samples.end(); 
			++iterator) {
		xMatrix->data()[idx][1] = iterator->getBoilingPoint();
		yMatrix->data()[idx][0] = iterator->getPressure();
		idx++;
	}

	// obtém os parâmetros de entrada do usuário final
	double boilingPoint = UserParams::getDoubleParam(BOILING_POINT___INPUT_MSG);

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Temperatura de ebulicao: %f\n", boilingPoint);
	Logger::log("%s\n", STARS);

	Matrix target(1, 1);
	target.data()[0][0] = boilingPoint;

	LeastSquaresMethod *lsm = new LeastSquaresMethod(xMatrix, yMatrix);
	Logger::log("PRESSAO: %9.6f\n", lsm->evaluate(&target, true));
	
	Logger::log("%s\n", STARS);

	delete lsm;
	delete yMatrix;
	delete xMatrix;

}

/**
 * Manipula os dados de livros emprestados, presenças em aula e notas.
 */
void playWithBooksAttendanceAndGrades() {

	std::string filePath = UserParams::getStringParam(SAMPLES_FILE___INPUT_MSG);
	
	// carrega o arquivo de amostras
	std::list<BookAttendGrade> samples = CSVFileReader::loadAsBookAttendGrade(filePath.c_str());

	Matrix *xMatrix = new Matrix(samples.size(), 3); 
	Matrix *yMatrix = new Matrix(samples.size(), 1); 

	size_t idx = 0;
	for (std::list<BookAttendGrade>::iterator iterator = samples.begin(); 
			iterator != samples.end(); 
			++iterator) {

		xMatrix->data()[idx][1] = iterator->getBooks();
		xMatrix->data()[idx][2] = iterator->getAttendance();
		yMatrix->data()[idx][0] = iterator->getGrade();
		idx++;
		
	}

	// obtém os parâmetros de entrada do usuário final
	size_t books = UserParams::getIntParam(BOOKS___INPUT_MSG);
	size_t classes = UserParams::getIntParam(CLASSES___INPUT_MSG);

	Logger::log("\n");
	Logger::log("%s\n", STARS);
	Logger::log("* Livros: %d\n", books);
	Logger::log("* Aulas: %d\n", classes);
	Logger::log("%s\n", STARS);

	Matrix target(1, 2);
	target.data()[0][0] = books;
	target.data()[0][1] = classes;

	LeastSquaresMethod *lsm = new LeastSquaresMethod(xMatrix, yMatrix);
	Logger::log("NOTA: %9.6f\n", lsm->evaluate(&target, true));
	
	Logger::log("%s\n", STARS);

	delete lsm;
	delete yMatrix;
	delete xMatrix;

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
