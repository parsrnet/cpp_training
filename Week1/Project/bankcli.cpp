#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
#include <cassert>
#include <algorithm> // std::sort
#include <regex> // For new account input sanitization/checking

#include "account.h"

// COMMANDS //
// show acounts 	> Display all accounts
// search name 		> Search accounts by name
// new account		> Create a new account
// close account	> Close an account by id
// quit			> Quits program


// FORWARD DECLARATIONS //

// ATTEMPT LOGIN
// 	(std::string) user: Username
// 	(std::string) pass: Password
// 	Returns 'true' on valid credentials
// 	Returns 'false' on invalid credentials

typedef enum { VIEW_RESULT_OK, VIEW_RESULT_INVALID_INPUT, VIEW_RESULT_ERROR } view_result_et;
typedef enum { PROMPT_RESULT_OK, PROMPT_RESULT_INVALID_INPUT } prompt_result_et;

std::string 	promptStr		(const std::string& promptText);
std::string	promptStrR		(const std::string& promptText, const std::regex& reg, prompt_result_et& res);
int		promptInt		(const std::string& promptText, prompt_result_et& res);
long		promptLong		(const std::string& promptText, prompt_result_et& res);

bool 		attempt_login		(const std::string& user, const std::string& pass);
view_result_et	view_login		();
view_result_et 	view_show_accounts	(const AccountList&);
view_result_et 	view_display_account	(const AccountList&);
view_result_et 	view_search_name	(const AccountList&);
view_result_et	view_new_account	(AccountList&);
view_result_et	view_close_account	(AccountList&);

const std::string embeddedUsername = "admin";
const std::string embeddedPassword = "password";

int main(void)
{
	/* Adding some account dummy data */
	AccountList accounts = AccountList();
	accounts.add_account("Joshua M. Willis", "123-45-6789");
	accounts.add_account("Manoj Joshi", "321-54-9876");
	accounts.add_account("Phillip Goldfarb", "842-20-1273");
	accounts.add_account("Joshua Peterson", "519-21-1928");
	

	/* Login */
	view_result_et loginResult;;
	
	do
	{
		std::cout << "Please enter valid credentials." << std::endl;
		loginResult = view_login();

		if (loginResult == VIEW_RESULT_INVALID_INPUT)
			std::cout << "Credentials invalid." << std::endl;
	}
	while (loginResult != VIEW_RESULT_OK);

	/* Menu */
	std::string input;
	view_result_et viewResult;
	for (;;)
	{
		input = promptStr("Menu >");

		if (input.compare("show accounts") == 0)
		{
			viewResult = view_show_accounts(accounts);
		}
		else if (input.compare("display account") == 0)
		{
			viewResult = view_display_account(accounts);
		}
		else if (input.compare("search name") == 0)
		{
			viewResult = view_search_name(accounts);
		}
		else if (input.compare("new account") == 0)
		{
			viewResult = view_new_account(accounts);
		}
		else if (input.compare("close account") == 0)
		{
			viewResult = view_close_account(accounts);
		}
		else if (input.compare("quit") == 0 || input.compare("exit") == 0)
		{
			break;
		}
	}
}

// Prompt user prompt, return string which is user input
std::string promptStr(const std::string& prompt)
{
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	return input;
}

// Prompt user prompt, match string reg, 
std::string promptStrR(const std::string& prompt, const std::regex& reg, prompt_result_et& res)
{
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	if (regex_match(input, reg))
	{
		res = PROMPT_RESULT_OK;
		return input;
	}
	else
	{
		res = PROMPT_RESULT_INVALID_INPUT;
		return "";
	}
}

// Prompt user prompt, OK or INVALID res, returns user input as int (or -1 on failure)
int promptInt(const std::string& prompt, prompt_result_et& res)
{
	auto r = std::regex("[0-9]+");
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	if (regex_match(input, r))
	{
		res = PROMPT_RESULT_OK;
		return std::stoi(input);
	}
	else
	{
		res = PROMPT_RESULT_INVALID_INPUT;
		return -1;
	}
}

// Prompt user prompt, OK  or INVALID res, and returns user input as long (or -1 on failure)
long promptLong(const std::string& prompt, prompt_result_et& res)
{
	auto r = std::regex("[0-9]+");
	std::cout << prompt;
	std::string input;
	std::getline(std::cin, input);
	if (regex_match(input, r))
	{
		res = PROMPT_RESULT_OK;
		return std::stol(input);
	}
	else
	{
		res = PROMPT_RESULT_INVALID_INPUT;
		return -1;
	}
}

// returns true on credentials successfully validated
bool attempt_login(const std::string& user, const std::string& pass)
{
	return user.compare(embeddedUsername) == 0 && pass.compare(embeddedPassword) == 0;
}

// This view displays the login and returns VIEW_RESULT_OK on successful login
view_result_et view_login()
{
	std::string user = promptStr("Username >");
	std::string pass = promptStr("Password >");

	if (attempt_login(user, pass))
		return VIEW_RESULT_OK;
	else
		return VIEW_RESULT_INVALID_INPUT;
}

// This view will show all accounts
view_result_et view_show_accounts(const AccountList& accounts)
{
	for (auto account : accounts.vector())
		std::cout << account->to_string() << std::endl;
	return VIEW_RESULT_OK;
}

