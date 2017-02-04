#pragma once

#ifndef __DYNAMIC_PROGRAMMING_H__
#define __DYNAMIC_PROGRAMMING_H__

#include <inc\Utils.h>
#include <inc\Matrix.h>

#include <inc\RLConstants.h>

#include <inc\SmallGridWorld.h>
#include <inc\SmallGridWorldState.h>

using namespace pel208::commons;

namespace pel208 {

	namespace week6 {

		/**
		 * Classe de implementa��o de programa��o din�mica.<br />
		 *
		 * @author arrebola
		 */
		class DynamicProgramming {

		private:

		public:
			/**
			 * Construtor.
			 */
			DynamicProgramming() {
			};

			/**
			 * Destrutor.
			 */
			~DynamicProgramming() {
			};

			/**
			 * Calcula o valor de V de um determinado estado.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param state
			 *					o SmallGridWorldState que representa o estado
			 * @param stateIdx
			 *					o <code>size_t</code> que representa o �ndice do estado
			 * @param gamma
			 *					o <code>double</code> que representa o gamma (o desconto)
			 * @param debug
			 *					indica se as mensagens de depura��o devem ser exibidas
			 *
			 * @return o <code>double</code> que representa o valor de V
			 */
			PRIVATE static double evaluatePolicy(
					IN SmallGridWorld *world, 
					IN SmallGridWorldState *state, 
					IN size_t stateIdx, 
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				double sum = 0.0f;

				Matrix *S = state->getNextStates();
				Matrix *P = state->getTransitionProbabilities();
				Matrix *R = state->getTransitionRewards();

				// sum s' [ P (s, a, s') * [ R(s, a, s') + gamma * V(s') ]
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {

					register size_t s = (size_t)S->data()[0][idx];
					register double p = P->data()[0][idx];
					register double r = R->data()[0][idx];
					register double v = world->getState(s)->getValue();
					if (debug) {
						Logger::log("P(%d,%d,%d)=%f, R(%d,%d,%d)=%f, V(%d)=%f\n", 
							stateIdx, idx, s, p, stateIdx, idx, s, r, v);
					}

					sum += p * (r + (gamma * v));

				}

				if (debug) {
					Logger::log(">> sum=%f\n", sum);
				}

				return sum;

			};

			/**
			 * Avalia a melhoria de pol�tica.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param state
			 *					o SmallGridWorldState que representa o estado
			 * @param stateIdx
			 *					o <code>size_t</code> que representa o �ndice do estado
			 * @param gamma
			 *					o <code>double</code> que representa o gamma (o desconto)
			 * @param debug
			 *					indica se as mensagens de depura��o devem ser exibidas
			 *
			 * @return o Matrix que representa a nova pol�tica
			 */
			PRIVATE static Matrix *evaluatePolicyImprovement(
					IN SmallGridWorld *world, 
					IN SmallGridWorldState *state, 
					IN size_t stateIdx,
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				Matrix *S = state->getNextStates();
				Matrix *P = state->getTransitionProbabilities();
				Matrix *R = state->getTransitionRewards();

				Matrix *P_prime = P->clone();

				// sum s' [ P (s, a, s') * [ R(s, a, s') + gamma * V(s') ]
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					
					register size_t s = (size_t)S->data()[0][idx];
					register double p = P->data()[0][idx];
					register double r = R->data()[0][idx];
					register double v = world->getState(s)->getValue();
					register double value = p * (r + gamma * v);

					if (debug) {
						Logger::log("P(%d,%d,%d)=%f, R(%d,%d,%d)=%f, V(%d)=%f\n", 
							stateIdx, idx, s, p, stateIdx, idx, s, r, v);
					}

					P_prime->data()[0][idx] = value;

				}
				
				double max = DBL_MIN;
				size_t maxRowId = 0;
				size_t maxColIdx = 0;
				if (!P_prime->max(&max, &maxRowId, &maxColIdx)) {
					return P->clone();
				}
				
				if (std::abs(max - 0.0f) < pel208::commons::PRECISION) {
					return P->clone();
				}

				std::vector<size_t> indexes;
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					if (std::abs(max - P_prime->data()[0][idx]) < pel208::commons::PRECISION) {
						indexes.push_back(idx);
					}
				}
					
				P_prime->fill(0.0f);

				size_t size = indexes.size();
				double probability = 1.0f / (size * 1.0f);
				for (size_t idx = 0; idx < size; idx++) {
					P_prime->data()[0][indexes.at(idx)] = probability;
				}

				return P_prime;

			};
			
