#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <iostream>

#include <inc/Utils.h>

namespace pel216 {

	namespace commons {

		#define SIMPLE_FORMAT			"[%02i:%02i:%02i] %s"
		#define COMPLETE_FORMAT			"[%02i:%02i:%02i] (%s:%i) %s"

		/**
		 * Representa o mecanismo de impressao de mensagens no console.
		 *
		 * @author arrebola
		 */
		class Logger {

		public:

			/**
			 * Registra uma mensagem no console.
			 *
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			static void log(IN const char *pszFormat, ...) {

				if (pszFormat == NULL) {
					return;
				}

				const int iVarArgMsgLen = MAX_PATH * 4;
				char pszVarArgMsg[iVarArgMsgLen] = {0x00};

				const int iLogMsgLen = MAX_PATH * 5;
				char pszLogMsg[iLogMsgLen] = {0x00};

				va_list varArgs;
				va_start(varArgs, pszFormat);

				if (vsprintf_s(pszVarArgMsg, iVarArgMsgLen, pszFormat, varArgs) < 0) {
					va_end(varArgs);
					return;
				}

				time_t timer = {0x00};
				time(&timer);

				struct tm tm = {0x00};
				localtime_s(&tm, &timer);

				if (sprintf_s(pszLogMsg, iLogMsgLen, SIMPLE_FORMAT, tm.tm_hour, tm.tm_min, tm.tm_sec, pszVarArgMsg) > 0) {
					std::cout << pszLogMsg;
				}

				ZERO_MEM(pszVarArgMsg, iVarArgMsgLen);
				ZERO_MEM(pszLogMsg, iLogMsgLen);

				va_end(varArgs);

			}

		}; // class Logger

	} // namespace commons

} // namespace pel216

#endif
