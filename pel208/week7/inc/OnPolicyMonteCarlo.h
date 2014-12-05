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

namespace pel208 {

	namespace week7 {

		/**
		 * Classe que representa um estado do episódio.<br />
		 *
		 * @author arrebola
		 */
		class EpisodeState {
		private:
			size_t stateIdx;
			size_t actionIdx;
			EpisodeState *previous;
			EpisodeState *next;
			double R;

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param stateIdx
			 *				 o <code>size_t</code> que representa o estado
			 * @param actionIdx
			 *				 o <code>size_t</code> que representa a ação
			 * @param previous
			 *				 o EpisodeState que representa o estado anterior
			 * @param next
			 *				 o EpisodeState que representa o estado posterior
			 */
			EpisodeState(
					IN size_t stateIdx, 
					IN size_t actionIdx, 
					IN EpisodeState *previous = NULL, 
					IN EpisodeState *next = NULL) {
				this->stateIdx = stateIdx;
				this->actionIdx = actionIdx;
				this->previous = previous;
				this->next = next;
				this->R = 0;
			};
			
			/**
			 * Destrutor.<br />
			 */
			~EpisodeState() {
			};
			
			/**
			 * Determina se um objeto é igual à instância atual.<br />
			 *
			 * @param that
			 *				o EpisodeState que representa o objeto
			 *
			 * @return <code>true</code> caso o objeto seja igual; do contrário <code>false</code>
			 */
			PUBLIC bool equals(IN EpisodeState *that) {
				
				bool equals = false;
				if (Utils::isValidHandle(that)) {
					equals = ((this->getActionIdx() == that->getActionIdx()) && 
						(this->getStateIdx() == that->getStateIdx()));
				}

				return equals;
			
			};

			/**
			 * Retorna o estado.<br />
			 *
			 * @return o <code>size_t</code> que representa o estado
			 */
			PUBLIC size_t getStateIdx() {
				return this->stateIdx;
			};

			/**
			 * Retorna o ação.<br />
			 *
			 * @return o <code>size_t</code> que representa a ação
			 */
			PUBLIC size_t getActionIdx() {
				return this->actionIdx;
			};

			/**
			 * Retorna o estado anterior.<br />
			 *
			 * @return o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC EpisodeState *getPrevious() {
				return this->previous;
			};

			/**
			 * Retorna o estado anterior.<br />
			 *
			 * @param previous 
			 *				o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC void setPrevious(IN EpisodeState *previous) {
				this->previous = previous;
			};

			/**
			 * Retorna o próximo estado.<br />
			 *
			 * @return o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC EpisodeState *getNext() {
				return this->next;
			};

			/**
			 * Retorna o próximo estado.<br />
			 *
			 * @param next 
			 *				o <code>EpisodeState</code> que representa o estado
			 */
			PUBLIC void setNext(IN EpisodeState *next) {
				this->next = next;
			};

			/**
			 * Obtém valor de R.<br />
			 *
			 * @return o <code>double</code> que representa o R
			 */
			PUBLIC double getR() {
				return this->R;
			};

			/**
			 * Configura o valor de R.<br />
			 *
			 * @param R 
			 *				o <code>double</code> que representa o R
			 */
			PUBLIC void setR(IN double R) {
				this->R = R;
			};

		}; /* class EpisodeState */

		/**
		 * Classe que representa um episódio.<br />
		 *
		 * @author arrebola
		 */
		class Episode {
		private:
			std::vector<EpisodeState*> *visitedStates;

		public:
			/**
			 * Construtor.<br />
			 */
			Episode() {
				this->visitedStates = new std::vector<EpisodeState*>();
			};

			/**
			 * Destrutor.<br />
			 */
			~Episode() {
				delete this->visitedStates;
			};

			/**
			 * Adição um estado ao episódio.<br />
			 * 
			 * @param state
			 *				o EpisodeState que representa o estado do episódio
			 */
			PUBLIC void add(IN EpisodeState* state) {

				if (Utils::isInvalidHandle(state)) {
					throw new IllegalParameterException();
				}

				this->visitedStates->push_back(state);

			};

			/**
			 * Retorna o tamanho do episódio.<br />
			 *
			 * @return o <code>size_t</code> que representa o tamanho do episódio
			 */
			PUBLIC size_t size() {
				return this->visitedStates->size();
			};