			/** 
			 * Avalia o problema do <i>small grid world</i> utilizando a t�cnica de itera��o de pol�ticas.<br />
			 * O primeiro e o �ltimo estado do grid s�o considerados estados terminais.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param newWorld
			 *					o SmallGridWorld que representa o <i>small grid world</i> final
			 * @param iteractions
			 *					o <code>size_t</code> que representa a quantidade de itera��es
			 * @param theta
			 *					o <code>double</code> que representa o theta (a precis�o)
			 * @param gamma
			 *					o <code>double</code> que representa o gamma (o desconto)
			 * @param debug
			 *					indica se as mensagens de depura��o devem ser exibidas
			 *
			 * @return <code>true</code> caso a avalia��o tenha sido bem sucedida; do contr�rio <code>false</code>
			 */
			PUBLIC static bool evaluateUsingPolicyIteration(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **newWorld, 
					IN OUT size_t *iteractions,
					IN double theta = DEFAULT_THETA, 
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world) || theta < 0.0f || gamma < 0.0f) {
					throw new IllegalParameterException();
				}

				size_t stateCount = world->getStateCount();

				SmallGridWorld *currentWorld = world->clone();
				*newWorld = currentWorld->clone();

				*iteractions = 0;
				double delta = 0.0f;
				do {

					delta = 0.0f;

					// c�lculo da pol�tica
					for (size_t stateIdx = 1; stateIdx < stateCount - 1; stateIdx++) {
						SmallGridWorldState *state = currentWorld->getState(stateIdx);
						register double curValue = state->getValue();
						register double newValue = evaluatePolicy(currentWorld, state, stateIdx, gamma, debug);
						(*newWorld)->getState(stateIdx)->setValue(newValue);
						delta = std::max(delta, std::abs(curValue - newValue));
					}

					// melhoria da pol�tica
					for (size_t stateIdx = 1; stateIdx < stateCount - 1; stateIdx++) {
						SmallGridWorldState *newState = (*newWorld)->getState(stateIdx);
						register Matrix *P_prime = evaluatePolicyImprovement(*newWorld, newState, stateIdx, gamma, debug);
						newState->updateTransitionProbabilities(P_prime);
						delete P_prime;
					}

					delete currentWorld;
					currentWorld = (*newWorld);

					(*newWorld) = (*newWorld)->clone();

					(*iteractions)++;

				} while (delta > theta && (*iteractions) < MAX_ITERATIONS);
				
				return true;

			};

			/**
			 * Avalia o problema do <i>small grid world</i> utilizando a t�cnica de itera��o de valores.<br />
			 * O primeiro e o �ltimo estado do grid s�o considerados estados terminais.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param newWorld
			 *					o SmallGridWorld que representa o <i>small grid world</i> final
			 * @param iteractions
			 *					o <code>size_t</code> que representa a quantidade de itera��es
			 * @param theta
			 *					o <code>double</code> que representa o theta (a precis�o)
			 * @param gamma
			 *					o <code>double</code> que representa o gamma (o desconto)
			 * @param debug
			 *					indica se as mensagens de depura��o devem ser exibidas
			 *
			 * @return <code>true</code> caso a avalia��o tenha sido bem sucedida; do contr�rio <code>false</code>
			 */
			PUBLIC static bool evaluateUsingValueIteration(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **newWorld, 
					IN OUT size_t *iteractions,
					IN double theta = DEFAULT_THETA, 
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world) || theta < 0.0f || gamma < 0.0f) {
					throw new IllegalParameterException();
				}

				size_t stateCount = world->getStateCount();

				SmallGridWorld *currentWorld = world->clone();
				*newWorld = currentWorld->clone();

				// faz a itera��o de valores
				*iteractions = 0;
				double delta = 0.0f;
				do {

					delta = 0.0f;

					for (size_t stateIdx = 1; stateIdx < stateCount - 1; stateIdx++) {
						
						SmallGridWorldState *state = currentWorld->getState(stateIdx);
						register double curValue = state->getValue();
						register double newValue = evaluatePolicy(currentWorld, state, stateIdx, gamma, debug);

						(*newWorld)->getState(stateIdx)->setValue(newValue);

						delta = std::max(delta, std::abs(curValue - newValue));

					}

					delete currentWorld;
					currentWorld = (*newWorld);

					(*newWorld) = (*newWorld)->clone();

					(*iteractions)++;

				} while (delta > theta && (*iteractions) < MAX_ITERATIONS);
				
				// calcula a pol�tica
				for (size_t stateIdx = 1; stateIdx < stateCount - 1; stateIdx++) {
					SmallGridWorldState *state = (*newWorld)->getState(stateIdx);
					register Matrix *P_prime = evaluatePolicyImprovement((*newWorld), state, stateIdx, gamma, debug);
					state->updateTransitionProbabilities(P_prime);
					delete P_prime;
				}
					
				return true;

			};

		}; /* class DynamicProgramming */

	} /* namespace week6 */

} /* namespace pel208 */

#endif /* __DYNAMIC_PROGRAMMING_H__ */
