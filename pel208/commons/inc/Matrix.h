#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string>
#include <vector>
#include <algorithm>

#include <inc/Utils.h>
#include <inc/Logger.h>
#include <inc/ex/IllegalParameterException.h>

using namespace std;
using namespace pel216::commons;

namespace pel208 {

	namespace commons {

		static const int MAX_DIMENSIONS = 3;
		static const int MAX_COLUMNS_TO_DUMP = 5;

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
			 * Inicializa a matriz.
			 */
			void initialize() {

				this->_data = new double*[this->rows];
				for (size_t idx = 0; idx < this->rows; idx++) {
					this->_data[idx] = new double[this->columns];
				}

			};

			/**
			 *
			 */
			double sum(Matrix *by, size_t row, size_t column) {

				double result = 0.0f;
				
				for (size_t idx = 0; idx < this->columns; idx++) {
					result += this->data()[row][idx] * by->data()[idx][column];
				}

				return result;

			};

		public:
			/**
			 * Construtor.
			 *
			 * @param rows
			 *				o <code>size_t</code> que representa a quantidade de linhas da matriz
			 * @param columns
			 *				o <code>size_t</code> que representa a quantidade de colunas da matriz
			 */
			Matrix(size_t rows, size_t columns) {
				
				if (rows < 1 || columns < 1) {
					throw new pel216::commons::IllegalParameterException();
				}

				this->rows = rows;
				this->columns = columns;

				this->initialize();

			};

