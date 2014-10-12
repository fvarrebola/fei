#pragma once

#ifndef __TESTSUITE_WEEK2_H__
#define __TESTSUITE_WEEK2_H__

namespace pel208 {

	namespace week2 {

		/**
		 * Classe de testes.<br />
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:
			static void testMatrixClassUsing1stDataSet();
			static void testMatrixClassUsing2ndDataSet();
			static void testPCAMethodClassUsing1stDataSet();
			static void testPCAMethodClassUsing2ndDataSet();

		public:
			/**
			 * Executa todos os testes.<br />
			 */
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week2 */

} /* namespace pel216 */

#endif /* __TESTSUITE_WEEK2_H__ */
