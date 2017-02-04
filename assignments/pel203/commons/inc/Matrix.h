#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string>
#include <vector>
#include <algorithm>

#include <chrono>
#include <random>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

using namespace pel203::commons;

namespace pel203 {

	namespace commons {

		static const int MAX_DIMENSIONS = 3;
		static const int MAX_COLUMNS_TO_DUMP = 10;
		static const double PRECISION = 0.000001;

		/**
		 * Classe que representa uma matrix.
		 *
		 * @author arrebola
		 */
		class Matrix {

		private:
			size_t rows;
			size_t columns;
			double **_data;

			/**
			 * Inicializa a matriz.<br />
			 *
			 * @param rows
			 *				o <code>size_t</code> que representa a quantidade de linhas da matriz
			 * @param columns
			 *				o <code>size_t</code> que representa a quantidade de colunas da matriz
			 * @param value
			 *				o <code>double</code> que representa o valor inicial
			 */
			PRIVATE void initialize(IN size_t rows, IN size_t columns = 0, IN double value = 0.0f) {

				if (rows < 1) {
					throw new IllegalParameterException();
				}

				this->rows = rows;
				this->columns = (columns == 0) ? this->rows : columns;

				this->_data = new double*[this->rows];
				for (size_t idx = 0; idx < this->rows; idx++) {
					this->_data[idx] = new double[this->columns];
				}

				fill(value);

			};

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param rows
			 *				o <code>size_t</code> que representa a quantidade de linhas da matriz
			 * @param columns
			 *				o <code>size_t</code> que representa a quantidade de colunas da matriz
			 */
			Matrix(IN size_t rows, IN size_t columns = 0) {
				this->initialize(rows, columns);
			};

			/**
			 * Construtor.<br />
			 *
			 * @param rows
			 *				o <code>size_t</code> que representa a quantidade de linhas da matriz
			 * @param columns
			 *				o <code>size_t</code> que representa a quantidade de colunas da matriz
			 * @param value
			 *				o <code>double</code> que representa o valor inicial
			 */
			Matrix(IN size_t rows, IN size_t columns, IN double value) {
				this->initialize(rows, columns, value);
			};

			/**
			 * Destrutor.<br />
			 */
			~Matrix() {

				if (Utils::isInvalidHandle(this->_data)) {
					return;
				}

				for (size_t idx = 0; idx < this->rows; idx++) {
					delete [] this->_data[idx];
				}
				delete [] this->_data;

			};
		
			/**
			 * Obtém a quantidade de linhas da matriz.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de linhas da matriz
			 */
			PUBLIC size_t getRows() {
				return this->rows;
			};

			/**
			 * Obtém a quantidade de colunas da matriz.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de colunas da matriz
			 */
			PUBLIC size_t getColumns() {
				return this->columns;
			};
			
			/**
			 * Obtém os dados da matriz.<br />
			 *
			 * @return o <code>double**</code> que representa os dados da matriz
			 */
			PUBLIC double **data() {
				return this->_data;
			};

			/**
			 * Clona uma matriz.<br />
			 *
			 * @return o Matrix que representa o clone
			 */
			PUBLIC Matrix *clone() {

				Matrix *matrix = new Matrix(this->rows, this->columns);

				for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
					for (size_t colIdx = 0; colIdx < this->columns; colIdx++) {
						matrix->data()[rowIdx][colIdx] = this->_data[rowIdx][colIdx];
					}
				}

				return matrix;

			};

			/**
			 * Obtém o elemento com maior valor.<br />
			 *
			 * @param max
			 *			o <code>double</code> que representa o maior valor encontrado
			 * @param maxRowIdx
			 *			o <code>size_t</code> que representa o índice da linha do maior valor encontrado
			 * @param maxColIdx
			 *			o <code>size_t</code> que representa o índice da coluna do maior valor encontrado
			 *
			 * @return <code>true</code> caso a obtenção tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool max(OUT double *max, OUT size_t *maxRowIdx, OUT size_t *maxColIdx) {
				
				size_t rowsCount = this->getRows();
				size_t colsCount = this->getColumns();
        
				*max = std::numeric_limits<double>::lowest();
				for (size_t rowIdx = 0; rowIdx < rowsCount; rowIdx++) {
					for (size_t colIdx = 0; colIdx < colsCount; colIdx++) {
						register double v = this->data()[rowIdx][colIdx];
						if (v > *max) {
							*max = v;
							*maxRowIdx = rowIdx;
							*maxColIdx = colIdx;
						}
					}
				}
				
				return (*max > std::numeric_limits<double>::lowest());

			};

			/**
			 * Obtém o elemento com maior valor.<br />
			 *
			 * @param max
			 *			o <code>double</code> que representa o maior valor encontrado
			 *
			 * @return <code>true</code> caso a obtenção tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool max(OUT double *max) {
				
				size_t rowsCount = this->getRows();
				size_t colsCount = this->getColumns();
        
				*max = std::numeric_limits<double>::lowest();
				for (size_t rowIdx = 0; rowIdx < rowsCount; rowIdx++) {
					for (size_t colIdx = 0; colIdx < colsCount; colIdx++) {
						register double v = this->data()[rowIdx][colIdx];
						if (v > *max) {
							*max = v;
						}
					}
				}
				
				return (*max > std::numeric_limits<double>::lowest());

			};
			
			/**
			 * Preenche a matriz com o valor informado.<br />
			 *
			 * @param value
			 *			o <code>double</code> que representa o valor 
			 */
			PUBLIC bool fill(IN double value = LONG_MIN) {

				// calcula o resultado aproximado da integração numérica
				for (size_t rowIdx = 0; rowIdx < this->getRows(); rowIdx++) {
					for (size_t colIdx = 0; colIdx < this->getColumns(); colIdx++) {
						this->data()[rowIdx][colIdx] = value;
					}
				}

				return true;

			};
			
