#pragma once

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <inc/Logger.h>
#include <inc/Utils.h>
#include <inc/Element.h>
#include <inc/Collection.h>
#include <inc/Stack.h>
#include <inc/Queue.h>

namespace pel216 {

	namespace week1 {

		class TestSuite {

		private:
			static char *createRandomData(unsigned long cbData);
			static Element *createRandomElement(char *pbData, unsigned long cbData);

			static void testUtilsClass();
			static void testLoggerClass();
			static void testElementClass();
			static void testStackClass();
			static void testQueueClass();

		public:
			static void run(); 

		}; // class TestSuite

	} // namespace week1

} // namespace pel216


#endif
