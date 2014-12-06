#pragma once

#ifndef __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__
#define __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__

#include <inc\Utils.h>

#include <inc\Matrix.h>
#include <inc\Random.h>

#include <inc\SmallGridWorld.h>
#include <inc\SmallGridWorldState.h>

#include <inc\OnPolicyMonteCarlo.h>

#define MAX_EPISODES					UINT_MAX - 1
#define MAX_EPISODE_LEN					256
#define MAX_ALPHA						1.0f
#define DEFAULT_ALPHA					0.5f
#define MAX_GAMMA						1.0f
#define DEFAULT_GAMMA					1.0f

using namespace pel208::commons;
using namespace pel208::week6;
using namespace pel208::week7;

namespace pel208 {

	namespace week8 {

		/**
		 * Implementação do método Q-Learning Off Policy TD Control.<br />
		 *
		 * @author arrebola
		 */
		class QLearningOffPolicyTDControl {

		private:
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
			 * Obtém o valor máximo de Q(s, a) de um estado.<br />
			 *
			 * @param state
			 *				o SmallGridWorldState que representa o estado
			 *
			 * @return <code>true</code> caso a operação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool getMaxFutureValue(IN SmallGridWorldState *state, OUT double *max) {

				if (Utils::isInvalidHandle(state)) {
					throw new IllegalParameterException();
				}

				return state->getQ()->max(&(*max));

			};

			/**
			 * Gera um episódio.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param episode
			 *				o Episode que representa o episódio
			 * @param alpha
			 *				o <code>double</code> que representa o alpha (taxa de aprendizado)
			 * @param gamma
			 *				o <code>double</code> que representa o gamma (desconto)
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 *
			 * @return <code>true</code> caso a geração tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool generateEpisode(
					IN SmallGridWorld *world, 
					IN OUT Episode **episode, 
					IN double alpha = DEFAULT_ALPHA,
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				bool succeeded = false;

				(*episode) = new Episode();

				std::vector<EpisodeState*> *visited = (*episode)->getVisitedStates();

				// escolhe um estado aleatório
				size_t stateIdx = selectRandomState(world);
				
				bool ended = false;
				while (!ended && (*episode)->size() < MAX_EPISODE_LEN) {
					
					register SmallGridWorldState *state = world->getState(stateIdx);
					register Matrix *Q = state->getQ();
					
					// escolhe uma ação aleatória de acordo com a política vigente
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
					
					// observa o próximo estado para determinar o valor máximo
					register size_t nextStateIdx = (size_t)state->getNextStates()->data()[0][actionIdx];
					register double max = 0;
					if (!getMaxFutureValue(world->getState(nextStateIdx), &max)) {
						continue;
					}

					// Q(s, a) = Q(s, a) + alpha * (r + (gamma * max(a) Q(s', a)) - Q(s, a))
					register double currentValue = Q->data()[0][actionIdx];
					Q->data()[0][actionIdx] = currentValue + alpha * 
						(pel208::week6::SmallGridWorld::DEFAULT_REWARD + (gamma * max) - currentValue);

					(*episode)->add(current);

					ended = (nextStateIdx == 0 || nextStateIdx == 15);
					stateIdx = nextStateIdx;

				}

				succeeded = (*episode)->size() < MAX_EPISODE_LEN;

				// atualiza as recompensas...
				if (succeeded) {
					int counter = visited->size();
					for (std::vector<EpisodeState*>::iterator iterator = visited->begin() ; 
							iterator != visited->end(); 
							++iterator) {
						(*iterator)->setR(pel208::week6::SmallGridWorld::DEFAULT_REWARD * --counter * 1.0f);
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
			QLearningOffPolicyTDControl() {
			};

			/**
			 * Destrutor.<br />
			 */
			~QLearningOffPolicyTDControl() {
			};

			/**
			 * Avalia o problema do <i>small grid world</i> utilizando a técnica de Q learning.<br />
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
			 * @param alpha
			 *				o <code>double</code> que representa o alpha (taxa de aprendizado)
			 * @param gamma
			 *				o <code>double</code> que representa o gamma (desconto)
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
					IN double alpha = DEFAULT_ALPHA,
					IN double gamma = DEFAULT_GAMMA,
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world)) {
					throw new IllegalParameterException();
				}

				if (maxEpisodes > MAX_EPISODES || alpha > MAX_ALPHA || gamma > MAX_GAMMA) {
					throw new IllegalParameterException();
				}

				(*goal) = world->clone();
				size_t stateCount = (*goal)->getStateCount();

				(*R) = new Matrix(maxEpisodes, 1);

				size_t episodes = 0;
				do {

					if (debug) {
						Logger::logToFile("\n");
						Logger::logToFile("%s\n", STARS);
					}

					Episode *episode = NULL;
					if (generateEpisode((*goal), &episode, alpha, gamma, debug)) {

						if (debug) {
							(*goal)->dumpToFile();
							Logger::logToFile("%s\n", STARS);
							Logger::logToFile("\n");
						}

						(*R)->data()[episodes][0] = ((double)episode->size()) * pel208::week6::SmallGridWorld::DEFAULT_REWARD;

						delete episode;

					}

				} while (++episodes < maxEpisodes);

				return true;

			};

		}; /* class QLearningOffPolicyTDControl */

	} /* namespace week8 */

} /* namespace pel208 */

#endif /* __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__ */
