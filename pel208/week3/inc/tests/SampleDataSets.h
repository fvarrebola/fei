#pragma once

#ifndef _DATASETS_H_
#define _DATASETS_H_

#include <inc/Matrix.h>

using namespace std;

namespace pel208 {

	namespace commons {

		class SampleDataSets {

		private:

		public:

			/**
			 * Obt�m a matriz de amostras com duas dimens�es para uso no PCA.<br />
			 *
			 * @return o Matrix que representa o conjunto de amostras
			 */
			PUBLIC static Matrix *getPCASimpleDS() {

				Matrix *m = new Matrix(10, 2);

				// valores de x
				m->data()[0][0] = 2.5f;
				m->data()[1][0] = 0.5f;
				m->data()[2][0] = 2.2f;
				m->data()[3][0] = 1.9f;
				m->data()[4][0] = 3.1f;
				m->data()[5][0] = 2.3f;
				m->data()[6][0] = 2.0f;
				m->data()[7][0] = 1.0f;
				m->data()[8][0] = 1.5;
				m->data()[9][0] = 1.1;

				// valores de y
				m->data()[0][1] = 2.4f;
				m->data()[1][1] = 0.7f;
				m->data()[2][1] = 2.9f;
				m->data()[3][1] = 2.2f;
				m->data()[4][1] = 3.0f;
				m->data()[5][1] = 2.7f;
				m->data()[6][1] = 1.6f;
				m->data()[7][1] = 1.1f;
				m->data()[8][1] = 1.6f;
				m->data()[9][1] = 0.9f;

				return m;

			};

			/**
			 * Obt�m a matriz de amostras <i>hald</i> para uso no PCA.<br />
			 *
			 * @return o Matrix que representa o conjunto de amostras
			 */
			PUBLIC static Matrix *getPCAHaldDS() {

				Matrix *m = new Matrix(13, 4);

				m->data()[0][0] = 7;
				m->data()[0][1] = 26;
				m->data()[0][2] = 6;
				m->data()[0][3] = 60; 
				//m->data()[0][4] = 78.5f;
				m->data()[1][0] =  1;
				m->data()[1][1] =  29;
				m->data()[1][2] =  15;
				m->data()[1][3] =  52; 
				//m->data()[1][4] = 74.3;
				m->data()[2][0] =  11;
				m->data()[2][1] =  56;
				m->data()[2][2] =  8;
				m->data()[2][3] =  20; 
				//m->data()[2][4] = 104.3;
				m->data()[3][0] =  11;
				m->data()[3][1] =  31;
				m->data()[3][2] =  8;
				m->data()[3][3] =  47; 
				//m->data()[3][4] = 87.6;
				m->data()[4][0] =  7;
				m->data()[4][1] =  52;
				m->data()[4][2] =  6;
				m->data()[4][3] =  33; 
				//m->data()[4][4] = 95.9;
				m->data()[5][0] =  11;
				m->data()[5][1] =  55;
				m->data()[5][2] =  9;
				m->data()[5][3] =  22; 
				//m->data()[5][4] = 109.2;
				m->data()[6][0] =  3;
				m->data()[6][1] =  71;
				m->data()[6][2] =  17;
				m->data()[6][3] =  6; 
				//m->data()[6][4] = 102.7;
				m->data()[7][0] =  1;
				m->data()[7][1] =  31;
				m->data()[7][2] =  22;
				m->data()[7][3] =  44; 
				//m->data()[7][4] = 72.5;
				m->data()[8][0] =  2;
				m->data()[8][1] =  54;
				m->data()[8][2] =  18;
				m->data()[8][3] =  22; 
				//m->data()[8][4] = 93.1;
				m->data()[9][0] =  21;
				m->data()[9][1] =  47;
				m->data()[9][2] =  4;
				m->data()[9][3] =  26; 
				//m->data()[9][4] = 115.9;
				m->data()[10][0] =  1;
				m->data()[10][1] =  40;
				m->data()[10][2] =  23;
				m->data()[10][3] =  34; 
				//m->data()[10][4] = 83.8;
				m->data()[11][0] =  11;
				m->data()[11][1] =  66;
				m->data()[11][2] =  9;
				m->data()[11][3] =  12; 
				//m->data()[11][4] = 113.3;
				m->data()[12][0] =  10;
				m->data()[12][1] =  68;
				m->data()[12][2] =  8;
				m->data()[12][3] =  12;
				//m->data()[12][4] = 109.4;

				return m;

			};

			/**
			 * Retorna o conjunto de amostras para testes com o LDA.<br />
			 * Nesse conjunto temos 2 classes e 5 amostras de cada.<br />
			 * A matriz tem 3 colunas; a 1a indica a classe, a segunda e a terceira os valores das amostras.<br />
			 *
			 * @return o Matrix que representa o conjunto de dados
			 */
			PUBLIC static Matrix *getLDASimpleDS() {

				Matrix *m = new Matrix(10, 3);

				m->data()[0][0] = 0; m->data()[0][1] = 4; m->data()[0][2] = 2;
				m->data()[1][0] = 0; m->data()[1][1] = 2; m->data()[1][2] = 4; 
				m->data()[2][0] = 0; m->data()[2][1] = 2; m->data()[2][2] = 3;
				m->data()[3][0] = 0; m->data()[3][1] = 3; m->data()[3][2] = 6; 
				m->data()[4][0] = 0; m->data()[4][1] = 4; m->data()[4][2] = 4;

				m->data()[5][0] = 1; m->data()[5][1] = 9; m->data()[5][2] = 10;
				m->data()[6][0] = 1; m->data()[6][1] = 6; m->data()[6][2] = 8; 
				m->data()[7][0] = 1; m->data()[7][1] = 9; m->data()[7][2] = 5;
				m->data()[8][0] = 1; m->data()[8][1] = 8; m->data()[8][2] = 7; 
				m->data()[9][0] = 1; m->data()[9][1] = 10; m->data()[9][2] = 8;

				return m;

			};

