#pragma once

#ifndef _MENU_H_
#define _MENU_H_

#include <string>
#include <vector>
#include <algorithm>

#include <inc/Utils.h>
#include <inc/Logger.h>

// estrutura que representa uma opcao do menu
typedef struct tagMenuOption {
    const int iOptionId;
    const char *pszOptionName;
    void (* pfnFunction)();
} MENU_OPTION, *PMENU_OPTION;

namespace pel216 {

	namespace commons {

		/**
		 * Classe do menu com o usuario.
		 *
		 * @author arrebola
		 */
		class Menu {

		public:
			/**
			 * Obtem a opcao selecionada em um menu.
			 *
			 * @param menu
			 *            o vetor de <code>MENU_OPTION</code> que representa as opcoes do menu
			 *
			 * @return o <code>PMENU_OPTION</code> que representa a opcao selecionada
			 */
			static PMENU_OPTION pickMenuOption(MENU_OPTION menu[], std::string title = "Lista de comandos disponiveis") {

			    PMENU_OPTION pCommand = NULL;

			    pel216::commons::Logger::log("\n");
				pel216::commons::Logger::log("%s\n", title.c_str());

			    int iListIdx = 0;
			    while (menu[iListIdx].pszOptionName) {
			    	pel216::commons::Logger::log("%2.0d - %s\n", iListIdx + 1, menu[iListIdx].pszOptionName);
			        iListIdx++;
			    }

			    int iChosenIdx = 0;
			    pel216::commons::Logger::log("Escolha o comando [1-%d]: ", iListIdx);
			    std::cin >> iChosenIdx;

			    if (iChosenIdx > 0 && iChosenIdx < iListIdx + 1) {
			        pCommand = (PMENU_OPTION)(&menu[iChosenIdx - 1]);
			    } else {
			        pCommand = pickMenuOption(menu);
			    }

			    return pCommand;

			};

		}; // class Menu

	} // namespace commons

} // namespace pel216


#endif
