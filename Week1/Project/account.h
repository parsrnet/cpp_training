class Account
{
private:
	const unsigned long id;
	std::string holderName;
	std::string ssn;
	std::string dateCreated;
public:
	Account(unsigned long i, const std::string& name, const std::string& ss);

	unsigned long getID() const;
	const std::string& getHolderName() const;
	const std::string& getDateCreated() const;
	std::string getSSNLastFour() const;
	std::string to_string() const;
};



class AccountList
{
public:
	enum : unsigned long { INVALID_ACCOUNT = 0 };
	/* IMPORTANT NOTE
	 * 	get_account_by ... : Returns SINGLE ACCOUNT POINTER - ALWAYS - SHOULD ONLY EVER RETURN A SINGLE VALUE.
	 * 	get_accounts_by .. : (Note the plural!!!) Returns NUMBER OF INSTANCE FOUND  A-L-W-A-Y-S, PASSES AccountSearchResult BY REFERENCE A-L-W-A-Y-S
	 */
	struct AccountSearchResult
	{
		friend class AccountList;
	private:
		struct {
			std::string term;
			size_t operator () (Account* A, Account* B) const { return A->getHolderName().find(term) < B->getHolderName().find(term); } // We overload the () operator: this is our comparison logic
		} cmp_functor_wrapper; // Functor for comparison function. This way we can sort using an indeterminate term which is very important and we don't have to implement custom sort logic!

		std::vector<Account*> accounts;
		void add(Account* a);
		void clear();
		void sort(const std::string& term); // Because we want the closest result to come up first, we should implement sort logic. This isn't very fast, however.
	public:
		const std::vector<Account*>& vector();
		Account* at(size_t index) const;
		size_t size() const;
	};
private:
	std::vector<Account*> accounts;
public:
	friend struct AccountSearchResult; // Declare a friend: Now we can access private methods
	AccountList();
	~AccountList();
	
	std::vector<Account*> vector() const;
	size_t size() const;
	Account* at(unsigned index) const;

	Account* add_account(const std::string& accountHolderName, const std::string& accountHolderSSN);
	bool close_account(unsigned int id); // Returns true on successful removal

	size_t get_accounts_by_name(const std::string& queryTerm, AccountSearchResult& res) const;
	Account* get_account_by_id(unsigned long queryId) const;
};

