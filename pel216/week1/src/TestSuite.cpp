#include <assert.h>

#include <inc/Utils.h>
#include <inc/TestSuite.h>

using namespace pel216::commons;
using namespace pel216::week1;

/**
 * Testa os metodos da classe Utils.
 */
PRIVATE void pel216::week1::TestSuite::testUtilsClass() {
	
	Logger::log("Testando classe pel216::week1::Utils...\n");

	PVOID pbData = NULL;
	unsigned long cbData = 1000;

	Logger::log("Testando pel216::week1::Utils::createPtr()...\n");
	assert(Utils::createPtr(cbData, &pbData));

	Logger::log("Testando pel216::week1::Utils::isValidHandle()...\n");
	assert(Utils::isValidHandle(pbData));

	Logger::log("Testando pel216::week1::Utils::destroyPtr()...\n");
	assert(Utils::destroyPtr(pbData, cbData));

	Logger::log("Testando pel216::week1::Utils::isInvalidHandle()...\n");
	assert(Utils::isInvalidHandle(NULL));

}



/**
 * Testa os metodos da classe Element.
 */
PRIVATE void pel216::week1::TestSuite::testElementClass() {
	
	Logger::log("Testando classe pel216::week1::Element...\n");

	unsigned long cbData = 10;
	char *pbData = NULL;
	Utils::createRandomData(cbData, &pbData);

	Element *element = new Element();

	Logger::log("Testando pel216::week1::Element::setData()...\n");
	assert(element->setData(pbData, cbData));

	Logger::log("Testando pel216::week1::Element::getDataLen()...\n");
	unsigned long cbDataFromObj = element->getDataLen();
	assert(cbData == cbDataFromObj);

	Logger::log("Testando pel216::week1::Element::getData()...\n");
	char *pbDataFromObj = (char*)element->getData();
	for (unsigned long idx = 0; idx < cbDataFromObj; idx++) {
		assert(pbData[idx] == pbDataFromObj[idx]);
	}
	
	delete element;

	assert(Utils::destroyPtr(pbData, cbData));

}



/**
 * Testa os metodos da classe Stack.
 */
PRIVATE void pel216::week1::TestSuite::testStackClass() {

	Stack *stack = new Stack();

	Logger::log("Testando pel216::week1::Stack::push()...\n");
	
	static int SIZE = 10;
	for (int idx = 0; idx < SIZE; idx++) {
		Element *element = Element::createRandomElement();
		assert(stack->push(element));
		delete element;
	}

	Logger::log("Testando pel216::week1::Stack::count()...\n");
	assert(stack->count() == SIZE);

	Logger::log("Testando pel216::week1::Stack::dump()...\n");
	stack->dump();

	Logger::log("Testando pel216::week1::Stack::pop()...\n");
	Element *poppedElement = stack->pop();
	assert(Utils::isValidHandle(poppedElement));
	assert(stack->count() == SIZE - 1);
	Logger::log("> %s\n", poppedElement->toString().c_str());
	stack->dump();

	Logger::log("Testando pel216::week1::Stack::peek()...\n");
	Element *peekedElement = stack->peek();
	assert(Utils::isValidHandle(peekedElement));
	assert(stack->count() == SIZE - 1);
	Logger::log("> %s\n", peekedElement->toString().c_str());
	stack->dump();

	Logger::log("Testando pel216::week1::Stack::search()...\n");
	assert(stack->search(poppedElement) == -1);
	assert(stack->search(peekedElement) == 1);

	delete stack;

}



/**
 * Testa os metodos da classe Queue.
 */
PRIVATE void pel216::week1::TestSuite::testQueueClass() {

	Queue *queue = new Queue();

	Logger::log("Testando pel216::week1::Queue::push()...\n");
	
	static int SIZE = 10;
	for (int idx = 0; idx < SIZE; idx++) {
		Element *element = Element::createRandomElement();
		assert(queue->push(element));
		delete element;
	}

	Logger::log("Testando pel216::week1::Queue::count()...\n");
	assert(queue->count() == SIZE);

	Logger::log("Testando pel216::week1::Queue::dump()...\n");
	queue->dump();

	Logger::log("Testando pel216::week1::Queue::pop()...\n");
	Element *poppedElement = queue->pop();
	assert(Utils::isValidHandle(poppedElement));
	assert(queue->count() == SIZE - 1);
	Logger::log("> %s\n", poppedElement->toString().c_str());
	queue->dump();

	Logger::log("Testando pel216::week1::Queue::peek()...\n");
	Element *peekedElement = queue->peek();
	assert(Utils::isValidHandle(peekedElement));
	assert(queue->count() == SIZE - 1);
	Logger::log("> %s\n", peekedElement->toString().c_str());
	queue->dump();

	Logger::log("Testando pel216::week1::Queue::search()...\n");
	assert(queue->search(poppedElement) == -1);
	assert(queue->search(peekedElement) == 1);

	delete queue;

}



/**
 * Executa todos os testes.
 */
PUBLIC void pel216::week1::TestSuite::run() {
	
	Logger::log("Iniciando execucao dos testes unitarios...\n");

	TestSuite::testUtilsClass();
	TestSuite::testElementClass();
	TestSuite::testStackClass();
	TestSuite::testQueueClass();

	Logger::log("Todos os testes foram executados com sucesso\n");

}
