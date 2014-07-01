#include <inc/Utils.h>
#include <inc/Queue.h>

/**
 * Construtor.
 */
PUBLIC pel216::week1::Queue::Queue() : Collection() {

}



/**
 * Destrutor.
 */
PUBLIC pel216::week1::Queue::~Queue() {

}



/**
 * Adiciona um elemento ao fim na fila.
 *
 * @param element
 *				o <code>Element</code> que representa o elemento
 *
 * @return o <code>true</code> caso o elemento tenha sido adicionado com sucesso
 */
PROTECTED bool pel216::week1::Queue::add(IN Element *element) {

	bool added = false;

	if (pel216::commons::Utils::isInvalidHandle(element)) {
		return added;
	}

	if (this->size < MAX_SIZE - 1) {
		this->collection[this->size++] = element->clone();
		added = true;
	}

	return added;

}



/**
 * Remove um elemento do comeco da fila.
 *
 * @return o <code>true</code> caso o elemento tenha sido removido com sucesso
 */
PROTECTED bool pel216::week1::Queue::remove() {

	bool removed = false;

	if (isEmpty()) {
		return removed;
	}

	Element *element = getFirstElement();
	if (pel216::commons::Utils::isValidHandle(element)) {

		delete element;

		for (int idx = ONE; idx < MAX_SIZE; idx++) {
			this->collection[idx - 1] = this->collection[idx];
		}
		
		this->size--;
		removed = true;

	}

	return removed;

}



/**
 * Insere um elemento no final da fila.
 *
 * @param element
 *				o <code>Element</code> que representa o elemento
 *
 * @return o <code>true</code> caso a insersao tenha sido bem sucedida; do contrario <code>false</code>
 */
PUBLIC bool pel216::week1::Queue::push(IN Element *element) {
	return this->add(element);
}



/**
 * Remove o elemento do comeco da fila.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Queue::pop() {

	Element *element = peek();
	if (!this->remove()) {
		element = NULL;
	}

	return element;

}



/**
 * Obtem o elemento do comeco da fila sem removê-lo.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Queue::peek() {

	Element *element = this->getFirstElement();
	return (pel216::commons::Utils::isValidHandle(element) ? element->clone() : NULL);

}
