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

using namespace std;
using namespace pel216::commons;

namespace pel208 {

	namespace commons {

		static const int MAX_DIMENSIONS = 3;
		static const int MAX_COLUMNS_TO_DUMP = 10;

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
					throw new pel216::commons::IllegalParameterException();
				}

				this->rows = rows;
				this->columns = (columns == 0) ? this->rows : columns;

				this->_data = new double*[this->rows];
				for (size_t idx = 0; idx < this->rows; idx++) {
					this->_data[idx] = new double[this->columns];
				}

				fill(value);

			};


			/**
			 * Inverte uma matrix 2 x 2.<br />
			 * 
			 * @param inverse
			 *				o Matrix que representa a matriz inversa
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE bool invert2x2(OUT Matrix **inverse) {

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
			 *				o Matrix que representa a matriz inversa
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE bool invert3x3(OUT Matrix **inverse) {

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
			 * Inverte uma matrix 4 x 4.<br />
			 * Extraído de <a href="http://www.mesa3d.org/">MESA</a>.<br />
			 * 
			 * @param inverse
			 *				o Matrix que representa a matriz inversa
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE bool invert4x4(OUT Matrix **inverse) {

				double inv[16], det;

				double m[16] = {0.0f};
				for (size_t idx = 0; idx < 16; idx++) {
					m[idx] = this->data()[idx / 4][idx % 4];
				}

				inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
				inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
				inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
				inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
				inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
				inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] -m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
				inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
				inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
				inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
				inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
				inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
				inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
				inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
				inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
				inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
				inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

				det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

				if (det == 0) {
					return false;
				}

				det = 1.0 / det;

				*inverse = new Matrix(4, 4);
				for (size_t idx = 0; idx < 16; idx++) {
					(*inverse)->data()[idx / 4][idx % 4] = inv[idx] * det;
				}

				return true;
		
			};

			/**
			 * Soma do produto de todos os valores da linha da matriz atual com a coluna da matriz <code>by</code>.<br />
			 *
			 * @param by
			 *				o Matrix que representa o fator de multiplicação
			 * @param column
			 *				o <code>size_t</code> que represente a linha
			 * @param row
			 *				o <code>size_t</code> que represente a coluna
			 *
			 * @return o <code>double</code> que representa a soma
			 */
			PRIVATE	double multi_sum(Matrix *by, size_t row, size_t column) {

				double result = 0.0f;
				
				for (size_t idx = 0; idx < by->getColumns(); idx++) {
					if (idx < by->getRows()) {
						result += this->data()[row][idx] * by->data()[idx][column];
					}
				}

				return result;

			};

			/**
			 * Ajusta uma matriz subtraindo o valor da média.<br />
			 *
			 * @return o Matrix que representa a matriz resultante
			 */
			PRIVATE Matrix *adjustByMeanValue() {

				Matrix *adjusted = NULL;
				
				Matrix *means = mean();
				if (pel216::commons::Utils::isInvalidHandle(means)) {
					return adjusted;
				}
				
				adjusted = new Matrix(this->rows, this->columns);

				// subtrai as médias das amostras
				for (size_t colIdx = 0; colIdx < this->columns; colIdx++) {
					for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
						adjusted->data()[rowIdx][colIdx] = this->_data[rowIdx][colIdx] - means->data()[0][colIdx];
					}
				}

				delete means;

				return adjusted;

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
			Matrix(IN size_t rows, IN size_t columns = 0) {
				this->initialize(rows, columns);
			};

			/**
			 * Construtor.
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
			 * Destrutor.
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
			 * Configura todas as linhas de uma coluna com o valor informado.<br />
			 *
			 * @param column
			 *				o <code>size_t</code> que representa a coluna da matriz
			 * @param value
			 *				o <code>double</code> que representa o valor
			 */
			PUBLIC void setColumnCellsValue(size_t column, double value = 0.0f) {
				for (size_t idx = 0; idx < this->rows; idx++) {
					this->_data[idx][column] = value;
				}
			};

			/**
			 * Transpõe uma matriz.<br />
			 *
			 * @return o Matrix que representa a matriz transposta
			 */
			PUBLIC Matrix *transpose() {

				Matrix *transposed = new Matrix(this->columns, this->rows);
				
				for (size_t i = 0; i < this->rows; i++) {
					for (size_t j = 0; j < this->columns; j++) {
						transposed->data()[j][i] = this->_data[i][j];
					}
				}

				return transposed;

			};

			/**
			 * Multiplica uma matriz por outra.<br />
			 *
			 * @param by
			 *				o Matrix que representa o fator de multiplicação
			 *
			 * @return o Matrix que representa a matriz resultante
			 */
			PUBLIC Matrix *multiply(IN Matrix *by) {

				if (pel216::commons::Utils::isInvalidHandle(by)) {
					throw new pel216::commons::IllegalParameterException();
				}

				Matrix *product = new Matrix(this->rows, by->columns);

				for (size_t prodRowIdx = 0; prodRowIdx < product->getRows(); prodRowIdx++) {
					for (size_t prodColIdx = 0; prodColIdx < product->getColumns(); prodColIdx++) {
						product->data()[prodRowIdx][prodColIdx] = multi_sum(by, prodRowIdx, prodColIdx);
					}
				}

				return product;

			};

			/**
			 * Multiplica uma matriz por um valor.<br />
			 *
			 * @param double
			 *				o <code>double</code> que representa o fator de multiplicação
			 *
			 * @return o Matrix que representa a matriz resultante
			 */
			PUBLIC Matrix *multiply(IN double value) {

				Matrix *product = new Matrix(this->rows, this->columns);

				for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
					for (size_t colIdx = 0; colIdx < this->columns; colIdx++) {
						product->data()[rowIdx][colIdx] = this->data()[rowIdx][colIdx] * value;
					}
				}

				return product;

			};

			/**
			 * Divide uma matriz por um valor.<br />
			 *
			 * @param double
			 *				o <code>double</code> que representa o divisor
			 *
			 * @return o Matrix que representa a matriz resultante
			 */
			PUBLIC Matrix *divide(IN double value) {

				Matrix *result = new Matrix(this->rows, this->columns);

				for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
					for (size_t colIdx = 0; colIdx < this->columns; colIdx++) {
						result->data()[rowIdx][colIdx] = this->data()[rowIdx][colIdx] / value;
					}
				}

				return result;

			};

			/**
			 * Inverte uma matriz.<br />
			 *
			 * @param inverse
			 *				o Matrix que representa a matriz resultante
			 *
			 * @return <code>true</code> caso a inversão tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool invert(OUT Matrix **inverse) {

				// matrizes com inverso devem ser quadradas 
				if (this->rows != this->columns) {
					throw new pel216::commons::IllegalParameterException();
				}
								
				bool result = false;

				if (this->rows == 2) {
					result = invert2x2(inverse);
				} else if (this->rows == 3) {
					result = invert3x3(inverse);
				}  else if (this->rows == 4) {
					result = invert4x4(inverse);
				} else {
					throw new pel216::commons::IllegalParameterException(); // apenas matrizes 2x2 e 3x3 são suportadas
				}

				return result;

			};

			/**
			 * Calcula a matriz de covariância.<br />
			 *
			 * @param adjusted
			 *				o Matrix que representa a matriz de valores ajustados
			 *
			 * @return o Matrix que representa a matriz de covariância
			 */
			PUBLIC Matrix *covariate(OUT Matrix **adjusted) {

				Matrix *covariate = NULL;

				*adjusted = adjustByMeanValue();
				if (pel216::commons::Utils::isInvalidHandle(adjusted)) {
					return covariate;
				}

				double samples = this->rows; 

				size_t covarSize = this->getColumns(); 
				covariate = new Matrix(covarSize, covarSize);
				for (size_t covarRowIdx = 0; covarRowIdx < covarSize; covarRowIdx++) {
					for (size_t covarColIdx = 0; covarColIdx < covarSize; covarColIdx++) {
						register double sum = 0.0f;
						for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
							sum += (*adjusted)->data()[rowIdx][covarRowIdx] * (*adjusted)->data()[rowIdx][covarColIdx];
						}
						covariate->data()[covarRowIdx][covarColIdx] = (sum / ((samples - 1) * 1.0f));
					}
				}

				return covariate;

			};

			/**
			 * Retorna a matriz identidade de uma matriz.<br />
			 *
			 * @param identity
			 *				o Matrix que representa a matriz identidade
			 *
			 * @return <code>true</code> caso o cálculo tenha sido bem sucedido; do contrário <code>false</code>
			 */			 
			PUBLIC bool identity(OUT Matrix **identity) {

				size_t size = this->getColumns(); 
				
				*identity = new Matrix(size, size);
				for (size_t idx = 0; idx < size; idx++) {
					(*identity)->data()[idx][idx] = 1.0f;
				}

				return true;

			};

			/**
			 * Retorna a matriz diagonal de uma matriz.<br />
			 *
			 * @return o Matrix que representa a matriz diagonal
			 */			 
			PUBLIC Matrix *diagonal() {

				size_t size = this->getColumns(); 
				
				Matrix *diagonal = new Matrix(size, 1);
				for (size_t idx = 0; idx < size; idx++) {
					diagonal->data()[idx][0] = this->data()[idx][idx];
				}

				return diagonal;

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
        
				*max = LONG_MIN;
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
				
				return (*max != LONG_MIN);

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
			 * Obtém os valores médios para as amostras de uma das colunas da matriz.<br />
			 * As médias são armazenadas em uma matriz com a mesma quantidade de colunas da matriz sendo analisada.<br />
			 * 		
			 * @return o Matrix que representa a matriz de valores médios
			 */
			PUBLIC Matrix *mean() {
				
				Matrix *means = new Matrix(1, this->columns);

				for (size_t colIdx = 0; colIdx < this->columns; colIdx++) {
					double sum = 0.0f;
					for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {
						sum += this->_data[rowIdx][colIdx];
					}
					means->data()[0][colIdx] = sum / (this->rows * 1.0f);
				}
				
				return means;

			};

			/**
			 * Encolhe uma matriz.<br />
			 *
			 * @param rows
			 *			o <code>size_t</code> que representa a quantidade de linhas
			 */
			PUBLIC void shrink(size_t rows = 0) {

				if (rows == 0 || rows > this->rows) {
					throw new pel216::commons::IllegalParameterException();
				}

				if (rows > 0) {
					for (size_t idx = rows; idx < this->rows; idx++) {
						delete [] this->_data[idx];
					}
					this->rows = rows;
				}

			};

			/**
			 * Gera uma matriz de elementos únicos considerando as amostras da coluna informada.<br />
			 *
			 * @param column
			 *			o <code>size_t</code> que representa o índice da coluna
			 */
			PUBLIC Matrix *unique(size_t column = 0) {

				// em termos de quantidade de linhas a matriz de valores únicos
				// é, no máximo, igual à matriz atual
				Matrix *unique = new Matrix(this->rows, 1);

				size_t count = 0;
				
				for (size_t rowIdx = 0; rowIdx < this->rows; rowIdx++) {

					register double value = data()[rowIdx][column];

					bool known = false;

					if (rowIdx > 0) {
						size_t invRowIdx = rowIdx;
						while (invRowIdx > 0 && !known) {
							if (data()[rowIdx][column] == data()[invRowIdx - 1][column]) {
								known = true;							
							}
							invRowIdx--;
						}
					}

					if (!known) {
						unique->data()[count++][0] = value;
					}

				}

				unique->shrink(count);

				return unique;

			};

			/**
			 * Soma uma matriz à matriz atual.<br />
			 *
			 * @param with
			 *				o Matrix que representa a matriz a ser somada
			 * @param result
			 *				o Matrix que representa o resultado
			 *
			 * @return <code>true</code> caso a soma seja bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool sum(IN Matrix *with, IN OUT Matrix **result) {

				if (pel216::commons::Utils::isInvalidHandle(with)) {
					throw new pel216::commons::IllegalParameterException();
				}

				size_t rows = this->getRows();
				size_t cols = this->getColumns();
				if ((with->getRows() != rows) || (with->getColumns() != cols)) {
					throw new pel216::commons::IllegalParameterException();
				}

				if (pel216::commons::Utils::isInvalidHandle((*result))) {
					*result = this->clone();
				}

				for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					for (size_t colIdx = 0; colIdx < cols; colIdx++) {
						(*result)->data()[rowIdx][colIdx] = this->data()[rowIdx][colIdx] + with->data()[rowIdx][colIdx];
					}
				}

				return true;

			}

			/**
			 * Subtrai uma matriz da matriz atual.<br />
			 *
			 * @param identity
			 *				o Matrix que representa a matriz a ser subtraída
			 * @param identity
			 *				o Matrix que representa o resultado
			 *
			 * @return <code>true</code> caso a sbbtração seja bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC bool minus(IN Matrix *with, IN OUT Matrix **result) {

				if (pel216::commons::Utils::isInvalidHandle(with)) {
					throw new pel216::commons::IllegalParameterException();
				}

				size_t rows = this->getRows();
				size_t cols = this->getColumns();
				if ((with->getRows() != rows) || (with->getColumns() != cols)) {
					throw new pel216::commons::IllegalParameterException();
				}

				if (pel216::commons::Utils::isInvalidHandle(*result)) {
					*result = this->clone();
				}

				for (size_t rowIdx = 0; rowIdx < rows; rowIdx++) {
					for (size_t colIdx = 0; colIdx < cols; colIdx++) {
						(*result)->data()[rowIdx][colIdx] = this->data()[rowIdx][colIdx] - with->data()[rowIdx][colIdx];
					}
				}

				return true;

			}

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
					Logger::log(">>>> Imprimindo matrix %s (%d x %d)...\n", prefix.c_str(), this->rows, this->columns);
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

} // namespace pel208

#endif
