#pragma once

#ifndef __ON_POLICY_MONTE_CARLO_H__
#define __ON_POLICY_MONTE_CARLO_H__

#include <array>

#include <inc\Utils.h>

#include <inc\Matrix.h>
#include <inc\Random.h>

#include <inc\SmallGridWorld.h>
#include <inc\SmallGridWorldState.h>

#define MAX_EPISODES					UINT_MAX - 1
#define MAX_EPISODE_LEN					256
#define DEFAULT_GAMMA					1.0f
#define DEFAULT_EPSILON					0.1f

using namespace pel208::commons;
using namespace pel208::week6;
using namespace pel208::week7;

namespace pel208 {

	namespace week7 {

		/**
		 * Classe que representa um par de estado-ação.<br />
		 *
		 * @author arrebola
		 */
		class StateActionPair {
		private:
			size_t state;
			size_t action;
			SmallGridWorldState *stateInfo;

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param state
			 *					 o <code>size_t</code> que representa o estado
			 * @param action
			 *					 o <code>size_t</code> que representa a ação
			 * @param stateInfo
			 *					o SmallGridWorldState que representa as informações do estado
			 */
			StateActionPair(IN size_t state, IN size_t action, IN SmallGridWorldState *stateInfo = NULL) {
				this->state = state;
				this->action = action;
				this->stateInfo = stateInfo;
			};
			
			/**
			 * Destrutor.<br />
			 */
			~StateActionPair() {
			};
			
			/**
			 * Retorna o estado.<br />
			 *
			 * @return o <code>size_t</code> que representa o estado
			 */
			PUBLIC size_t getState() {
				return this->state;
			};

			/**
			 * Retorna o ação.<br />
			 *
			 * @return o <code>size_t</code> que representa a ação
			 */
			PUBLIC size_t getAction() {
				return this->action;
			};

			/**
			 * Retorna informações sobre o estado.<br />
			 *
			 * @return o SmallGridWorldState que representa as informações do estado
			 */
			PUBLIC SmallGridWorldState *getStateInfo() {
				return this->stateInfo;
			};
		
		}; /* class StateActionPair */

		/**
		 * Classe que representa um episódio.<br />
		 *
		 * @author arrebola
		 */
		class Episode {
		private:
			std::vector<StateActionPair*> *pairs;

		public:
			/**
			 * Construtor.<br />
			 */
			Episode() {
				this->pairs = new std::vector<StateActionPair*>();
			};

			/**
			 * Destrutor.<br />
			 */
			~Episode() {
				delete this->pairs;
			};

			/**
			 * Adição um par estado-ação ao episódio.<br />
			 * 
			 * @param pair
			 *					o StateActionPair que representa um par de estado-ação
			 */
			PUBLIC void add(IN StateActionPair* pair) {

				if (Utils::isInvalidHandle(pair)) {
					throw new IllegalParameterException();
				}

				this->pairs->push_back(pair);

			};

			/**
			 * Retorna o tamanho do episódio.<br />
			 *
			 * @return o <code>size_t</code> que representa o tamanho do episódio
			 */
			PUBLIC size_t size() {
				return this->pairs->size();
			};

			/**
			 * Retorna os pares de estado-ação contidos no episódio.<br />
			 *
			 * @return o <code>std::vector</code> de StateActionPair que representa os pares de estado-ação
			 */
			PUBLIC std::vector<StateActionPair*> *getPairs() {
				return new std::vector<StateActionPair*>(this->pairs->begin(), this->pairs->end());
			};