			/**
			 * Destrutor.
			 */
			~Matrix() {

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
			size_t getRows() {
				return this->rows;
			};

			/**
			 * Obtém a quantidade de colunas da matriz.<br />
			 *
			 * @return o <code>size_t</code> que representa a quantidade de colunas da matriz
			 */
			size_t getColumns() {
				return this->columns;
			};
			
			/**
			 * Obtém os dados da matriz.<br />
			 *
			 * @return o <code>double**</code> que representa os dados da matriz
			 */
			double **data() {
				return this->_data;
			};

			/**
			 * Configura todas as linhas de uma coluna com o valor informado.<br />
			 *
			 * @param value
			 *				o <code>double</code> que representa o valor
			 * @param rows
			 *				o <code>size_t</code> que representa a linha da matriz
			 * @param columns
			 *				o <code>size_t</code> que representa a coluna da matriz
			 */
			void setColumnCellsValue(size_t column, double value = 0.0f) {
				for (size_t idx = 0; idx < this->rows; idx++) {
					this->_data[idx][column] = value;
				}
			};

			/**
			 * Transpõe uma matriz.<br />
			 *
			 * @param transposed
			 *				o @link{Matrix} que representa a matriz transposta
			 *
			 * @return <code>true</code> caso a transposição tenha sido bem sucedida; do contrário <code>false</code>
			 */
			bool transpose(Matrix **transposed) {

				*transposed = new Matrix(this->columns, this->rows);
				
				for (size_t i = 0; i < this->rows; i++) {
					for (size_t j = 0; j < this->columns; j++) {
						(*transposed)->data()[j][i] = this->_data[i][j];
					}
				}

				return true;

			};

			/**
			 * Multiplica uma matriz por outra.<br />
			 *
			 * @param by
			 *				o @link{Matrix} que representa o fator de multiplicação
			 * @param product
			 *				o @link{Matrix} que representa a matriz resultante
			 *
			 * @return <code>true</code> caso a multiplicação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			bool multiply(Matrix *by, Matrix **product) {

				if (pel216::commons::Utils::isInvalidHandle(by)) {
					throw new pel216::commons::IllegalParameterException();
				}

				*product = new Matrix(this->rows, by->columns);

				for (size_t prodRowIdx = 0; prodRowIdx < (*product)->rows; prodRowIdx++) {
					for (size_t prodColIdx = 0; prodColIdx < (*product)->columns; prodColIdx++) {
						(*product)->data()[prodRowIdx][prodColIdx] = sum(by, prodRowIdx, prodColIdx);
					}
				}

				return true;

			};

			/**
			 * Inverte uma matrix 2 x 2.<br />
			 * 
			 * @param inverse
			 *				o @link{Matrix} que representa a matriz inversa
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			bool invert2x2(Matrix **inverse) {

				double a = this->_data[0][0];
				double b = this->_data[0][1];
				double c = this->_data[1][0];
				double d = this->_data[1][1];
				
				double det = ((a * d) - (b * c)) * 1.0f;
				if (det == 0.0f) {
					return false;
				}

				double det_inv = 1 / det;
				
				*inverse = new Matrix(this->rows, this->columns);
				(*inverse)->data()[0][0] = det_inv * d;
				(*inverse)->data()[0][1] = det_inv * b * -1.0f;
				(*inverse)->data()[1][0] = det_inv * c * -1.0f;
				(*inverse)->data()[1][1] = det_inv * a;
			
				return true;

			};

			/**
			 * Inverte uma matrix 3 x 3.<br />
			 * 
			 * @param inverse
			 *				o @link{Matrix} que representa a matriz inversa
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			bool invert3x3(Matrix **inverse) {

				Matrix identity(3,3);
				identity.data()[0][0] = 1;
				identity.data()[1][1] = 1;
				identity.data()[2][2] = 1;

				double a = this->_data[0][0];
				double b = this->_data[0][1];
				double c = this->_data[0][2];
				double d = this->_data[1][0];
				double e = this->_data[1][1];
				double f = this->_data[1][2];
				double g = this->_data[2][0];
				double h = this->_data[2][1];
				double i = this->_data[2][2];
				
				double det = (a * (e * i - f * h)) - (b * (i * d - f * g)) + (c * (d * h - e * g));
				if (det == 0) {
					return false;
				}

				double det_inv = 1 / det;
				
				*inverse = new Matrix(this->rows, this->columns);
				(*inverse)->data()[0][0] = det_inv * (e * i - f * h);
				(*inverse)->data()[0][1] = det_inv * (b * i - c * h) * -1.0f;
				(*inverse)->data()[0][2] = det_inv * (b * f - c * e);
				(*inverse)->data()[1][0] = det_inv * (d * i - f * g) * -1.0f;
				(*inverse)->data()[1][1] = det_inv * (a * i - c * g);
				(*inverse)->data()[1][2] = det_inv * (a * f - c * d) * -1.0f;
				(*inverse)->data()[2][0] = det_inv * (d * h - e * g);
				(*inverse)->data()[2][1] = det_inv * (a * h - b * g) * -1.0f;
				(*inverse)->data()[2][2] = det_inv * (a * e - b * d);

				return true;

			};

			/**
			 * Inverte uma matriz.<br />
			 *
			 * @param inverse
			 *				o @link{Matrix} que representa a matriz resultante
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			bool invert(Matrix **inverse) {

				// matrizes com inverso devem ser quadradas 
				if (this->rows != this->columns) {
					throw new pel216::commons::IllegalParameterException();
				}
								
				bool result = false;

				if (this->rows == 2) {
					result = invert2x2(inverse);
				} else if (this->rows == 3) {
					result = invert3x3(inverse);
				} else {
					throw new pel216::commons::IllegalParameterException(); // apenas matrizes 2x2 e 3x3 são suportadas
				}

				return result;

			};

			/**
			 * Faz a impressão de uma matriz.
			 *
			 * @param prefix
			 *				o <code>std::string</code> que representa o prefixo da impressão
			 */
			void dump(std::string prefix) {

				Logger::log("Imprimindo matrix %s (%d x %d)...\n", prefix.c_str(), this->rows, this->columns);
				for (size_t i = 0; i < this->rows; i++) {
					
					Logger::log("|");
					for (size_t j = 0; j < this->columns && j < MAX_COLUMNS_TO_DUMP + 1; j++) {
						Logger::logWithoutTimestamp(" %12.5f ", this->_data[i][j]);
					}
					
					if (this->columns > MAX_COLUMNS_TO_DUMP) {
						Logger::logWithoutTimestamp(" ... ");
					}

					Logger::logWithoutTimestamp("|\n");
				}
				Logger::log("\n");

			};

		}; // class Matrix

	} // namespace commons

} // namespace pel208

#endif
