#pragma once

#ifndef __TESTSUITE_WEEK7_H__
#define __TESTSUITE_WEEK7_H__

#include <assert.h>

namespace pel216 {

	namespace week7 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testMonteCarloRuleClass();
			static void testToroidVolumeCalculatorClass();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuiteWeek7 */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK7_H__ */