			/**
			 * Retorna o conjunto de amostras para testes com o LDA.<br />
			 * Nesse conjunto temos 3 classes e 50 amostras de cada.<br />
			 * A matriz tem 5 colunas; a 5a indica a classe.<br />
			 *
			 * @return o Matrix que representa o conjunto de dados
			 */
			PUBLIC static Matrix *getLDAIrisDS() {

				Matrix *m = new Matrix(150, 5);

				m->data()[0][1] = 5.1; 	m->data()[0][2] = 3.5; 	m->data()[0][3] = 1.4; 	m->data()[0][4] = 0.2; 	m->data()[0][0] = 0; 
				m->data()[1][1] = 4.9; 	m->data()[1][2] = 3; 	m->data()[1][3] = 1.4; 	m->data()[1][4] = 0.2; 	m->data()[1][0] = 0; 
				m->data()[2][1] = 4.7; 	m->data()[2][2] = 3.2; 	m->data()[2][3] = 1.3; 	m->data()[2][4] = 0.2; 	m->data()[2][0] = 0; 
				m->data()[3][1] = 4.6; 	m->data()[3][2] = 3.1; 	m->data()[3][3] = 1.5; 	m->data()[3][4] = 0.2; 	m->data()[3][0] = 0; 
				m->data()[4][1] = 5; 	m->data()[4][2] = 3.6; 	m->data()[4][3] = 1.4; 	m->data()[4][4] = 0.2; 	m->data()[4][0] = 0; 
				m->data()[5][1] = 5.4; 	m->data()[5][2] = 3.9; 	m->data()[5][3] = 1.7; 	m->data()[5][4] = 0.4; 	m->data()[5][0] = 0; 
				m->data()[6][1] = 4.6; 	m->data()[6][2] = 3.4; 	m->data()[6][3] = 1.4; 	m->data()[6][4] = 0.3; 	m->data()[6][0] = 0; 
				m->data()[7][1] = 5; 	m->data()[7][2] = 3.4; 	m->data()[7][3] = 1.5; 	m->data()[7][4] = 0.2; 	m->data()[7][0] = 0; 
				m->data()[8][1] = 4.4; 	m->data()[8][2] = 2.9; 	m->data()[8][3] = 1.4; 	m->data()[8][4] = 0.2; 	m->data()[8][0] = 0; 
				m->data()[9][1] = 4.9; 	m->data()[9][2] = 3.1; 	m->data()[9][3] = 1.5; 	m->data()[9][4] = 0.1; 	m->data()[9][0] = 0; 
				m->data()[10][1] = 5.4; 	m->data()[10][2] = 3.7; 	m->data()[10][3] = 1.5; 	m->data()[10][4] = 0.2; 	m->data()[10][0] = 0; 
				m->data()[11][1] = 4.8; 	m->data()[11][2] = 3.4; 	m->data()[11][3] = 1.6; 	m->data()[11][4] = 0.2; 	m->data()[11][0] = 0; 
				m->data()[12][1] = 4.8; 	m->data()[12][2] = 3; 	m->data()[12][3] = 1.4; 	m->data()[12][4] = 0.1; 	m->data()[12][0] = 0; 
				m->data()[13][1] = 4.3; 	m->data()[13][2] = 3; 	m->data()[13][3] = 1.1; 	m->data()[13][4] = 0.1; 	m->data()[13][0] = 0; 
				m->data()[14][1] = 5.8; 	m->data()[14][2] = 4; 	m->data()[14][3] = 1.2; 	m->data()[14][4] = 0.2; 	m->data()[14][0] = 0; 
				m->data()[15][1] = 5.7; 	m->data()[15][2] = 4.4; 	m->data()[15][3] = 1.5; 	m->data()[15][4] = 0.4; 	m->data()[15][0] = 0; 
				m->data()[16][1] = 5.4; 	m->data()[16][2] = 3.9; 	m->data()[16][3] = 1.3; 	m->data()[16][4] = 0.4; 	m->data()[16][0] = 0; 
				m->data()[17][1] = 5.1; 	m->data()[17][2] = 3.5; 	m->data()[17][3] = 1.4; 	m->data()[17][4] = 0.3; 	m->data()[17][0] = 0; 
				m->data()[18][1] = 5.7; 	m->data()[18][2] = 3.8; 	m->data()[18][3] = 1.7; 	m->data()[18][4] = 0.3; 	m->data()[18][0] = 0; 
				m->data()[19][1] = 5.1; 	m->data()[19][2] = 3.8; 	m->data()[19][3] = 1.5; 	m->data()[19][4] = 0.3; 	m->data()[19][0] = 0; 
				m->data()[20][1] = 5.4; 	m->data()[20][2] = 3.4; 	m->data()[20][3] = 1.7; 	m->data()[20][4] = 0.2; 	m->data()[20][0] = 0; 
				m->data()[21][1] = 5.1; 	m->data()[21][2] = 3.7; 	m->data()[21][3] = 1.5; 	m->data()[21][4] = 0.4; 	m->data()[21][0] = 0; 
				m->data()[22][1] = 4.6; 	m->data()[22][2] = 3.6; 	m->data()[22][3] = 1; 	m->data()[22][4] = 0.2; 	m->data()[22][0] = 0; 
				m->data()[23][1] = 5.1; 	m->data()[23][2] = 3.3; 	m->data()[23][3] = 1.7; 	m->data()[23][4] = 0.5; 	m->data()[23][0] = 0; 
				m->data()[24][1] = 4.8; 	m->data()[24][2] = 3.4; 	m->data()[24][3] = 1.9; 	m->data()[24][4] = 0.2; 	m->data()[24][0] = 0; 
				m->data()[25][1] = 5; 	m->data()[25][2] = 3; 	m->data()[25][3] = 1.6; 	m->data()[25][4] = 0.2; 	m->data()[25][0] = 0; 
				m->data()[26][1] = 5; 	m->data()[26][2] = 3.4; 	m->data()[26][3] = 1.6; 	m->data()[26][4] = 0.4; 	m->data()[26][0] = 0; 
				m->data()[27][1] = 5.2; 	m->data()[27][2] = 3.5; 	m->data()[27][3] = 1.5; 	m->data()[27][4] = 0.2; 	m->data()[27][0] = 0; 
				m->data()[28][1] = 5.2; 	m->data()[28][2] = 3.4; 	m->data()[28][3] = 1.4; 	m->data()[28][4] = 0.2; 	m->data()[28][0] = 0; 
				m->data()[29][1] = 4.7; 	m->data()[29][2] = 3.2; 	m->data()[29][3] = 1.6; 	m->data()[29][4] = 0.2; 	m->data()[29][0] = 0; 
				m->data()[30][1] = 4.8; 	m->data()[30][2] = 3.1; 	m->data()[30][3] = 1.6; 	m->data()[30][4] = 0.2; 	m->data()[30][0] = 0; 
				m->data()[31][1] = 5.4; 	m->data()[31][2] = 3.4; 	m->data()[31][3] = 1.5; 	m->data()[31][4] = 0.4; 	m->data()[31][0] = 0; 
				m->data()[32][1] = 5.2; 	m->data()[32][2] = 4.1; 	m->data()[32][3] = 1.5; 	m->data()[32][4] = 0.1; 	m->data()[32][0] = 0; 
				m->data()[33][1] = 5.5; 	m->data()[33][2] = 4.2; 	m->data()[33][3] = 1.4; 	m->data()[33][4] = 0.2; 	m->data()[33][0] = 0; 
				m->data()[34][1] = 4.9; 	m->data()[34][2] = 3.1; 	m->data()[34][3] = 1.5; 	m->data()[34][4] = 0.1; 	m->data()[34][0] = 0; 
				m->data()[35][1] = 5; 	m->data()[35][2] = 3.2; 	m->data()[35][3] = 1.2; 	m->data()[35][4] = 0.2; 	m->data()[35][0] = 0; 
				m->data()[36][1] = 5.5; 	m->data()[36][2] = 3.5; 	m->data()[36][3] = 1.3; 	m->data()[36][4] = 0.2; 	m->data()[36][0] = 0; 
				m->data()[37][1] = 4.9; 	m->data()[37][2] = 3.1; 	m->data()[37][3] = 1.5; 	m->data()[37][4] = 0.1; 	m->data()[37][0] = 0; 
				m->data()[38][1] = 4.4; 	m->data()[38][2] = 3; 	m->data()[38][3] = 1.3; 	m->data()[38][4] = 0.2; 	m->data()[38][0] = 0; 
				m->data()[39][1] = 5.1; 	m->data()[39][2] = 3.4; 	m->data()[39][3] = 1.5; 	m->data()[39][4] = 0.2; 	m->data()[39][0] = 0; 
				m->data()[40][1] = 5; 	m->data()[40][2] = 3.5; 	m->data()[40][3] = 1.3; 	m->data()[40][4] = 0.3; 	m->data()[40][0] = 0; 
				m->data()[41][1] = 4.5; 	m->data()[41][2] = 2.3; 	m->data()[41][3] = 1.3; 	m->data()[41][4] = 0.3; 	m->data()[41][0] = 0; 
				m->data()[42][1] = 4.4; 	m->data()[42][2] = 3.2; 	m->data()[42][3] = 1.3; 	m->data()[42][4] = 0.2; 	m->data()[42][0] = 0; 
				m->data()[43][1] = 5; 	m->data()[43][2] = 3.5; 	m->data()[43][3] = 1.6; 	m->data()[43][4] = 0.6; 	m->data()[43][0] = 0; 
				m->data()[44][1] = 5.1; 	m->data()[44][2] = 3.8; 	m->data()[44][3] = 1.9; 	m->data()[44][4] = 0.4; 	m->data()[44][0] = 0; 
				m->data()[45][1] = 4.8; 	m->data()[45][2] = 3; 	m->data()[45][3] = 1.4; 	m->data()[45][4] = 0.3; 	m->data()[45][0] = 0; 
				m->data()[46][1] = 5.1; 	m->data()[46][2] = 3.8; 	m->data()[46][3] = 1.6; 	m->data()[46][4] = 0.2; 	m->data()[46][0] = 0; 
				m->data()[47][1] = 4.6; 	m->data()[47][2] = 3.2; 	m->data()[47][3] = 1.4; 	m->data()[47][4] = 0.2; 	m->data()[47][0] = 0; 
				m->data()[48][1] = 5.3; 	m->data()[48][2] = 3.7; 	m->data()[48][3] = 1.5; 	m->data()[48][4] = 0.2; 	m->data()[48][0] = 0; 
				m->data()[49][1] = 5; 	m->data()[49][2] = 3.3; 	m->data()[49][3] = 1.4; 	m->data()[49][4] = 0.2; 	m->data()[49][0] = 0; 
				m->data()[50][1] = 7; 	m->data()[50][2] = 3.2; 	m->data()[50][3] = 4.7; 	m->data()[50][4] = 1.4; 	m->data()[50][0] = 1; 
				m->data()[51][1] = 6.4; 	m->data()[51][2] = 3.2; 	m->data()[51][3] = 4.5; 	m->data()[51][4] = 1.5; 	m->data()[51][0] = 1; 
				m->data()[52][1] = 6.9; 	m->data()[52][2] = 3.1; 	m->data()[52][3] = 4.9; 	m->data()[52][4] = 1.5; 	m->data()[52][0] = 1; 
				m->data()[53][1] = 5.5; 	m->data()[53][2] = 2.3; 	m->data()[53][3] = 4; 	m->data()[53][4] = 1.3; 	m->data()[53][0] = 1; 
				m->data()[54][1] = 6.5; 	m->data()[54][2] = 2.8; 	m->data()[54][3] = 4.6; 	m->data()[54][4] = 1.5; 	m->data()[54][0] = 1; 
				m->data()[55][1] = 5.7; 	m->data()[55][2] = 2.8; 	m->data()[55][3] = 4.5; 	m->data()[55][4] = 1.3; 	m->data()[55][0] = 1; 
				m->data()[56][1] = 6.3; 	m->data()[56][2] = 3.3; 	m->data()[56][3] = 4.7; 	m->data()[56][4] = 1.6; 	m->data()[56][0] = 1; 
				m->data()[57][1] = 4.9; 	m->data()[57][2] = 2.4; 	m->data()[57][3] = 3.3; 	m->data()[57][4] = 1; 	m->data()[57][0] = 1; 
				m->data()[58][1] = 6.6; 	m->data()[58][2] = 2.9; 	m->data()[58][3] = 4.6; 	m->data()[58][4] = 1.3; 	m->data()[58][0] = 1; 
				m->data()[59][1] = 5.2; 	m->data()[59][2] = 2.7; 	m->data()[59][3] = 3.9; 	m->data()[59][4] = 1.4; 	m->data()[59][0] = 1; 
				m->data()[60][1] = 5; 	m->data()[60][2] = 2; 	m->data()[60][3] = 3.5; 	m->data()[60][4] = 1; 	m->data()[60][0] = 1; 
				m->data()[61][1] = 5.9; 	m->data()[61][2] = 3; 	m->data()[61][3] = 4.2; 	m->data()[61][4] = 1.5; 	m->data()[61][0] = 1; 
				m->data()[62][1] = 6; 	m->data()[62][2] = 2.2; 	m->data()[62][3] = 4; 	m->data()[62][4] = 1; 	m->data()[62][0] = 1; 
				m->data()[63][1] = 6.1; 	m->data()[63][2] = 2.9; 	m->data()[63][3] = 4.7; 	m->data()[63][4] = 1.4; 	m->data()[63][0] = 1; 
				m->data()[64][1] = 5.6; 	m->data()[64][2] = 2.9; 	m->data()[64][3] = 3.6; 	m->data()[64][4] = 1.3; 	m->data()[64][0] = 1; 
				m->data()[65][1] = 6.7; 	m->data()[65][2] = 3.1; 	m->data()[65][3] = 4.4; 	m->data()[65][4] = 1.4; 	m->data()[65][0] = 1; 
				m->data()[66][1] = 5.6; 	m->data()[66][2] = 3; 	m->data()[66][3] = 4.5; 	m->data()[66][4] = 1.5; 	m->data()[66][0] = 1; 
				m->data()[67][1] = 5.8; 	m->data()[67][2] = 2.7; 	m->data()[67][3] = 4.1; 	m->data()[67][4] = 1; 	m->data()[67][0] = 1; 
				m->data()[68][1] = 6.2; 	m->data()[68][2] = 2.2; 	m->data()[68][3] = 4.5; 	m->data()[68][4] = 1.5; 	m->data()[68][0] = 1; 
				m->data()[69][1] = 5.6; 	m->data()[69][2] = 2.5; 	m->data()[69][3] = 3.9; 	m->data()[69][4] = 1.1; 	m->data()[69][0] = 1; 
				m->data()[70][1] = 5.9; 	m->data()[70][2] = 3.2; 	m->data()[70][3] = 4.8; 	m->data()[70][4] = 1.8; 	m->data()[70][0] = 1; 
				m->data()[71][1] = 6.1; 	m->data()[71][2] = 2.8; 	m->data()[71][3] = 4; 	m->data()[71][4] = 1.3; 	m->data()[71][0] = 1; 
				m->data()[72][1] = 6.3; 	m->data()[72][2] = 2.5; 	m->data()[72][3] = 4.9; 	m->data()[72][4] = 1.5; 	m->data()[72][0] = 1; 
				m->data()[73][1] = 6.1; 	m->data()[73][2] = 2.8; 	m->data()[73][3] = 4.7; 	m->data()[73][4] = 1.2; 	m->data()[73][0] = 1; 
				m->data()[74][1] = 6.4; 	m->data()[74][2] = 2.9; 	m->data()[74][3] = 4.3; 	m->data()[74][4] = 1.3; 	m->data()[74][0] = 1; 
				m->data()[75][1] = 6.6; 	m->data()[75][2] = 3; 	m->data()[75][3] = 4.4; 	m->data()[75][4] = 1.4; 	m->data()[75][0] = 1; 
				m->data()[76][1] = 6.8; 	m->data()[76][2] = 2.8; 	m->data()[76][3] = 4.8; 	m->data()[76][4] = 1.4; 	m->data()[76][0] = 1; 
				m->data()[77][1] = 6.7; 	m->data()[77][2] = 3; 	m->data()[77][3] = 5; 	m->data()[77][4] = 1.7; 	m->data()[77][0] = 1; 
				m->data()[78][1] = 6; 	m->data()[78][2] = 2.9; 	m->data()[78][3] = 4.5; 	m->data()[78][4] = 1.5; 	m->data()[78][0] = 1; 
				m->data()[79][1] = 5.7; 	m->data()[79][2] = 2.6; 	m->data()[79][3] = 3.5; 	m->data()[79][4] = 1; 	m->data()[79][0] = 1; 
				m->data()[80][1] = 5.5; 	m->data()[80][2] = 2.4; 	m->data()[80][3] = 3.8; 	m->data()[80][4] = 1.1; 	m->data()[80][0] = 1; 
				m->data()[81][1] = 5.5; 	m->data()[81][2] = 2.4; 	m->data()[81][3] = 3.7; 	m->data()[81][4] = 1; 	m->data()[81][0] = 1; 
				m->data()[82][1] = 5.8; 	m->data()[82][2] = 2.7; 	m->data()[82][3] = 3.9; 	m->data()[82][4] = 1.2; 	m->data()[82][0] = 1; 
				m->data()[83][1] = 6; 	m->data()[83][2] = 2.7; 	m->data()[83][3] = 5.1; 	m->data()[83][4] = 1.6; 	m->data()[83][0] = 1; 
				m->data()[84][1] = 5.4; 	m->data()[84][2] = 3; 	m->data()[84][3] = 4.5; 	m->data()[84][4] = 1.5; 	m->data()[84][0] = 1; 
				m->data()[85][1] = 6; 	m->data()[85][2] = 3.4; 	m->data()[85][3] = 4.5; 	m->data()[85][4] = 1.6; 	m->data()[85][0] = 1; 
				m->data()[86][1] = 6.7; 	m->data()[86][2] = 3.1; 	m->data()[86][3] = 4.7; 	m->data()[86][4] = 1.5; 	m->data()[86][0] = 1; 
				m->data()[87][1] = 6.3; 	m->data()[87][2] = 2.3; 	m->data()[87][3] = 4.4; 	m->data()[87][4] = 1.3; 	m->data()[87][0] = 1; 
				m->data()[88][1] = 5.6; 	m->data()[88][2] = 3; 	m->data()[88][3] = 4.1; 	m->data()[88][4] = 1.3; 	m->data()[88][0] = 1; 
				m->data()[89][1] = 5.5; 	m->data()[89][2] = 2.5; 	m->data()[89][3] = 4; 	m->data()[89][4] = 1.3; 	m->data()[89][0] = 1; 
				m->data()[90][1] = 5.5; 	m->data()[90][2] = 2.6; 	m->data()[90][3] = 4.4; 	m->data()[90][4] = 1.2; 	m->data()[90][0] = 1; 
				m->data()[91][1] = 6.1; 	m->data()[91][2] = 3; 	m->data()[91][3] = 4.6; 	m->data()[91][4] = 1.4; 	m->data()[91][0] = 1; 
				m->data()[92][1] = 5.8; 	m->data()[92][2] = 2.6; 	m->data()[92][3] = 4; 	m->data()[92][4] = 1.2; 	m->data()[92][0] = 1; 
				m->data()[93][1] = 5; 	m->data()[93][2] = 2.3; 	m->data()[93][3] = 3.3; 	m->data()[93][4] = 1; 	m->data()[93][0] = 1; 
				m->data()[94][1] = 5.6; 	m->data()[94][2] = 2.7; 	m->data()[94][3] = 4.2; 	m->data()[94][4] = 1.3; 	m->data()[94][0] = 1; 
				m->data()[95][1] = 5.7; 	m->data()[95][2] = 3; 	m->data()[95][3] = 4.2; 	m->data()[95][4] = 1.2; 	m->data()[95][0] = 1; 
				m->data()[96][1] = 5.7; 	m->data()[96][2] = 2.9; 	m->data()[96][3] = 4.2; 	m->data()[96][4] = 1.3; 	m->data()[96][0] = 1; 
				m->data()[97][1] = 6.2; 	m->data()[97][2] = 2.9; 	m->data()[97][3] = 4.3; 	m->data()[97][4] = 1.3; 	m->data()[97][0] = 1; 
				m->data()[98][1] = 5.1; 	m->data()[98][2] = 2.5; 	m->data()[98][3] = 3; 	m->data()[98][4] = 1.1; 	m->data()[98][0] = 1; 
				m->data()[99][1] = 5.7; 	m->data()[99][2] = 2.8; 	m->data()[99][3] = 4.1; 	m->data()[99][4] = 1.3; 	m->data()[99][0] = 1; 
				m->data()[100][1] = 6.3; 	m->data()[100][2] = 3.3; 	m->data()[100][3] = 6; 	m->data()[100][4] = 2.5; 	m->data()[100][0] = 2; 
				m->data()[101][1] = 5.8; 	m->data()[101][2] = 2.7; 	m->data()[101][3] = 5.1; 	m->data()[101][4] = 1.9; 	m->data()[101][0] = 2; 
				m->data()[102][1] = 7.1; 	m->data()[102][2] = 3; 	m->data()[102][3] = 5.9; 	m->data()[102][4] = 2.1; 	m->data()[102][0] = 2; 
				m->data()[103][1] = 6.3; 	m->data()[103][2] = 2.9; 	m->data()[103][3] = 5.6; 	m->data()[103][4] = 1.8; 	m->data()[103][0] = 2; 
				m->data()[104][1] = 6.5; 	m->data()[104][2] = 3; 	m->data()[104][3] = 5.8; 	m->data()[104][4] = 2.2; 	m->data()[104][0] = 2; 
				m->data()[105][1] = 7.6; 	m->data()[105][2] = 3; 	m->data()[105][3] = 6.6; 	m->data()[105][4] = 2.1; 	m->data()[105][0] = 2; 
				m->data()[106][1] = 4.9; 	m->data()[106][2] = 2.5; 	m->data()[106][3] = 4.5; 	m->data()[106][4] = 1.7; 	m->data()[106][0] = 2; 
				m->data()[107][1] = 7.3; 	m->data()[107][2] = 2.9; 	m->data()[107][3] = 6.3; 	m->data()[107][4] = 1.8; 	m->data()[107][0] = 2; 
				m->data()[108][1] = 6.7; 	m->data()[108][2] = 2.5; 	m->data()[108][3] = 5.8; 	m->data()[108][4] = 1.8; 	m->data()[108][0] = 2; 
				m->data()[109][1] = 7.2; 	m->data()[109][2] = 3.6; 	m->data()[109][3] = 6.1; 	m->data()[109][4] = 2.5; 	m->data()[109][0] = 2; 
				m->data()[110][1] = 6.5; 	m->data()[110][2] = 3.2; 	m->data()[110][3] = 5.1; 	m->data()[110][4] = 2; 	m->data()[110][0] = 2; 
				m->data()[111][1] = 6.4; 	m->data()[111][2] = 2.7; 	m->data()[111][3] = 5.3; 	m->data()[111][4] = 1.9; 	m->data()[111][0] = 2; 
				m->data()[112][1] = 6.8; 	m->data()[112][2] = 3; 	m->data()[112][3] = 5.5; 	m->data()[112][4] = 2.1; 	m->data()[112][0] = 2; 
				m->data()[113][1] = 5.7; 	m->data()[113][2] = 2.5; 	m->data()[113][3] = 5; 	m->data()[113][4] = 2; 	m->data()[113][0] = 2; 
				m->data()[114][1] = 5.8; 	m->data()[114][2] = 2.8; 	m->data()[114][3] = 5.1; 	m->data()[114][4] = 2.4; 	m->data()[114][0] = 2; 
				m->data()[115][1] = 6.4; 	m->data()[115][2] = 3.2; 	m->data()[115][3] = 5.3; 	m->data()[115][4] = 2.3; 	m->data()[115][0] = 2; 
				m->data()[116][1] = 6.5; 	m->data()[116][2] = 3; 	m->data()[116][3] = 5.5; 	m->data()[116][4] = 1.8; 	m->data()[116][0] = 2; 
				m->data()[117][1] = 7.7; 	m->data()[117][2] = 3.8; 	m->data()[117][3] = 6.7; 	m->data()[117][4] = 2.2; 	m->data()[117][0] = 2; 
				m->data()[118][1] = 7.7; 	m->data()[118][2] = 2.6; 	m->data()[118][3] = 6.9; 	m->data()[118][4] = 2.3; 	m->data()[118][0] = 2; 
				m->data()[119][1] = 6; 	m->data()[119][2] = 2.2; 	m->data()[119][3] = 5; 	m->data()[119][4] = 1.5; 	m->data()[119][0] = 2; 
				m->data()[120][1] = 6.9; 	m->data()[120][2] = 3.2; 	m->data()[120][3] = 5.7; 	m->data()[120][4] = 2.3; 	m->data()[120][0] = 2; 
				m->data()[121][1] = 5.6; 	m->data()[121][2] = 2.8; 	m->data()[121][3] = 4.9; 	m->data()[121][4] = 2; 	m->data()[121][0] = 2; 
				m->data()[122][1] = 7.7; 	m->data()[122][2] = 2.8; 	m->data()[122][3] = 6.7; 	m->data()[122][4] = 2; 	m->data()[122][0] = 2; 
				m->data()[123][1] = 6.3; 	m->data()[123][2] = 2.7; 	m->data()[123][3] = 4.9; 	m->data()[123][4] = 1.8; 	m->data()[123][0] = 2; 
				m->data()[124][1] = 6.7; 	m->data()[124][2] = 3.3; 	m->data()[124][3] = 5.7; 	m->data()[124][4] = 2.1; 	m->data()[124][0] = 2; 
				m->data()[125][1] = 7.2; 	m->data()[125][2] = 3.2; 	m->data()[125][3] = 6; 	m->data()[125][4] = 1.8; 	m->data()[125][0] = 2; 
				m->data()[126][1] = 6.2; 	m->data()[126][2] = 2.8; 	m->data()[126][3] = 4.8; 	m->data()[126][4] = 1.8; 	m->data()[126][0] = 2; 
				m->data()[127][1] = 6.1; 	m->data()[127][2] = 3; 	m->data()[127][3] = 4.9; 	m->data()[127][4] = 1.8; 	m->data()[127][0] = 2; 
				m->data()[128][1] = 6.4; 	m->data()[128][2] = 2.8; 	m->data()[128][3] = 5.6; 	m->data()[128][4] = 2.1; 	m->data()[128][0] = 2; 
				m->data()[129][1] = 7.2; 	m->data()[129][2] = 3; 	m->data()[129][3] = 5.8; 	m->data()[129][4] = 1.6; 	m->data()[129][0] = 2; 
				m->data()[130][1] = 7.4; 	m->data()[130][2] = 2.8; 	m->data()[130][3] = 6.1; 	m->data()[130][4] = 1.9; 	m->data()[130][0] = 2; 
				m->data()[131][1] = 7.9; 	m->data()[131][2] = 3.8; 	m->data()[131][3] = 6.4; 	m->data()[131][4] = 2; 	m->data()[131][0] = 2; 
				m->data()[132][1] = 6.4; 	m->data()[132][2] = 2.8; 	m->data()[132][3] = 5.6; 	m->data()[132][4] = 2.2; 	m->data()[132][0] = 2; 
				m->data()[133][1] = 6.3; 	m->data()[133][2] = 2.8; 	m->data()[133][3] = 5.1; 	m->data()[133][4] = 1.5; 	m->data()[133][0] = 2; 
				m->data()[134][1] = 6.1; 	m->data()[134][2] = 2.6; 	m->data()[134][3] = 5.6; 	m->data()[134][4] = 1.4; 	m->data()[134][0] = 2; 
				m->data()[135][1] = 7.7; 	m->data()[135][2] = 3; 	m->data()[135][3] = 6.1; 	m->data()[135][4] = 2.3; 	m->data()[135][0] = 2; 
				m->data()[136][1] = 6.3; 	m->data()[136][2] = 3.4; 	m->data()[136][3] = 5.6; 	m->data()[136][4] = 2.4; 	m->data()[136][0] = 2; 
				m->data()[137][1] = 6.4; 	m->data()[137][2] = 3.1; 	m->data()[137][3] = 5.5; 	m->data()[137][4] = 1.8; 	m->data()[137][0] = 2; 
				m->data()[138][1] = 6; 		m->data()[138][2] = 3; 	m->data()[138][3] = 4.8; 	m->data()[138][4] = 1.8; 	m->data()[138][0] = 2; 
				m->data()[139][1] = 6.9; 	m->data()[139][2] = 3.1; 	m->data()[139][3] = 5.4; 	m->data()[139][4] = 2.1; 	m->data()[139][0] = 2; 
				m->data()[140][1] = 6.7; 	m->data()[140][2] = 3.1; 	m->data()[140][3] = 5.6; 	m->data()[140][4] = 2.4; 	m->data()[140][0] = 2; 
				m->data()[141][1] = 6.9; 	m->data()[141][2] = 3.1; 	m->data()[141][3] = 5.1; 	m->data()[141][4] = 2.3; 	m->data()[141][0] = 2; 
				m->data()[142][1] = 5.8; 	m->data()[142][2] = 2.7; 	m->data()[142][3] = 5.1; 	m->data()[142][4] = 1.9; 	m->data()[142][0] = 2; 
				m->data()[143][1] = 6.8; 	m->data()[143][2] = 3.2; 	m->data()[143][3] = 5.9; 	m->data()[143][4] = 2.3; 	m->data()[143][0] = 2; 
				m->data()[144][1] = 6.7; 	m->data()[144][2] = 3.3; 	m->data()[144][3] = 5.7; 	m->data()[144][4] = 2.5; 	m->data()[144][0] = 2; 
				m->data()[145][1] = 6.7; 	m->data()[145][2] = 3; 	m->data()[145][3] = 5.2; 	m->data()[145][4] = 2.3; 	m->data()[145][0] = 2; 
				m->data()[146][1] = 6.3; 	m->data()[146][2] = 2.5; 	m->data()[146][3] = 5; 	m->data()[146][4] = 1.9; 	m->data()[146][0] = 2; 
				m->data()[147][1] = 6.5; 	m->data()[147][2] = 3; 	m->data()[147][3] = 5.2; 	m->data()[147][4] = 2; 	m->data()[147][0] = 2; 
				m->data()[148][1] = 6.2; 	m->data()[148][2] = 3.4; 	m->data()[148][3] = 5.4; 	m->data()[148][4] = 2.3; 	m->data()[148][0] = 2; 
				m->data()[149][1] = 5.9; 	m->data()[149][2] = 3; 	m->data()[149][3] = 5.1; 	m->data()[149][4] = 1.8; 	m->data()[149][0] = 2; 

				return m;

			};

