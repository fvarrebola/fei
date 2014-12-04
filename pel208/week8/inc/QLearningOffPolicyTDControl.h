#pragma once

#ifndef __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__
#define __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__

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

	namespace week8 {

		/**
		 * Implementa��o do m�todo Q-Learning Off Policy TD Control.<br />
		 *
		 * @author arrebola
		 */
		class QLearningOffPolicyTDControl {

		private:

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
			 * Avalia o problema do <i>small grid world</i> utilizando a t�cnica de Q learning.<br />
			 * O primeiro e o �ltimo estado do grid s�o considerados estados terminais.<br />
			 *
			 * @param world
			 *					o SmallGridWorld que representa o <i>small grid world</i>
			 * @param goal
			 *					o SmallGridWorld que representa o <i>small grid world</i> final
			 * @param maxIterations
			 *					o <code>size_t</code> que representa a quantidade m�xima de itera��es
			 * @param maxEpisodes
			 *					o <code>size_t</code> que representa a quantidade m�xima de epis�dios
			 * @param debug
			 *					indica se as mensagens de depura��o devem ser exibidas
			 *
			 * @return <code>true</code> caso a avalia��o tenha sido bem sucedida; do contr�rio <code>false</code>
			 */
			PUBLIC static bool evaluate(
					IN SmallGridWorld *world, 
					IN OUT SmallGridWorld **goal,
					IN size_t maxEpisodes = MAX_EPISODES,
					IN bool debug = false) {

				if (Utils::isInvalidHandle(world)) {
					throw new IllegalParameterException();
				}

				if (maxEpisodes > MAX_EPISODES) {
					throw new IllegalParameterException();
				}

				(*goal) = world->clone();
				size_t stateCount = (*goal)->getStateCount();

				return true;

			};

		}; /* class QLearningOffPolicyTDControl */

	} /* namespace week8 */

} /* namespace pel208 */

#endif /* __Q_LEARNING_OFF_POLICY_TD_CONTROL_H__ */