			/**
			 * Imprime detalhes sobre o episódio.
			 */
			PUBLIC void dump() {

				size_t size = this->pairs->size();

				Logger::log("Episodio com %d estados...\n", size);
				Logger::log("");

				size_t counter = 1;
				for (std::vector<StateActionPair*>::iterator iterator =  this->pairs->begin() ; 
						iterator != this->pairs->end(); 
						++iterator) {

					register size_t stateIdx = (*iterator)->getState();
					register size_t actionIdx = (*iterator)->getAction();
					register SmallGridWorldState *state = (*iterator)->getStateInfo();

					Logger::logWithoutTimestamp("(s=%02d,%s) ", 
						stateIdx, 
						(actionIdx == 0 ? "U" : ((actionIdx == 1) ? "D" : ((actionIdx == 2) ? "L" : "R"))));

					if (counter++ % 8 == 0) {
						Logger::logWithoutTimestamp("\n");
						Logger::log("");
					}

				}

				Logger::logWithoutTimestamp("\n");

			};

		}; /* class Episode */

		/**
		 * Implementação do método On Policy Monte Carlo.<br />
		 *
		 * @author arrebola
		 */
		class OnPolicyMonteCarlo {

		private:
			const static int DEFAULT_REWARD = -1;	

		public:
			/**
			 * Construtor.<br />
			 */
			OnPolicyMonteCarlo() {
			};

			/**
			 * Destrutor.<br />
			 */
			~OnPolicyMonteCarlo() {
			};

			/**
			 * Seleciona um estado aleatório diferente dos alvos seguindo uma distribuição uniforme.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 *
			 * @return <code>size_t</code> que representa o estado
			 */
			PRIVATE static size_t selectRandomState(IN SmallGridWorld *world) {

				if (Utils::isInvalidHandle(world) || world->getStateCount() < 1) {
					throw new IllegalParameterException();
				}

				return Random::nextUint(1, world->getStateCount() - 1);

			};

			/**
			 * Seleciona uma ação aleatória seguindo a distribuição determinada pela política de transição do estado.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param state
			 *					o SmallGridWorldState que representa o estado
			 *
			 * @return <code>size_t</code> que representa a ação
			 */
			PRIVATE static size_t selectRandomAction(IN SmallGridWorld *world, IN SmallGridWorldState *state) {

				if (Utils::isInvalidHandle(world) || Utils::isInvalidHandle(state)) {
					throw new IllegalParameterException();
				}

				Matrix *P = state->getTransitionProbabilities();

				std::discrete_distribution<size_t>::param_type::_Noinit noInit;
				std::discrete_distribution<size_t>::param_type pType(noInit);
				for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) {
					pType._Pvec.push_back(P->data()[0][idx]);
				}
				pType._Init();

				std::random_device generator;
				std::discrete_distribution<size_t> distribution(pType);

				return distribution(generator);
			
			};

