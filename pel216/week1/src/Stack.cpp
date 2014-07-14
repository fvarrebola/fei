#include <inc/Utils.h>
#include <inc/Stack.h>

/**
 * Construtor.
 */
PUBLIC pel216::week1::Stack::Stack() : Collection() {

}



/**
 * Destrutor.
 */
PUBLIC pel216::week1::Stack::~Stack() {

}



/**
 * Adiciona um elemento ao topo da pilha.
 *
 * @param element
 *				o <code>Element</code> que representa o elemento
 *
 * @return o <code>true</code> caso o elemento tenha sido adicionado com sucesso
 */
PROTECTED bool pel216::week1::Stack::add(IN Element *element) {

	bool added = false;

	if (pel216::commons::Utils::isInvalidHandle(element)) {
		return added;
	}

	if (!isEmpty() && pel216::commons::Utils::isInvalidHandle(getFirstElement())) {
		return added;
	}

	if (this->size < MAX_SIZE) {
		this->size++;
		for (int idx = this->size; idx != ZERO; idx--) {
			this->collection[idx] = this->collection[idx - 1];
		}
		this->collection[ZERO] = element->clone();
		added = true;
	}

	return added;

}



/**
 * Remove um elemento do topo da pilha.
 *
 * @return o <code>true</code> caso o elemento tenha sido removido com sucesso
 */
PROTECTED bool pel216::week1::Stack::remove() {

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
 * Insere um elemento no topo da pilha.
 *
 * @param element
 *				o <code>Element</code> que representa o elemento
 *
 * @return o <code>true</code> caso a insercao tenha sido bem sucedida; do contrario <code>false</code>
 */
PUBLIC bool pel216::week1::Stack::push(IN Element *element) {
	return this->add(element);
}



/**
 * Remove o elemento do topo da pilha.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Stack::pop() {
	
	Element *element = peek();
	if (!this->remove()) {
		element = NULL;
	}

	return element;

}



/**
 * Obtem o elemento do topo da pilha sem removê-lo.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Stack::peek() {
	
	Element *element = this->getFirstElement();
	return (pel216::commons::Utils::isValidHandle(element) ? element->clone() : NULL);

}
