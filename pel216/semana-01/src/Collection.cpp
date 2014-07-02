#include <iostream>

#include <inc/Utils.h>
#include <inc/Collection.h>

/**
 * Construtor.
 */
PUBLIC pel216::week1::Collection::Collection() {

	this->size = 0;
	for (int idx = 0; idx < MAX_SIZE; idx++) {
		this->collection[idx] = NULL;
	}
	this->type = UNDEFINED;
}



/**
 * Destrutor.
 */
PUBLIC pel216::week1::Collection::~Collection() {
	for (int idx = 0; idx < MAX_SIZE; idx++) {
		Element *element = this->collection[idx];
		if (pel216::commons::Utils::isValidHandle(element)) {
			delete element;
		}
		this->collection[idx] = NULL;
	}
	this->size = 0;
}



/**
 * Obtem um elemento na colecao de uma determinada posicao.
 *
 * @param position
 *				o <code>int</code> que representa a posicao
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Collection::getNthElement(IN int position) {
	return ((position > 0 && position < MAX_SIZE + 1) ? this->collection[position - 1] : NULL);
}



/**
 * Obtem o primeiro elemento da colecao.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Collection::getFirstElement() {
	return getNthElement(ONE);
}



/**
 * Obtem o ultimo elemento da colecao.
 *
 * @return o <code>Element</code> que representa o elemento
 */
PUBLIC pel216::week1::Element *pel216::week1::Collection::getLastElement() {
	return getNthElement(this->size);
}



/**
 * Limpa a colecao, removendo todos os elementos.
 *
 * @return o <code>true</code> caso a colecao tenha sido limpa com sucesso
 */
PUBLIC bool pel216::week1::Collection::clear() {

	bool removed = true;
	while (!isEmpty() && removed) {
		removed = this->remove();
	}

	return removed;

}



/**
 * Busca um elemento na colecao.
 *
 * @param element
 *				o <code>Element</code> que representa o elemento
 *
 * @return o <code>int</code> que representa a posicao do elemento na colecao
 */
PUBLIC int pel216::week1::Collection::search(IN pel216::week1::Element *element) {

	int position = -1;

	if (pel216::commons::Utils::isInvalidHandle(element)) {
		return position;
	}

	bool found = false;
	for (int idx = 0; idx < this->size && !found; idx++) {
		Element *el = this->collection[idx];
		if (element->equals(el)) {
			position = idx + 1;
			found = true;
		}
	}

	return position;
}



/**
 * Imprime o conteúdo de uma colecao.
 */
PUBLIC void pel216::week1::Collection::dump() {

	if (this->size == 0) {
		pel216::commons::Logger::log("[colecao vazia]\n");
		return;
	}

	pel216::commons::Logger::log("[t: %d,\n", this->size);
	pel216::commons::Logger::log("tels: [\n");
	for (int idx = 0; idx < this->size; idx++) {
		Element *element = this->collection[idx];
		pel216::commons::Logger::log("#%2.0d (0x%08X) %s\n", idx + 1, element, (element ? element->toString().c_str() : UNKNOWN));
	}
	pel216::commons::Logger::log("]]\n");

}
