#pragma once

#ifndef __TESTSUITE_WEEK1_H__
#define __TESTSUITE_WEEK1_H__

#include <assert.h>

namespace pel208 {

	namespace week1 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testMatrixClass();
			static void testLeastSquaresMethodClass();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week1 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK1_H__ */
