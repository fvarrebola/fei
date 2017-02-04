#pragma once

#ifndef __TESTSUITE_WEEK3_H__
#define __TESTSUITE_WEEK3_H__

namespace pel208 {

	namespace week3 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testLDAMethodClassUsingSimpleDataSet();
			static void testLDAMethodClassUsingIrisDataSet();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK2_H__ */
