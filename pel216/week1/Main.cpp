#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Menu.h>
#include <inc/Element.h>
#include <inc/Stack.h>
#include <inc/Queue.h>

#include <inc/TestSuite.h>

// definicao de metodos
void playWithStacksAndQueues();

using namespace pel216::commons;
using namespace pel216::week1;

// enum de comandos
enum Commands {
    PLAY_WITH_STACKS_AND_QUEUES    = 0,
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
        PLAY_WITH_STACKS_AND_QUEUES, 
        "Usando pilhas e filas", 
        playWithStacksAndQueues
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

/* menu de operacoes sobre pilhas e filas */
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
 * metodo que ilustra o uso de pilhas e filas.
 */
void playWithStacksAndQueues() {

    Stack *stack = new Stack();
    Queue *queue = new Queue();

    while (true) {
    
        PMENU_OPTION pCommand = pel216::commons::Menu::pickMenuOption(SUBMENU);
        if (pCommand->iOptionId == EXIT) {
            break;
        }
     
        Element *element = NULL;
        switch (pCommand->iOptionId) {
            case DUMP:
                Logger::log("Imprimindo conteudo da pilha...\n");
                stack->dump();
                Logger::log("Imprimindo conteudo da fila...\n");
                queue->dump();
                break;
            case PUSH:
                element = Element::createRandomElement();
                Logger::log("Inserindo mesmo elemento na fila e na pilha...\n> %s\n", 
                        (element ? element->toString().c_str() : UNKNOWN));
                Logger::log("Elemento inserido com %s\n", 
                        (stack->push(element) && queue->push(element) ? "sucesso" : "falha"));
                break;
            case POP:
                Logger::log("Removendo o elemento da fila e da pilha...\nElemento removido com %s\n", 
                        ((stack->pop() && queue->pop()) ? "sucesso" : "falha"));
                break;
            case PEEK:
                element = stack->peek();
                Logger::log("Espiando o topo da pilha...\n> %s\n", 
                        (element ? element->toString().c_str() : UNKNOWN));
                element = queue->peek();
                Logger::log("Espiando o primeiro elemento da fila...\n> %s\n", 
                        (element ? element->toString().c_str() : UNKNOWN));
                break;
            case COUNT:
                Logger::log("O tamanho da pilha eh: %d\n", stack->count());
				Logger::log("O tamanho da fila eh: %d\n", queue->count());
                break;
            case CLEAR:
                Logger::log("Limpando pilha...\n");
                Logger::log("Pilha limpa com %s\n", (stack->clear() ? "sucesso" : "falha"));
                Logger::log("Limpando fila...\n");
                Logger::log("Fila limpa com %s\n", (queue->clear() ? "sucesso" : "falha"));
                break;
        }

    }

}



/**
 * Imprime o cabecalho.
 */
void printHeader() {
    Logger::log("%s\n", STARS);
    Logger::log("* PEL216\n");
    Logger::log("* Semana 1 - Pilhas e filas\n");
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
