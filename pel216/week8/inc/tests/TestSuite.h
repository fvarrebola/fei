#pragma once

#ifndef __TESTSUITE_WEEK8_H__
#define __TESTSUITE_WEEK8_H__

#include <assert.h>

namespace pel216 {

	namespace week8 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testNearestNeighborClass();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuiteWeek8 */

	} /* namespace week8 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK8_H__ */