// This view will display an account by account #
view_result_et view_display_account(const AccountList& accounts)
{
	// Prompt user for account id
	prompt_result_et promptRes;
	unsigned long queryId;
	do
	{
		queryId = (unsigned long) promptLong("account >", promptRes);
		if (promptRes == PROMPT_RESULT_INVALID_INPUT)
			std::cout << "Must enter a valid number [0-99999999...]" << std::endl;
	}
	while (promptRes != PROMPT_RESULT_OK);
	
	Account* found = accounts.get_account_by_id(queryId);
	if (found != nullptr)
		std::cout << found->to_string() << std::endl;
	else
		std::cout << "invalid account" << std::endl;
	
	return VIEW_RESULT_OK;
}

// This view is for conducting a search-by-name
view_result_et view_search_name(const AccountList& accounts)
{
	// Prompt user for names
	std::string input = promptStr("name >");

	// Perform a search
	AccountList::AccountSearchResult results;
	std::cout << "SEARCHING " << input << std::endl;
	size_t resCount = accounts.get_accounts_by_name(input, results);
	std::cout << "FOUND " << resCount << " RESULTS" << std::endl;

	if (resCount == 1)
	{
		// Single search result found!
		std::cout << "Single match found" << std::endl;
		std::cout << results.at(0)->to_string() << std::endl;
	}
	else if (resCount > 0 && resCount <= 10)
	{
		// Search good!
		// Show results: Ask for clarification
		for (;;)
		{
			// This could potentially be a function with params const AccountList::AccountSearchResults&

			unsigned i;
			for (i=0; i < resCount; i++)
				std::cout << i << ") " << results.at(i)->getHolderName() << std::endl;
			std::cout << resCount << ") " << "Home" << std::endl;
			
			// Get line number and corresponding account
			prompt_result_et lineNumberRes;
			int lineNumber;
			promptInt("select number >", lineNumberRes);
			
			if (lineNumberRes != PROMPT_RESULT_OK) // If the prompt failed (user entered in nan)
			{
				std::cout << "Must enter a valid number [0-" << resCount << "]..." << std::endl;
				continue;
			}
			else if (lineNumber == resCount) // If the user entered in option to return to home
			{
				std::cout << "Returning to home view..." << std::endl;
				break;
			}
			else if (lineNumber >= 0 && lineNumber < resCount) // If the user entered a number corresponding to a result
			{
				std::cout << results.at(lineNumber)->to_string() << std::endl;
				break;
			}
			else // If it was a number, but not within the correct range
			{
				std::cout << "invalid number" << std::endl;
				continue;
			}
		}
	}
	else // No results found
		std::cout << "No results found for \"" << input << "\"." << std::endl;
	return VIEW_RESULT_OK;
}

// This view is for creating a new account //
view_result_et view_new_account(AccountList& accounts)
{
	// Set up values for a new account...
	std::string newAccountName, newAccountSSN;

	// Prompt for new name...
	std::string input;
	std::regex validName("([a-zA-Z]+[\\s]?)+");
	prompt_result_et res;
	
	for (;;)
	{
		input = promptStrR("customer name >", validName, res);
		if (res == PROMPT_RESULT_OK)
		{
			newAccountName = input;
			break;
		}
		else
		{
			std::cout << "Incorrect format (alphanumerical characters and spaces only)" << std::endl;
			input = "";
		}
	}

	// Prompt for SSN...
	std::regex validSSN("[0-9]{3}-[0-9]{2}-[0-9]{4}");
	input = "";
	for (;;)
	{
		input = promptStrR("customer SSN >", validSSN, res);
		if (regex_match(input, validSSN))
		{
			newAccountSSN = input;
			break;
		}
		else
		{
			std::cout << "Incorrect format (xxx-xx-xxxx)" << std::endl;
			input = "";
		}
	}

	auto newAcct = accounts.add_account(newAccountName, newAccountSSN);
	std::cout << "New account created" << std::endl << newAcct->to_string() << std::endl;
	// Delete newAcct pointer?
	
	return VIEW_RESULT_OK;
}

// This view prompts the user for an id and 
view_result_et view_close_account(AccountList& accounts)
{
	prompt_result_et res;
	unsigned long id = (unsigned long) promptLong("account >", res);

	if (res != PROMPT_RESULT_OK)
		std::cout << "Must enter a valid number..." << std::endl;
	else
	{
		auto acctToDelete = accounts.get_account_by_id(id);
		if (acctToDelete != nullptr)
		{
			for (;;)
			{
				std::string input = promptStr("Really delete account " + std::to_string(id) + "?\n" + acctToDelete->to_string() + "\nPlease confirm (Y/N):");
				if (input.compare("Y") == 0|| input.compare("y") == 0)
				{
					std::cout << "Deleting account " << id << "..." << std::endl;
					bool success = accounts.close_account(id);
					std::cout << (success ? "Operation successful" : "Operation unsuccessful") << std::endl;
					break;
				}
				else if (input.compare("N") == 0 || input.compare("n") == 0)
				{
					std::cout << "operation aborted" << std::endl;
					break;
				}
			}
		}
		else
			std::cout << "could not find account # of " << id << std::endl;
	}
	return VIEW_RESULT_OK;
}
