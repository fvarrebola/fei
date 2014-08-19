#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>

// marcadores que facilitam a leitura do código
#define IN
#define OUT

#define PUBLIC
#define PROTECTED
#define PRIVATE

// definicoes de tipos
#ifndef NULL
	#define NULL 0
#endif

#ifndef PVOID
	#define PVOID								void*
#endif

#ifndef DWORD
	#define DWORD								unsigned long
#endif

#ifndef ZERO
	#define ZERO								0
#endif

#ifndef ONE
	#define ONE									1
#endif

#ifndef TWO
	#define TWO									2
#endif

// definicoes de macros
#define ALLOC_MEM(size)							(size > 0 ? malloc(size) : 0)
#define FREE_MEM(buffer)						\
        ((buffer != NULL) ? free(buffer) : void(0))
#define ZERO_MEM(buffer, size)					\
        ((buffer != NULL) ? memset(buffer, 0, size) : NULL)
#define COPY_MEM(dest, source, length)			\
        ((dest != NULL && source != NULL) ? memcpy(dest, source, length) : NULL)

#define STARS					                \
        "*******************************************************************************"
#define UNKNOWN					                "?????"

#ifndef MAX_PATH
    #define MAX_PATH                            256
#endif

// definicao utilizada para determinar se as funcoes de runtime com sufixo '_s' estao disponiveis
#if !__STDC_WANT_SECURE_LIB__
    #define vsprintf_s(buffer, buffer_size, stringbuffer, ...) \
        (vsprintf(buffer, stringbuffer, __VA_ARGS__))

    #define sprintf_s(buffer, buffer_size, stringbuffer, ...) \
        (sprintf(buffer, stringbuffer, __VA_ARGS__))

    #define localtime_s(tm, timer) \
		(*tm = *localtime(timer))
#endif

namespace pel216 {

	namespace commons {

		static const float pi = 3.141592654f;

		/**
		 * Classe utilitaria.
		 *
		 * @author arrebola
		 */
		class Utils {

			public:

				/**
				 * Determina se um ponteiro para uma memória eh valido.
				 *
				 * @param pSomePtr 
				 *              o <code>PVOID</code> que aponta para uma area de memória
				 *
				 * @return <code>TRUE</code> caso o ponteiro seja valido; do contrario, <code>FALSE</code>
				 */
				static bool isValidHandle(IN PVOID pSomePtr) {
					return (pSomePtr != NULL);
				};

				/**
				 * Determina se um ponteiro para uma memória eh valido.
				 *
				 * @param pSomePtr 
				 *              o <code>PVOID</code> que aponta para uma area de memória
				 *
				 * @return <code>TRUE</code> caso o ponteiro seja invalido; do contrario, <code>FALSE</code>
				 */
				static bool isInvalidHandle(IN PVOID pSomePtr) {
					return (!isValidHandle(pSomePtr));
				};

				/**
				 * Cria um ponteiro do tipo <code>void *</code>.
				 *
				 * @param uBytes
				 *              o <code>size_t</code> que representa o tamanho reservado para o ponteiro
				 * @param pSomePtr
				 *              o <code>PVOID</code> que representa o ponteiro de memória
				 *
				 * @return <code>TRUE</code> caso a criacao do ponteiro de memória tenha sido bem sucedida; do contrario <code>FALSE</code>
				 */
				static bool createPtr(IN size_t uBytes, OUT PVOID *pSomePtr) {

					bool bReturn = false;
    
					*pSomePtr = ALLOC_MEM(uBytes);
					if (isValidHandle(*pSomePtr)) {
						ZERO_MEM(*pSomePtr, uBytes);
						bReturn = true;
					}
    
					return bReturn;
    
				};

				/**
				 * Destrói um ponteiro do tipo <code>PVOID</code>.
				 *
				 * @param pSomePtr
				 *              o <code>PVOID</code> que representa o ponteiro de memória
				 * @param uBytes
				 *              o <code>size_t</code> que representa o tamanho reservado para o ponteiro
				 *
				 * @return <code>TRUE</code> caso a destruicao do ponteiro de memória tenha sido bem sucedida; do contrario <code>FALSE</code>
				 */
				static bool destroyPtr(IN PVOID pSomePtr, IN size_t uBytes) {

					bool bReturn = false;
    
					if (isValidHandle(pSomePtr)) {
						ZERO_MEM(pSomePtr, uBytes);
						FREE_MEM(pSomePtr);
						bReturn = true;
					}
    
					return bReturn;
    
				};

				/**
				 * Cria um vetor de dados aleatório.
				 *
				 * @param cbData
				 * 				o <code>unsigned long</code> que representa o tamanho de dados
				 * @param pbData
				 *				o <code>char **</code> que representa o vetor de dados aleatório
				 */
				static void createRandomData(IN unsigned long cbData, OUT char **pbData) {
					if (pel216::commons::Utils::createPtr(cbData, (PVOID*)(pbData))) {
						for (unsigned long idx = 0; idx < cbData; idx++) {
							(*pbData)[idx] = (char)(rand() % 127);
						}
					}
				};

				/**
				 * Converte um <code>std::vector</code> de <code>double</code> em um <code>std::string</code>.
				 *
				 * @param vector 
				 *				o <code>std::vector</code> a ser convertido
				 * 
				 * @return a <code>std::string</code> que representa o vetor
				 */
				static std::string doubleVectorToString(IN std::vector<double> vector) {

					std::stringstream stream;
					stream.precision(5);
					stream.setf(std::ios::fixed, std:: ios::floatfield);
					stream << "(";

					if (!vector.empty()) {
						size_t size = vector.size();
						for (size_t idx = 0; idx < size; idx++) {
							stream << vector[idx];
							if (idx < size - 1) {
								stream << ", ";
							}
						}
					}

					stream << ")";

					return stream.str();

				};

		}; // class Utils

	} // namespace commons

} // namespace pel216


#endif
