#pragma once

#ifndef __ON_POLICY_MONTE_CARLO_H__
#define __ON_POLICY_MONTE_CARLO_H__

#include <inc\Utils.h>
#include <inc\Matrix.h>

#include <inc\SmallGridWorld.h>
#include <inc\SmallGridWorldState.h>
#include <inc\Episode.h>
#include <inc\EpisodeState.h>

using namespace pel208::commons;
using namespace pel208::week6;

namespace pel208 {

	namespace week7 {

		/**
		 * Implementação do método On Policy Monte Carlo.<br />
		 *
		 * @author arrebola
		 */
		class OnPolicyMonteCarlo {

		private:
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

				// escolhe um estado aleatório
				size_t stateIdx = world->selectRandomState();
				
				bool ended = false;
				while (!ended && (*episode)->size() < MAX_EPISODE_LEN) {
					
					register SmallGridWorldState *state = world->getState(stateIdx);

					// escolhe uma ação aleatória de acordo com a política vigente
					register size_t actionIdx = world->selectRandomActionUsingP(state);
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
				
					ended = world->isTerminalState(stateIdx);

				}

				succeeded = (*episode)->size() < MAX_EPISODE_LEN;
				
				// atualiza as recompensas...
				if (succeeded) {
					int counter = visited->size();
					for (std::vector<EpisodeState*>::iterator iterator = visited->begin() ; 
							iterator != visited->end(); 
							++iterator) {
						(*iterator)->setR(DEFAULT_ACTION_REWARD * --counter * 1.0f);
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

				if (maxEpisodes > MAX_EPISODES || (epsilon < 0.0f || epsilon > MAX_EPSILON)) {
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
					
					(*R)->data()[episodes][0] = ((double)episodeSize) * DEFAULT_ACTION_REWARD;

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
						size_t maxRowIdx = 0;
						size_t maxColIdx = 0;
						if (!Q->max(&max, &maxRowIdx, &maxColIdx)) {
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
