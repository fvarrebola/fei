#pragma once

#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <inc/Utils.h>
#include <inc/ex/IllegalParameterException.h>

namespace pel216 {

	namespace week3 {

		/**
		 * Classe que representa um solucionador de problemas.
		 *
		 * @author arrebola
		 */
		class Solver {

		private:

		public:
			/**
			 * Construtor padrão.
			 */
			Solver() {
			};

			/**
			 * Destrutor.
			 */
			virtual ~Solver() {
			};

			/**
			 * Soluciona o problema.
			 */
			virtual void solve() const = 0;

		}; /* class Solver */

	} /* namespace week3 */

} /* namespace pel216 */

#endif /* __SOLVER_H__ */