			/**
			 * Obt�m a matriz de amostras de rendimentos para uso no Naive Bayes.<br />
			 *
			 * @return o Matrix que representa o conjunto de amostras
			 */
			PUBLIC static Matrix *getNaiveBayesPlayTennisDS() {

				Matrix *m = new Matrix(14, 5);

				m->data()[0][0] = 0;	m->data()[0][1] = 0;	m->data()[0][2] = 0;	m->data()[0][3] = 0;	m->data()[0][4] = 0;
				m->data()[1][0] = 0;	m->data()[1][1] = 0;	m->data()[1][2] = 0;	m->data()[1][3] = 1;	m->data()[1][4] = 0;
				m->data()[2][0] = 1;	m->data()[2][1] = 0;	m->data()[2][2] = 0;	m->data()[2][3] = 0;	m->data()[2][4] = 1;
				m->data()[3][0] = 2;	m->data()[3][1] = 1;	m->data()[3][2] = 0;	m->data()[3][3] = 0;	m->data()[3][4] = 1;
				m->data()[4][0] = 2;	m->data()[4][1] = 2;	m->data()[4][2] = 1;	m->data()[4][3] = 0;	m->data()[4][4] = 1;
				m->data()[5][0] = 2;	m->data()[5][1] = 2;	m->data()[5][2] = 1;	m->data()[5][3] = 1;	m->data()[5][4] = 0;
				m->data()[6][0] = 1;	m->data()[6][1] = 2;	m->data()[6][2] = 1;	m->data()[6][3] = 1;	m->data()[6][4] = 1;
				m->data()[7][0] = 0;	m->data()[7][1] = 1;	m->data()[7][2] = 0;	m->data()[7][3] = 0;	m->data()[7][4] = 0;
				m->data()[8][0] = 0;	m->data()[8][1] = 2;	m->data()[8][2] = 1;	m->data()[8][3] = 0;	m->data()[8][4] = 1;
				m->data()[9][0] = 3;	m->data()[9][1] = 1;	m->data()[9][2] = 1;	m->data()[9][3] = 0;	m->data()[9][4] = 1;
				m->data()[10][0] = 0;	m->data()[10][1] = 1;	m->data()[10][2] = 1;	m->data()[10][3] = 1;	m->data()[10][4] = 1;
				m->data()[11][0] = 1;	m->data()[11][1] = 1;	m->data()[11][2] = 0;	m->data()[11][3] = 1;	m->data()[11][4] = 1;
				m->data()[12][0] = 1;	m->data()[12][1] = 0;	m->data()[12][2] = 1;	m->data()[12][3] = 0;	m->data()[12][4] = 1;
				m->data()[13][0] = 2;	m->data()[13][1] = 1;	m->data()[13][2] = 0;	m->data()[13][3] = 1;	m->data()[13][4] = 0;

				return m;

			};

