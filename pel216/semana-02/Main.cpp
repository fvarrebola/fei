#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>


#include <inc/TestSuite.h>

using namespace pel216::commons;
using namespace pel216::week2;

void playWithShapes();

// enum de comandos
enum Commands {
    PLAY_WITH_SHAPES    			= 0,
    RUN_TESTS                      = 1,
    DUMP                           = 10,
    PUSH                           = 11,
    POP                            = 12,
    PEEK                           = 13,
    COUNT                          = 14,
    CLEAR                          = 15,
    EXIT                           = 99
};

/* menu principal */
MENU_OPTION MAIN_MENU[] = {
	{
		PLAY_WITH_SHAPES,
		"Usando formas geometricas",
		playWithShapes
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

/* menu de operacoes sobre formas */
MENU_OPTION SUBMENU[] = {
    {DUMP,   "Exibe",           NULL},
    {PUSH,   "Insere (push)",   NULL},
    {POP,    "Remove (pop)",    NULL},
    {PEEK,   "Espia  (peek)",   NULL},
    {COUNT,  "Conta  (count)",  NULL},
    {CLEAR,  "Limpa  (clear)",  NULL},
    {EXIT,   "Sair",            NULL},
    {-1, NULL, NULL}
};




/**
 * Metodo que ilustra o uso de formas geometricas.
 */
void playWithShapes() {

}



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
