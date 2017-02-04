#pragma once

#ifndef __Q_LAMBDA__
#define __Q_LAMBDA__

#include <inc\Utils.h>
#include <inc\Matrix.h>
#include <inc\Random.h>

#include <inc\SmallGridWorld.h>
#include <inc\SmallGridWorldState.h>
#include <inc\Episode.h>
#include <inc\EpisodeState.h>

#include <inc\RLConstants.h>

using namespace pel208::commons;
using namespace pel208::week6;
using namespace pel208::week7;

namespace pel208 {

	namespace week9 {

		/**
		 * Implementação do método Q-Lambda.<br />
		 *
		 * @author arrebola
		 */
		class QLambda {

		private:
			/**
			 * Obtém a ação ótima com base nos valores de Q.<br />
			 *
			 * @param Q
			 *				o Matrix que representa o Q
			 *
			 * @return o <code>size_t</code> que representa a ação ótima
			 */
			PRIVATE static size_t getAStar(IN Matrix *Q) {

				if (Utils::isInvalidHandle(Q)) {
					throw new IllegalParameterException();
				}

				size_t a_star = 0;

				double max = 0;
				size_t maxRowIdx = 0;
				
				Q->max(&max, &maxRowIdx, &a_star);

				return a_star;

			};

			/**
			 * Atualiza os traços de elegibilidade.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param visited
			 *				o <code>std::vector</code> de EpisodeState que indica os estados visitados
			 * @param a_prime_equals_a_star
			 *				indica se a' é igual ao a*
			 * @param alpha
			 *				o <code>double</code> que representa o alpha (taxa de aprendizado)
			 * @param gamma
			 *				o <code>double</code> que representa o gamma (desconto)
			 * @param zeroTraces
			 *				indica os traços devem ser zerados
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 * @param trace
			 *				indica se mensagens mais detalhadas devem ser exibidas
			 */
			PRIVATE static void updateElegibilityTraces(
					IN SmallGridWorld *world,
					std::vector<EpisodeState*> *visited, 
					IN bool a_prime_equals_a_star,
					IN double delta,
					IN double alpha = DEFAULT_ALPHA,
					IN double gamma = DEFAULT_GAMMA,
					IN double lambda = DEFAULT_LAMDA,
					IN bool zeroTraces = true,
					IN bool debug = false,
					IN bool trace = false) {

				// for all s, a
				for (size_t s_idx = 1; s_idx < world->getStateCount() - 1; s_idx++) {
				// for (std::vector<EpisodeState*>::iterator it = visited->begin(); it != visited->end(); ++it) {
					
					// register SmallGridWorldState *s = world->getState((*it)->getStateIdx());
					// register size_t a = (*it)->getActionIdx();

					register SmallGridWorldState *s = world->getState(s_idx);
					register Matrix *Q = s->getQ();
					register Matrix *E = s->getE(); 

					if (trace) {
						Q->dumpToFile();
						E->dumpToFile();
					}

					// Q(s, a) = Q(s, a) + alpha * delta * e(s, a)
					// if (a_prime == a_star)
					//     e(s, a) = gamma * lambda * e(s, a) 
					// else
					//     e(s, a) = 0
					for (size_t a = 0; a < ALLOWED_ACTIONS_QTY; a++) {
						Q->data()[0][a] += alpha * delta * E->data()[0][a];
						if (a_prime_equals_a_star) { 
							E->data()[0][a] = gamma * lambda * E->data()[0][a]; 
						} else if (zeroTraces) { 
							E->data()[0][a] = 0;
						}
					}

					if (trace) {
						Q->dumpToFile();
						E->dumpToFile();
					}

				}

			};

