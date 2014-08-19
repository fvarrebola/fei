#pragma once

#ifndef __TESTSUITE_WEEK6_H__
#define __TESTSUITE_WEEK6_H__

#include <assert.h>

namespace pel216 {

	namespace week6 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testRectangleRuleClass();
			static void testTrapezoidalRuleClass();
			static void testSimpsonRuleClass();

		public:
			/**
			 * Executa todos os testes.
			 */
			static void run(); 

		}; /* class TestSuiteWeek6 */

	} /* namespace week6 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK6_H__ */