			/**
			 * Preenche a matriz com valores aleatórios dentro de um intervalo.<br />
			 *
			 * @param min
			 *			o <code>double</code> que representa o valor mínimo do intervalo
			 * @param max
			 *			o <code>double</code> que representa o valor máximo do intervalo
			 */
			PUBLIC bool randomFill(IN double min = LONG_MIN, IN double max = LONG_MAX) {

				// cria o gerador aleatório
				std::random_device generator;
				std::uniform_real_distribution<double> distribution(min, max);

				// calcula o resultado aproximado da integração numérica
				for (size_t rowIdx = 0; rowIdx < this->getRows(); rowIdx++) {
					for (size_t colIdx = 0; colIdx < this->getColumns(); colIdx++) {
						this->data()[rowIdx][colIdx] = distribution(generator);
					}
				}

				return true;

			};
			
			/**
			 * Faz a impressão de uma matriz.<br />
			 *
			 * @param prefix
			 *				o <code>std::string</code> que representa o prefixo da impressão
			 */
			PUBLIC void dump(
					IN std::string prefix, 
					IN bool printPrefix = true, 
					IN size_t rows = 0,
					IN size_t columns = 0) {

				if (printPrefix) {
					Logger::log(">>>> Imprimindo matrix \"%s\" (%d x %d)...\n", prefix.c_str(), this->rows, this->columns);
				}

				size_t rows_to_Dump = (rows > 0) ? ((rows > this->rows) ?  this->rows : rows) : this->rows;
				size_t cols_to_Dump = (columns > 0) ? ((columns > this->columns) ?  
					((this->columns > MAX_COLUMNS_TO_DUMP) ? MAX_COLUMNS_TO_DUMP : this->columns) : columns) : this->columns;

				for (size_t i = 0; i < rows_to_Dump; i++) {
					
					Logger::log("|");
					for (size_t j = 0; j < cols_to_Dump; j++) {
						Logger::logWithoutTimestamp(" %12.5f ", this->_data[i][j]);
					}
					
					if (this->columns > MAX_COLUMNS_TO_DUMP) {
						Logger::logWithoutTimestamp(" ... ");
					}

					Logger::logWithoutTimestamp("|\n");
				}
				Logger::log("\n");

			};

			/**
			 * Faz a impressão de uma matriz.<br />
			 *
			 * @param prefix
			 *				o <code>std::string</code> que representa o prefixo da impressão
			 */
			PUBLIC void dumpToFile(
					IN size_t rows = 0, 
					IN size_t columns = 0) {

				size_t rows_to_Dump = (rows > 0) ? ((rows > this->rows) ?  this->rows : rows) : this->rows;
				size_t cols_to_Dump = (columns > 0) ?  ((columns > this->columns) ?  this->columns : columns) : this->columns;

				Logger::logToFile("\n");
				for (size_t i = 0; i < rows_to_Dump; i++) {
					
					Logger::logToFile("|");
					for (size_t j = 0; j < cols_to_Dump &&  j < MAX_COLUMNS_TO_DUMP; j++) {
						Logger::logToFileWithoutTimestamp(" %9.6f ", this->_data[i][j]);
					}
					
					if (this->columns > MAX_COLUMNS_TO_DUMP) {
						Logger::logToFileWithoutTimestamp(" ... ");
					}

					Logger::logToFileWithoutTimestamp("|\n");
				}
				Logger::logToFile("\n");

			};

		}; // class Matrix

	} // namespace commons

} // namespace pel203

#endif
