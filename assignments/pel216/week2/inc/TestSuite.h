#pragma once

#ifndef __TESTSUITE_H__
#define __TESTSUITE_H__

#include <assert.h>

namespace pel216 {

	namespace week2 {

		/**
		 * Classe de testes.
		 *
		 * @author arrebola
		 */
		class TestSuite {

		private:

			static void testShapeClass();

			// figuras elementares
			static void testPointClass();
			static void testLineClass();
			static void testLineSegmentClass();

			// figuras bidimensionais
			static void testCircleClass();
			static void testPolygons();

			// figuras tridimensionais
			static void testPolyhedrals();
			static void testCylinderClass();
			static void testConeClass();
			static void testPyramidClass();
			static void testSphereClass();

		public:
			static void run(); 

		}; /* class TestSuite */

	} /* namespace week2 */

} /* namespace pel216 */

#endif
