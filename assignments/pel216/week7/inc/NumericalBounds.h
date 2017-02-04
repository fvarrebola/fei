#pragma once

#ifndef __NUMERICAL_BOUNDS_H__
#define __NUMERICAL_BOUNDS_H__

namespace pel216 {

	namespace week7 {

		/**
		 * Classe que representa um limite numérico.<br />
		 *
		 * @author arrebola
		 */
		class NumericalBounds {

		private:
			double _lowerX;
			double _upperX;
			double _lowerY;
			double _upperY;
			double _lowerZ;
			double _upperZ;

		public:
			/**
			 * Construtor padrão.<br />
			 *
			 * @param lowerX
			 *				o <code>double</code> que representa o limite inferior em X
			 * @param upperX
			 *				o <code>double</code> que representa o limite superior em X
			 * @param lowerY
			 *				o <code>double</code> que representa o limite inferior em Y
			 * @param upperY
			 *				o <code>double</code> que representa o limite superior em Y
			 * @param lowerZ
			 *				o <code>double</code> que representa o limite inferior em Z
			 * @param upperZ
			 *				o <code>double</code> que representa o limite superior em Z
			 */
			NumericalBounds(double lowerX = 0.0f, double upperX = 0.0f, double lowerY = 0.0f, double upperY = 0.0f, double lowerZ = 0.0f, double upperZ = 0.0f) {
				this->_lowerX = lowerX;
				this->_upperX = upperX;
				this->_lowerY = lowerY;
				this->_upperY = upperY;
				this->_lowerZ = lowerZ;
				this->_upperZ = upperZ;
			};

			/**
			 * Obtém o limite inferior em X.
			 *
			 * @return o <code>double</code> que representa o limite inferior em X
			 */
			double lowerX() {
				return this->_lowerX;
			};

			/**
			 * Obtém o limite superior em X.
			 *
			 * @return o <code>double</code> que representa o limite superior em X
			 */
			double upperX() {
				return this->_upperX;
			};

			/**
			 * Obtém o limite inferior em Y.
			 *
			 * @return o <code>double</code> que representa o limite inferior em Y
			 */
			double lowerY() {
				return this->_lowerY;
			};

			/**
			 * Obtém o limite superior em Y.
			 *
			 * @return o <code>double</code> que representa o limite superior em Y
			 */
			double upperY() {
				return this->_upperY;
			};

			/**
			 * Obtém o limite inferior em Z.
			 *
			 * @return o <code>double</code> que representa o limite inferior em Z
			 */
			double lowerZ() {
				return this->_lowerZ;
			};

			/**
			 * Obtém o limite superior em Z.
			 *
			 * @return o <code>double</code> que representa o limite superior em Z
			 */
			double upperZ() {
				return this->_upperZ;
			};

		}; /* class NumericalBounds */

	} /* namespace week7 */

} /* namespace pel216 */

#endif /* __NUMERICAL_BOUNDS_H__ */
