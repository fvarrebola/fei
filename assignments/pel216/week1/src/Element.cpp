#include <cstdio>
#include <cstring>

#include <inc/Utils.h>
#include <inc/Element.h>

/**
 * Construtor.
 */
PUBLIC pel216::week1::Element::Element() {
	this->pbData = NULL;
	this->cbData = 0;
}



/**
 * Destrutor.
 */
PUBLIC pel216::week1::Element::~Element() {

	if (pel216::commons::Utils::isValidHandle(this->pbData)) {
		pel216::commons::Utils::destroyPtr(this->pbData, this->cbData);
	}

	this->pbData = NULL;
	this->cbData = 0;

}



/**
 * Obtem o dado encapsulado neste elemento.
 *
 * @return o <code>PVOID</code> que representa o dado 
 */
PUBLIC PVOID pel216::week1::Element::getData() {
	return this->pbData;
}



/**
 * Obtem o tamanho do dado encapsulado neste elemento.
 *
 * @return o <code>unsigned long</code> que representa o tamanho dado 
 */
PUBLIC unsigned long pel216::week1::Element::getDataLen() {
	return this->cbData;
}



/**
 * Configura o dado encapsulado neste elemento.
 *
 * @param data 
 *				o <code>PVOID</code> que representa o dado
 */
PUBLIC bool pel216::week1::Element::setData(IN PVOID pbData, IN unsigned long cbData) {

	bool result = false;

	if (pel216::commons::Utils::isInvalidHandle(pbData) || cbData < 1) {
		return result;
	}

	if (pel216::commons::Utils::createPtr(cbData, (PVOID*)&this->pbData)) {
		COPY_MEM(this->pbData, pbData, cbData);
		this->cbData = cbData;
		result = true;
	}

	return result;

}



/**
 * Cria um clone do elemento.
 *
 * @return o <code>Element</code> que representa o clone
 */
PUBLIC pel216::week1::Element *pel216::week1::Element::clone() {
	Element *element = new Element();
	element->setData(this->pbData, this->cbData);
	return element;
}



/**
 * Compara dois elementos.
 *
 * @param that
 *				o <code>Element</code> utilizado na comparacao
 *
 * @return o <code>true</code> caso os elementos sejam iguais; do contrario <code>false</code>
 */
PUBLIC bool pel216::week1::Element::equals(IN pel216::week1::Element *that) {
	
	if (pel216::commons::Utils::isInvalidHandle(that)) {
		return false;
	}

	if (this->cbData != that->cbData) {
		return false;
	}

	if (this->pbData == that->pbData) {
		return true;
	}

	bool equals = true;
	for (unsigned long idx = 0; idx < this->cbData && equals; idx++) {
		equals &= (((char*)this->pbData)[idx] == ((char*)that->pbData)[idx]);
	}

	return equals;

}



/**
 * Retorna a representacao do elemento.
 * 
 * @return o <code>std::string</code> que representa o elemento
 */
PUBLIC std::string pel216::week1::Element::toString() {
	
	std::string stringRep;
	stringRep.resize(MAX_PATH * 2);

	char pszDataAsChar[MAX_PATH] = {0x00};
	
	static int length = ((this->cbData > 10) ? 10 : this->cbData);
	for (int idx = 0; idx < length; idx++) {
		sprintf_s((pszDataAsChar + (idx * 5)), 6, "0x%02X ", ((char*)this->pbData)[idx]);
	}

	sprintf_s((char*)stringRep.c_str(), MAX_PATH * 2, "[t: %d, d: (%s...)]", length, pszDataAsChar);

	return stringRep;

}