			/**
			 * Gera um episódio.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param P
			 *					o Matrix que representa a matriz de probabilidades
			 * @param episode
			 *					o Episode que representa o episódio
			 *
			 * @return <code>true</code> caso a geração tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool generateEpisode(IN SmallGridWorld *world, IN OUT Episode **episode) {

				(*episode) = new Episode();

				size_t stateIdx = selectRandomState(world);
				
				while (stateIdx != 0 && stateIdx != 15 && (*episode)->size() < MAX_EPISODE_LEN) {
					SmallGridWorldState *state = world->getState(stateIdx);
					register size_t actionIdx = selectRandomAction(world, state);
					(*episode)->add(new StateActionPair(stateIdx, actionIdx, state));
					stateIdx = (size_t)state->getNextStates()->data()[0][actionIdx];
				}

				return ((*episode)->size() < MAX_EPISODE_LEN);

			};

			/**
			 * Avalia o problema do <i>small grid world</i> utilizando a técnica de monte carlo com controle de política.<br />
			 * O primeiro e o último estado do grid são considerados estados terminais.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param goal
			 *					o SmallGridWorld que representa o <i>small grid world</i> final
			 * @param maxIterations
			 *					o <code>size_t</code> que representa a quantidade máxima de iterações
			 * @param maxEpisodes
			 *					o <code>size_t</code> que representa a quantidade máxima de episódios
			 * @param epsilon
			 *					o <code>double</code> que representa o epsilon para a geração de políticas
			 * @param debug
			 *					indica se as mensagens de depuração devem ser exibidas
			 *
			 * @return <code>true</code> caso a avaliação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC static bool evaluate(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **goal,
					IN size_t maxEpisodes = MAX_EPISODES,
					IN double epsilon = DEFAULT_EPSILON, 
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world)) {
					throw new IllegalParameterException();
				}

				if (maxEpisodes > MAX_EPISODES || epsilon < 0.0f) {
					throw new IllegalParameterException();
				}

				(*goal) = world->clone();
				size_t stateCount = (*goal)->getStateCount();

				Matrix *W = new Matrix(stateCount, ALLOWED_ACTIONS_QTY);

				double policy_for_nomax_action = epsilon / 4;
				double policy_for_max_action = 1 - epsilon + epsilon / 4;

				size_t counter = 0;
				do {

					// 1. Gera um episódio
					Episode *episode = NULL;
					if (!generateEpisode((*goal), &episode)) {
						continue;
					}

					if (debug) {
						Logger::log("\n");
						Logger::log("%s\n", STARS);
						episode->dump();
						Utils::pressAnyKeyToContinue();
					}

					std::vector<bool> foundInEpisode(stateCount);

					// 2. Para cada par estado-ação do episódio...
					size_t counter = 0;
					size_t episodeSize = episode->size();
					std::vector<StateActionPair*> *pairs = episode->getPairs();
					for (std::vector<StateActionPair*>::iterator iterator =  pairs->begin() ; 
						iterator != pairs->end(); 
						++iterator) {

						register size_t stateIdx = (*iterator)->getState();
						register size_t actionIdx = (*iterator)->getAction();
						register SmallGridWorldState *state = (*goal)->getState(stateIdx);
						register Matrix *Q = state->getQ();

						foundInEpisode.at(stateIdx) = true;
						
						Q->data()[0][actionIdx] = 
								(((counter == episodeSize - 1) ? 0 : DEFAULT_REWARD)) / 
								++W->data()[stateIdx][actionIdx];

						counter++;

					}
					
					delete episode;

					if (debug) {
						(*goal)->dump(false, true);
						Utils::pressAnyKeyToContinue();
					}

					// 3. Atualize a política para cada estado encontrado no episódio
					for (size_t stateIdx = 0; stateIdx < stateCount; stateIdx++) {

						if (!foundInEpisode.at(stateIdx)) {
							continue;
						}

						register SmallGridWorldState *state = (*goal)->getState(stateIdx);
						register Matrix *Q = state->getQ();
						register Matrix *P = state->getTransitionProbabilities();

						// a* <- argmax a Q (s, a)
						double max = DBL_MIN;
						size_t maxRowId = 0;
						size_t maxColIdx = 0;
						std::vector<size_t> indexes;
						// atualiza a política, P(s, a) <- 1 - e + e/4, if a = a*; e/4, if a != a* 
						if (Q->max(&max, &maxRowId, &maxColIdx)) {
							P->fill(policy_for_nomax_action);
							P->data()[0][maxColIdx] = policy_for_max_action;
							/* for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) { if (std::abs(max - Q->data()[0][idx]) < PRECISION) { indexes.push_back(idx); }  } */
						} 
						
						/* for (size_t idx = 0; idx < indexes.size(); idx++) {  P->data()[0][indexes.at(idx)] = policy_for_max_action;  }  */

					}

					if (debug) {
						(*goal)->dump(false, true);
						Logger::log("%s\n", STARS);
						Utils::pressAnyKeyToContinue();
					}

				} while (counter++ < maxEpisodes);
				
				return true;

			};

		}; /* class OnPolicyMonteCarlo */

	} /* namespace week7 */

} /* namespace pel208 */

#endif /* __ON_POLICY_MONTE_CARLO_H__ */