			/**
			 * Retorna os estados do episódio.<br />
			 *
			 * @return o <code>std::vector</code> de EpisodeState que representa os estado do episódio
			 */
			PUBLIC std::vector<EpisodeState*> *getVisitedStates() {
				return this->visitedStates;
			};

			/**
			 * Imprime detalhes sobre o episódio.<br />
			 */
			PUBLIC void dumpToFile() {

				size_t size = this->visitedStates->size();

				Logger::logToFile("Episodio com %d estados...\n", size);

				size_t counter = 1;
				for (std::vector<EpisodeState*>::iterator iterator =  this->visitedStates->begin() ; 
						iterator != this->visitedStates->end(); 
						++iterator) {

					register size_t stateIdx = (*iterator)->getStateIdx();
					register size_t actionIdx = (*iterator)->getActionIdx();
					register double r = (*iterator)->getR();

					Logger::logToFile("  %05d: s=%02d a=%s Rt=%f\n", 
						counter++,
						stateIdx, 
						(actionIdx == 0 ? "U" : ((actionIdx == 1) ? "D" : ((actionIdx == 2) ? "L" : "R"))),
						 r);

				}

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

			/**
			 * Seleciona um estado aleatório diferente dos alvos seguindo uma distribuição uniforme.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 *
			 * @return <code>size_t</code> que representa o estado
			 */
			PRIVATE static size_t selectRandomState(IN SmallGridWorld *world) {

				if (Utils::isInvalidHandle(world) || world->getStateCount() < 1) {
					throw new IllegalParameterException();
				}

				// o estado 0 e o estado 15 são considerados estados terminais
				return Random::nextUint(1, 14);

			};

			/**
			 * Seleciona uma ação aleatória seguindo a distribuição determinada pela política de transição do estado.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param state
			 *				o SmallGridWorldState que representa o estado
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
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param episode
			 *				o Episode que representa o episódio
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 *
			 * @return <code>true</code> caso a geração tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool generateEpisode(
					IN SmallGridWorld *world, 
					IN OUT Episode **episode, 
					IN bool debug = false) {

				bool succeeded = false;

				(*episode) = new Episode();

				std::vector<EpisodeState*> *visited = (*episode)->getVisitedStates();

				size_t stateIdx = selectRandomState(world);
				
				bool ended = false;
				while (!ended && (*episode)->size() < MAX_EPISODE_LEN) {
					
					register SmallGridWorldState *state = world->getState(stateIdx);
					register size_t actionIdx = selectRandomAction(world, state);
					register EpisodeState *current = new EpisodeState(stateIdx, actionIdx);
					register EpisodeState *last = NULL;
					
					if (!visited->empty()) {
						last = visited->back();
					}

					if (current->equals(last)) {
						continue;
					}
					
					if (Utils::isValidHandle(last)) {
						last->setNext(current);
						current->setPrevious(last);
					}
					
					(*episode)->add(current);

					stateIdx = (size_t)state->getNextStates()->data()[0][actionIdx];
				
					ended = (stateIdx == 0 || stateIdx == 15);

				}

				succeeded = (*episode)->size() < MAX_EPISODE_LEN;
				
				if (succeeded) {
					int counter = visited->size();
					for (std::vector<EpisodeState*>::iterator iterator = visited->begin() ; 
							iterator != visited->end(); 
							++iterator) {
						(*iterator)->setR(DEFAULT_REWARD * --counter * 1.0f);
					}
					if (debug) {
						(*episode)->dumpToFile();
					}
				} else {
					delete (*episode);
					(*episode) = NULL;
				}

				return succeeded;

			};

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
			 * Avalia o problema do <i>small grid world</i> utilizando a técnica de monte carlo com controle de política.<br />
			 * O primeiro e o último estado do grid são considerados estados terminais.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param goal
			 *				o SmallGridWorld que representa o <i>small grid world</i> final
			 * @param R
			 *				o Matrix que representa a matrix de recompensas por episódio
			 * @param maxIterations
			 *				o <code>size_t</code> que representa a quantidade máxima de iterações
			 * @param maxEpisodes
			 *				o <code>size_t</code> que representa a quantidade máxima de episódios
			 * @param epsilon
			 *				o <code>double</code> que representa o epsilon para a geração de políticas
			 * @param uniqueQ
			 *				indica se um único Q deve ser considerado de depuração devem ser exibidas
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 *
			 * @return <code>true</code> caso a avaliação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC static bool evaluate(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **goal,
					IN OUT Matrix **R,
					IN size_t maxEpisodes = MAX_EPISODES,
					IN double epsilon = DEFAULT_EPSILON, 
					IN bool uniqueQ = false,
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world)) {
					throw new IllegalParameterException();
				}

				if (maxEpisodes > MAX_EPISODES || epsilon < 0.0f) {
					throw new IllegalParameterException();
				}

				(*goal) = world->clone();
				size_t stateCount = (*goal)->getStateCount();

				(*R) = new Matrix(maxEpisodes, 1);

				Matrix *W = new Matrix(stateCount, ALLOWED_ACTIONS_QTY);

				double policy_for_nomax_action = epsilon / 4;
				double policy_for_max_action = 1 - epsilon + epsilon / 4;

				size_t episodes = 0;
				do {

					if (debug) {
						Logger::logToFile("\n");
						Logger::logToFile("%s\n", STARS);
					}

					// 1. Gera um episódio
					Episode *episode = NULL;
					if (!generateEpisode((*goal), &episode, debug)) {
						continue;
					}

					std::vector<bool> foundInEpisode(stateCount);

					// 2. Para cada estado visitado no episódio...
					size_t episodeSize = episode->size();
					std::vector<EpisodeState*> *episodeStates = episode->getVisitedStates();
					for (std::vector<EpisodeState*>::iterator iterator = episodeStates->begin(); 
						iterator != episodeStates->end(); 
						++iterator) {

						register size_t stateIdx = (*iterator)->getStateIdx();
						register size_t actionIdx = (*iterator)->getActionIdx();
						register double R = (*iterator)->getR();
						register SmallGridWorldState *state = (*goal)->getState(stateIdx);
						register Matrix *Q = state->getQ();

						foundInEpisode.at(stateIdx) = true;
						
						Q->data()[0][actionIdx] = 
							Q->data()[0][actionIdx] + 
							((R - Q->data()[0][actionIdx]) / ++W->data()[stateIdx][actionIdx]);

					}
					
					(*R)->data()[episodes][0] = ((double)episodeSize) * DEFAULT_REWARD;

					delete episode;

					// 3. Atualize a política para cada estado encontrado no episódio
					for (size_t stateIdx = 0; stateIdx < stateCount; stateIdx++) {

						if (!foundInEpisode.at(stateIdx)) {
							continue;
						}

						register SmallGridWorldState *state = (*goal)->getState(stateIdx);
						register Matrix *Q = state->getQ();
						register Matrix *P = state->getTransitionProbabilities();

						double max = DBL_MIN;
						size_t maxRowId = 0;
						size_t maxColIdx = 0;
						if (!Q->max(&max, &maxRowId, &maxColIdx)) {
							return false;
						}

						P->fill(policy_for_nomax_action);
						
						if (uniqueQ) {
							std::vector<size_t> argMax;
							for (size_t idx = 0; idx < ALLOWED_ACTIONS_QTY; idx++) { 
								if (std::abs(max - Q->data()[0][idx]) < PRECISION) { 
									argMax.push_back(idx); 
								}  
							}
							register size_t argMaxCount = argMax.size();
							register double new_policy_for_max_action = policy_for_max_action / (argMaxCount * 1.0f);
							for (size_t idx = 0; idx < argMaxCount; idx++) {  
								P->data()[0][argMax.at(idx)] = new_policy_for_max_action;  
							} 
						} else { 
							P->data()[0][maxColIdx] = policy_for_max_action;
						}

					}

					if (debug) {
						(*goal)->dumpToFile();
						Logger::logToFile("%s\n", STARS);
						Logger::logToFile("\n");
					}

				} while (++episodes < maxEpisodes);

				delete W;

				return true;

			};

		}; /* class OnPolicyMonteCarlo */

	} /* namespace week7 */

} /* namespace pel208 */

#endif /* __ON_POLICY_MONTE_CARLO_H__ */
