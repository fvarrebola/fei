#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>


#include <inc/TestSuite.h>

using namespace pel216::commons;
using namespace pel216::week2;

// enum de comandos
enum Commands {
    PLAY_WITH_SHAPES 				= 0,
    RUN_TESTS                      	= 1,
    EXIT                           = 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
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
    Logger::log("* PEL216\n");
    Logger::log("* Semana 2 - Formas geometricas\n");
    Logger::log("%s\n", STARS);
}



/**
 * Imprime o rodape.
 */
void printFooter() {
    Logger::log("%s\n", STARS);
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
