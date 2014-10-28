#pragma once

#ifndef __IRIS_DATA_H__
#define __IRIS_DATA_H__

#include <string>
#include <sstream>

namespace pel208 {

	namespace week3 {

		/**
		 * Representação do dado.<br />
		 *
		 * @author arrebola
		 */
		class IrisData {

		private:
			size_t type;
			double pw;
			double pl;
			double sw;
			double sl;

		public:
			/**
			 * Construtor.<br />
			 *
			 * @param type
			 *				o <code>size_t</code> que representa o x1
			 * @param pw
			 *				o <code>double</code> que representa o x2
			 * @param pl
			 *				o <code>double</code> que representa o x3
			 * @param sw
			 *				o <code>double</code> que representa o x4
			 * @param sl
			 *				o <code>double</code> que representa o y
			 */
			IrisData(size_t type = 0, double pw = 0, double pl = 0, double sw = 0, double sl = 0) {
				this->type = type;
				this->pw = pw;
				this->pl = pl;
				this->sw = sw;
				this->sl = sl;
			};

			/**
			 * Retorna o type.<br />
			 * 
			 * @return o <code>double</code> que representa o type
			 */
			double getType() {
				return this->type;
			};
			
			/**
			 * Retorna o pw.<br />
			 * 
			 * @return o <code>double</code> que representa o pw
			 */
			double getPW() {
				return this->pw;
			};

			/**
			 * Retorna o pl.<br />
			 * 
			 * @return o <code>double</code> que representa o pl
			 */
			double getPL() {
				return this->pl;
			};

			/**
			 * Retorna o sw.<br />
			 * 
			 * @return o <code>double</code> que representa o sw
			 */
			double getSW() {
				return this->sw;
			};

			/**
			 * Retorna o sl.<br />
			 * 
			 * @return o <code>double</code> que representa o sl
			 */
			double getSL() {
				return this->sl;
			};

			/**
			 * Retorna uma representação do dado.<br />
			 *
			 * @return o <code>std::string</code> que representa o dado
			 */
			std::string toString() {

				char pszMsg[25] = {0x00};
				sprintf_s(pszMsg, 25, "(%3f, %3f, %3f, %3f, %3f)", this->type, this->pw, this->pl, this->sw, this->sl);
				return std::string(pszMsg);

			};

		}; /* class IrisData */

	} /* namespace week3 */

} /* namespace pel208 */

#endif /* __IRIS_DATA_H__ */
