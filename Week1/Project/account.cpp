#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <cassert>

#include "account.h"

// ACCOUNT IMPLEMENTATION //
Account::Account(unsigned long i, const std::string& name, const std::string& ss) : id(i), holderName(name), ssn(ss)
{
	time_t time = std::time(nullptr);
	const tm* timeNow = std::localtime(&time);
	dateCreated = asctime(timeNow);
	dateCreated.pop_back(); // Call 'pop_back' because asctime automatically inserts a newline char (probably for some internal formatting reason)
}

unsigned long Account::getID() const { return id; }
const std::string& Account::getHolderName() const { return holderName; }
const std::string& Account::getDateCreated() const { return dateCreated; }

std::string Account::getSSNLastFour() const { return "***-**-" + ssn.substr(7,4); }

std::string Account::to_string() const
{
	std::stringstream stringStream;
	stringStream.flush();
	stringStream << "Account #: " << std::to_string(id) << "; Holder: " << holderName << "; SSN: " << getSSNLastFour() << "; Date Created: " << dateCreated;
	return stringStream.str();
}

// ACCOUNTLIST::ACCOUNTSEARCHRESULT IMPLEMENTATION //
void AccountList::AccountSearchResult::add(Account* a) { accounts.push_back(a); }
void AccountList::AccountSearchResult::clear() { accounts.clear(); }
void AccountList::AccountSearchResult::sort(const std::string& term) // Because we want the closest result to come up first, we should implement sort logic. This isn't very fast, however.
{
	cmp_functor_wrapper.term = term; // We can set the term here...
	std::sort(accounts.begin(), accounts.end(), cmp_functor_wrapper); // And once we execute the sort, we can think of this as telling the sort function to call cmp_functor_wrapper(A,B)
}

const std::vector<Account*>& AccountList::AccountSearchResult::vector() { return accounts; }
Account* AccountList::AccountSearchResult::at(size_t index) const { return accounts.at(index); }
size_t AccountList::AccountSearchResult::size() const { return accounts.size(); }

// ACCOUNTLIST IMPLEMENTATION //
AccountList::AccountList()
{
}
AccountList::~AccountList()
{
	for (unsigned i=0; i < accounts.size(); i++)
		delete accounts[i];
}

std::vector<Account*> AccountList::vector() const { return accounts; }
size_t AccountList::size() const { return accounts.size(); }
Account* AccountList::at(unsigned index) const
{
	assert(index < accounts.size() &&
			index >= 0);
	return accounts[index];
}

Account* AccountList::add_account(const std::string& accountHolderName, const std::string& accountHolderSSN)
{
	// Implement queue logic for overwriting old ids?
	Account* newAcct = new Account(accounts.size() + 1, accountHolderName, accountHolderSSN); // Accounts.size() + 1 because 0 is RESERVED
	accounts.push_back(newAcct);
	return newAcct;
}

bool AccountList::close_account(unsigned int id) // Returns true on successful removal
{
	for (auto it = accounts.begin(); it != accounts.end(); it++)
	{
		if ((*it)->getID() == id)
		{
			delete *it;
			accounts.erase(it);
			return true;
		}

	}
	return false;
}

size_t AccountList::get_accounts_by_name(const std::string& queryTerm, AccountSearchResult& res) const
{
	size_t count = 0;
	for (Account* a : accounts)
	{
		if (a->getHolderName().find(queryTerm) != std::string::npos)
		{
			res.add(a);
			count++;
		}
	}
	if (count > 1)
		res.sort(queryTerm);
	return count;
}

Account* AccountList::get_account_by_id(unsigned long queryId) const
{
	for (Account* a : accounts)
		if (a->getID() == queryId)
			return a;
	return nullptr;
}