			/**
			 * Gera um episódio.<br />
			 *
			 * @param world
			 *				o SmallGridWorld que representa o <i>small grid world</i>
			 * @param episode
			 *				o Episode que representa o episódio
			 * @param epsilon
			 *				o <code>double</code> que representa o epsilon para a geração de políticas
			 * @param alpha
			 *				o <code>double</code> que representa o alpha (taxa de aprendizado)
			 * @param gamma
			 *				o <code>double</code> que representa o gamma (desconto)
			 * @param lambda
			 *				o <code>double</code> que representa o lambda
			 * @param zeroTraces
			 *				indica os traços devem ser zerados
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 * @param trace
			 *				indica se mensagens mais detalhadas devem ser exibidas
			 *
			 * @return <code>true</code> caso a geração tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PRIVATE static bool generateEpisode(
					IN SmallGridWorld *world, 
					IN OUT Episode **episode, 
					IN double epsilon = DEFAULT_EPSILON,
					IN double alpha = DEFAULT_ALPHA,
					IN double gamma = DEFAULT_GAMMA,
					IN double lambda = DEFAULT_LAMDA,
					IN bool zeroTraces = true,
					IN bool debug = false,
					IN bool trace = false) {

				bool succeeded = false;

				(*episode) = new Episode();

				std::vector<EpisodeState*> *visited = (*episode)->getVisitedStates();

				// escolhe um estado aleatório
				size_t s_idx = world->selectRandomState();
				SmallGridWorldState *s = world->getState(s_idx);
				size_t a = world->selectRandomActionUsingP(s);
				
				bool ended = false;
				while (!ended && (*episode)->size() < MAX_EPISODE_LEN) {

					register EpisodeState *current = new EpisodeState(s_idx, a);
					register EpisodeState *last = NULL;
					
					if (!visited->empty()) {
						last = visited->back();
					}

					if (Utils::isValidHandle(last)) {
						last->setNext(current);
						current->setPrevious(last);
					}

					// take action a, observe r and s'
					register double r = s->getTransitionRewards()->data()[0][a];
					register size_t s_prime_idx = (size_t)s->getNextStates()->data()[0][a];
					SmallGridWorldState *s_prime = world->getState(s_prime_idx);

					// choose a' from s' using policy derived from Q
					size_t a_prime = world->selectRandomActionUsingQ(s_prime, epsilon);
					// size_t a_prime = world->selectRandomActionUsingP(s_prime);

					// a* = argmax b Q(s', b) if (a' ties for the max, then a* = a')
					register Matrix *Q_prime = s_prime->getQ();
					register size_t a_star = getAStar(Q_prime);

					// delta = r + gamma * Q(s', a') - Q(s, a)
					register Matrix *Q = s->getQ();
					register double delta = r + (gamma * Q_prime->data()[0][a_prime]) - Q->data()[0][a];

					// e(s, a) = e(s, a) + 1
					s->getE()->data()[0][a] += ONE;

					if (debug) {
						Logger::logToFile("s=%d: a=%d, r=%f, s'=%d, a'=%d, a*=%d, d=%f (r + (g * Q(s', a*)=%f) - Q(s, a)=%f)\n", 
							s_idx, a, r, s_prime_idx, a_prime, a_star, delta, Q_prime->data()[0][a_star], Q->data()[0][a]);
					}

					// for all s, a:
					updateElegibilityTraces(world, visited, (a_prime == a_star), delta, alpha, gamma, lambda, zeroTraces, debug);

					(*episode)->add(current);

					// s = s_prime
					s = s_prime;

					// a = a_prime
					a = a_prime;

					ended = world->isTerminalState(s_idx);
					
					s_idx = s_prime_idx;

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
			QLambda() {
			};

			/**
			 * Destrutor.<br />
			 */
			~QLambda() {
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
			 * @param maxEpisodes
			 *				o <code>size_t</code> que representa a quantidade máxima de iterações
			 * @param epsilon
			 *				o <code>double</code> que representa o epsilon para a geração de políticas
			 * @param alpha
			 *				o <code>double</code> que representa o alpha (taxa de aprendizado)
			 * @param gamma
			 *				o <code>double</code> que representa o gamma (desconto)
			 * @param lambda
			 *				o <code>double</code> que representa o lambda
			 * @param zeroTraces
			 *				indica os traços devem ser zerados
			 * @param debug
			 *				indica se as mensagens de depuração devem ser exibidas
			 * @param trace
			 *				indica se mensagens mais detalhadas devem ser exibidas
			 *
			 * @return <code>true</code> caso a avaliação tenha sido bem sucedida; do contrário <code>false</code>
			 */
			PUBLIC static bool evaluate(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **goal,
					IN OUT Matrix **R,
					IN size_t maxEpisodes = MAX_EPISODES,
					IN double epsilon = DEFAULT_EPSILON,
					IN double alpha = DEFAULT_ALPHA,
					IN double gamma = DEFAULT_GAMMA,
					IN double lambda = DEFAULT_LAMDA,
					IN bool zeroTraces = false,
					IN bool debug = false,
					IN bool trace = false) {

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
					if (generateEpisode((*goal), &episode, epsilon, alpha, gamma, lambda, zeroTraces, debug, trace)) {

						if (debug) {
							(*goal)->dumpToFile();
							Logger::logToFile("%s\n", STARS);
							Logger::logToFile("\n");
						}

						(*R)->data()[episodes][0] = ((double)episode->size()) * DEFAULT_ACTION_REWARD;

						delete episode;

					}

				} while (++episodes < maxEpisodes);

				return true;

			};

		}; /* class QLambda */

	} /* namespace week9 */

} /* namespace pel208 */

#endif /* __Q_LAMBDA__ */