			/**
			 * Obt�m a matriz de amostras de rendimentos para uso no Naive Bayes.<br />
			 *
			 * @return o Matrix que representa o conjunto de amostras
			 */
			PUBLIC static Matrix *getNaiveBayesFirstDS() {

				Matrix *m = new Matrix(10, 4);

				m->data()[0][0]=1;	m->data()[0][1]=0;	m->data()[0][2]=2;	m->data()[0][3]=0;
				m->data()[1][0]=0;	m->data()[1][1]=1;	m->data()[1][2]=1;	m->data()[1][3]=0;
				m->data()[2][0]=0;	m->data()[2][1]=0;	m->data()[2][2]=0;	m->data()[2][3]=0;
				m->data()[3][0]=1;	m->data()[3][1]=1;	m->data()[3][2]=2;	m->data()[3][3]=0;
				m->data()[4][0]=0;	m->data()[4][1]=2;	m->data()[4][2]=1;	m->data()[4][3]=1;
				m->data()[5][0]=0;	m->data()[5][1]=1;	m->data()[5][2]=0;	m->data()[5][3]=0;
				m->data()[6][0]=1;	m->data()[6][1]=2;	m->data()[6][2]=2;	m->data()[6][3]=0;
				m->data()[7][0]=0;	m->data()[7][1]=0;	m->data()[7][2]=1;	m->data()[7][3]=1;
				m->data()[8][0]=0;	m->data()[8][1]=1;	m->data()[8][2]=0;	m->data()[8][3]=0;
				m->data()[9][0]=0;	m->data()[9][1]=0;	m->data()[9][2]=1;	m->data()[9][3]=1;

				return m;

			};

			/**
			 * Obt�m a matriz de amostras de rendimentos para uso no Naive Bayes.<br />
			 *
			 * @return o Matrix que representa o conjunto de amostras
			 */
			PUBLIC static Matrix *getNaiveBayesSecondDS() {

				Matrix *m = new Matrix(10, 2);

				m->data()[0][0]=0;	m->data()[0][1]=0;
				m->data()[1][0]=0;	m->data()[1][1]=0;
				m->data()[2][0]=0;	m->data()[2][1]=0;
				m->data()[3][0]=1;	m->data()[3][1]=1;
				m->data()[4][0]=1;	m->data()[4][1]=0;
				m->data()[5][0]=1;	m->data()[5][1]=1;
				m->data()[6][0]=1;	m->data()[6][1]=1;
				m->data()[7][0]=1;	m->data()[7][1]=0;
				m->data()[8][0]=0;	m->data()[8][1]=1;
				m->data()[9][0]=1;	m->data()[9][1]=1;

				return m;
			};

		}; // class SampleDataSets

	} // namespace commons

} // namespace pel208

#endif