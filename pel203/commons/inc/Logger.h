#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <iostream>
#include <fstream>

#include <inc/Utils.h>

namespace pel203 {

	namespace commons {

		#define OUTPUT_FILE				"log.txt"
		#define SIMPLE_FORMAT			"%s"
		#define SIMPLE_FORMAT_WITH_TIME	"[%02i:%02i:%02i] %s"
		#define COMPLETE_FORMAT			"[%02i:%02i:%02i] (%s:%i) %s"

		/**
		 * Representa o mecanismo de impressao de mensagens no console.
		 *
		 * @author arrebola
		 */
		class Logger {
		private:
			/**
			 * Registra uma mensagem.
			 *
			 * @param useConsole
			 *				o <code>bool</code> que indica se a mensagem deve ser registrada no console
			 * @param useFile
			 *				o <code>bool</code> que indica se a mensagem deve ser registrada em arquivo
			 * @param useTimeStamp
			 *				o <code>bool</code> que indica se a mensagem deve ser incluir <i>timestamp</i>
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			PRIVATE static void _log(IN bool useConsole, IN bool useFile, IN bool useTimeStamp, IN const char *pszFormat, IN va_list varArgs) {

				if (pszFormat == NULL) {
					return;
				}

				const int iVarArgMsgLen = MAX_PATH * 4;
				char pszVarArgMsg[iVarArgMsgLen] = {0x00};

				const int iLogMsgLen = MAX_PATH * 5;
				char pszLogMsg[iLogMsgLen] = {0x00};

				if (vsprintf_s(pszVarArgMsg, iVarArgMsgLen, pszFormat, varArgs) < 0) {
					return;
				}

				time_t timer = {0x00};
				time(&timer);

				struct tm tm = {0x00};
				localtime_s(&tm, &timer);

				bool gotMessage = false;
				if (useTimeStamp) {
					gotMessage = (sprintf_s(pszLogMsg, iLogMsgLen, 
						SIMPLE_FORMAT_WITH_TIME, tm.tm_hour, tm.tm_min, tm.tm_sec, pszVarArgMsg) > 0);
				} else {
					gotMessage = (sprintf_s(pszLogMsg, iLogMsgLen, SIMPLE_FORMAT, pszVarArgMsg) > 0);
				}

				if (gotMessage) {
					
					if (useConsole) {
						std::cout << pszLogMsg;
					}

					if (useFile) {
						std::ofstream out(OUTPUT_FILE, std::ios::out | std::ios::app);
						out << pszLogMsg;
						out.flush();
						out.close();
					}

				}

				ZERO_MEM(pszVarArgMsg, iVarArgMsgLen);
				ZERO_MEM(pszLogMsg, iLogMsgLen);

			};


		public:
			/**
			 * Registra uma mensagem no console.
			 *
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			PUBLIC static void log(IN const char *pszFormat, ...) {
				va_list varArgs;
				va_start(varArgs, pszFormat);
				_log(true, false, true, pszFormat, varArgs);
				va_end(varArgs);
			};

			/**
			 * Registra uma mensagem em arquivo.
			 *
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			PUBLIC static void logToFile(IN const char *pszFormat, ...) {
				va_list varArgs;
				va_start(varArgs, pszFormat);
				_log(false, true, true, pszFormat, varArgs);
				va_end(varArgs);
			};

			/**
			 * Registra uma mensagem no console sem <i>timestamp</i>.
			 *
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			PUBLIC static void logWithoutTimestamp(IN const char *pszFormat, ...) {
				va_list varArgs;
				va_start(varArgs, pszFormat);
				_log(true, false, false, pszFormat, varArgs);
				va_end(varArgs);
			};

			/**
			 * Registra uma mensagem em arquivo sem <i>timestamp</i>.
			 *
			 * @param pszFormat
			 *				o <code>char *</code> que representa a mensagem
			 */
			PUBLIC static void logToFileWithoutTimestamp(IN const char *pszFormat, ...) {
				va_list varArgs;
				va_start(varArgs, pszFormat);
				_log(false, true, false, pszFormat, varArgs);
				va_end(varArgs);
			};

		}; // class Logger

	} // namespace commons

} // namespace pel203

#endif
