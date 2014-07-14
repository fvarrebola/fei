#pragma once

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <string>
#include <sstream>

#include <inc/Utils.h>

namespace pel216 {

	namespace week1 {
	
		/**
		 * Representa de um elemento que pode ser incluído em uma pilha ou fila.
		 *
		 * @author arrebola
		 */
		class Element {

		private:
			unsigned long cbData;
			PVOID pbData;

		public:
			Element();
			~Element();

			/**
			 * Obtem o dado encapsulado neste elemento.
			 *
			 * @return o <code>PVOID</code> que representa o dado 
			 */
			PVOID getData();

			/**
			 * Obtem o tamanho do dado encapsulado neste elemento.
			 *
			 * @return o <code>unsigned long</code> que representa o tamanho dado 
			 */
			unsigned long getDataLen();

			/**
			 * Configura o dado encapsulado neste elemento.
			 *
			 * @param data 
			 *				o <code>PVOID</code> que representa o dado
			 *
			 * @return o <code>true</code> caso o dado tenha sido configurado com sucesso; do contrario <code>false</code>
			 */
			bool setData(IN PVOID pbData, IN unsigned long cbData);

			/**
			 * Compara dois elementos.
			 *
			 * @param that
			 *				o <code>Element</code> utilizado na comparacao
			 *
			 * @return o <code>true</code> caso os elementos sejam iguais; do contrario <code>false</code>
			 */
			bool equals(IN Element *that);

			/**
			 * Cria um clone do elemento.
			 *
			 * @return o <code>Element</code> que representa o clone
			 */
			Element *clone();

			/**
			 * Retorna a representacao do elemento.
			 */
			std::string toString();

			/**
 			 * Cria um <code>Element</code> aleatÃ³rio.
 			 * 
			 * @param pbData 
			 *				o <code>char *</code> que representa o conteúdo
			 * @param cbData
			 *				o <code>unsigned long</code> que representa o tamanho do conteúdo
			 *
			 * @return o <code>Element</code> aleatÃ³rio
			 */
			static Element *createRandomElement() {

				Element *element = new Element();

				unsigned long cbData = 10;
				char *pbData = NULL;
				if (pel216::commons::Utils::createPtr(cbData, (PVOID*)&pbData)) {
					for (unsigned long idx = 0; idx < cbData; idx++) {
						pbData[idx] = (char)(rand() % 127);
					}
				}

				element->setData(pbData, cbData);
			
				pel216::commons::Utils::destroyPtr(pbData, cbData);

				return element;
				
			}

		};

	} // namespace week1

} // namespace pel216

#endif
