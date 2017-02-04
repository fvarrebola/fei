#pragma once

#ifndef __TESTSUITE_WEEK4_H__
#define __TESTSUITE_WEEK4_H__

namespace pel208 {

	namespace week4 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testNaiveBayesMethodClassUsingPlayTennisDS();
			static void testNaiveBayesMethodClassUsingFirstDS();
			static void testNaiveBayesMethodClassUsingSecondDS();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week4 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK4_H__ */
