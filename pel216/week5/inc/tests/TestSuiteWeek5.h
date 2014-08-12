#pragma once

#ifndef __TESTSUITE_WEEK5_H__
#define __TESTSUITE_WEEK5_H__

#include <assert.h>

namespace pel216 {

	namespace week5 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testFirstFunctionClass();
			static void testSecondFunctionClass();
			static void testThirdFunctionClass();

		public:
			/**
			 * Executa todos os testes.
			 */
			static void run(); 

		}; /* class TestSuiteWeek5 */

	} /* namespace week5 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK5_H__ */
