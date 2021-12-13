#include <gtest/gtest.h>

#include "../account.h"

class AccountListTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		rm_.add_account("","");

		lookup_.add_account("test 1", "");
		lookup_.add_account("test 2", "");
		lookup_.add_account("test 3", "");
		lookup_.add_account("test 4", "");
		lookup_.add_account("test 5", "");
	}

	AccountList empty_;
	AccountList add_;
	AccountList rm_;

	AccountList lookup_;
};

TEST_F(AccountListTest, TestIsEmptyInit)
{
	EXPECT_EQ(empty_.size(), 0);
}

TEST_F(AccountListTest, TestAdd10)
{
	for (unsigned i=0; i < 10; i++)
		add_.add_account("","");
	EXPECT_EQ(add_.size(), 10);
}

TEST_F(AccountListTest, TestClose1)
{
	EXPECT_EQ(rm_.size(), 1);
	rm_.close_account(1);
	EXPECT_EQ(rm_.size(), 0);
}

TEST_F(AccountListTest, TestNameSearch)
{
	AccountList::AccountSearchResult result;
	EXPECT_EQ(lookup_.get_accounts_by_name("test", result), 5);
	EXPECT_EQ(result.size(), 5);
	EXPECT_EQ(result.at(0)->getHolderName(), "test 1");
}

class AccountListTestAddMany : public ::testing::Test
{
protected:
        void SetUp() override
        {
        }

        AccountList many10k;
        AccountList many100k;
        AccountList many1m;
};

TEST_F(AccountListTestAddMany, TestAdd10k)
{
	for (unsigned i=0; i < 10'000; i++)
		many10k.add_account("test "+std::to_string(i),"");
	EXPECT_EQ(many10k.size(), 10'000);
}

TEST_F(AccountListTestAddMany, TestAdd100k)
{
	for (unsigned i=0; i < 100'000; i++)
		many100k.add_account("test "+std::to_string(i),"");
	EXPECT_EQ(many100k.size(), 100'000);
}

TEST_F(AccountListTestAddMany, TestAdd1m)
{
	for (unsigned i=0; i < 1'000'000; i++)
		many1m.add_account("test "+std::to_string(i),"");
	EXPECT_EQ(many1m.size(), 1'000'000);
}

class AccountListTestMany : public ::testing::Test
{
protected:
	void SetUp() override
	{
		unsigned i=0;
		for (unsigned i=0; i < 1'000'000; i++)
		{
			if (i < 10'000)
				many10k.add_account("test "+std::to_string(i),"");
			if (i < 100'000)
				many100k.add_account("test "+std::to_string(i),"");
			if (i < 1'000'000)
				many1000k.add_account("test "+std::to_string(i),"");
		}
	}

	AccountList many10k;
	AccountList many100k;
	AccountList many1000k;
};

TEST_F(AccountListTestMany, TestSizes)
{
	EXPECT_EQ(many10k.size(), 10'000);
	EXPECT_EQ(many100k.size(), 100'000);
	EXPECT_EQ(many1000k.size(), 1'000'000);
}

TEST_F(AccountListTestMany, TestGetById10kEvery100)
{
	for (unsigned i=1; i <= 10'000; i+=100)
		EXPECT_NE(many10k.get_account_by_id(i), nullptr);
}
TEST_F(AccountListTestMany, TestGetById100kEvery100)
{
	for (unsigned i=1; i <= 100'000; i+=1000)
		EXPECT_NE(many100k.get_account_by_id(i), nullptr);
}
TEST_F(AccountListTestMany, TestGetById1000kEvery10000)
{
	for (unsigned i=1; i <= 1'000'000; i+=10'000)
		EXPECT_NE(many1000k.get_account_by_id(i), nullptr);
}

TEST_F(AccountListTestMany, TestGetByName10k)
{
	AccountList::AccountSearchResult res;
	size_t count = many10k.get_accounts_by_name("test", res);
	ASSERT_EQ(count, 10'000);
	ASSERT_EQ(res.size(), 10'000);
}

TEST_F(AccountListTestMany, TestGetByName100k)
{
	AccountList::AccountSearchResult res;
	size_t count = many100k.get_accounts_by_name("test ", res);
	ASSERT_EQ(count, 100'000);
	ASSERT_EQ(res.size(), 100'000);
}

TEST_F(AccountListTestMany, TestGetByName1000kSingle)
{
	AccountList::AccountSearchResult res;
	size_t count = many1000k.get_accounts_by_name("test 999999", res);
	ASSERT_EQ(count, 1);
	ASSERT_EQ(res.size(), 1);
}

TEST_F(AccountListTestMany, TestClose10k)
{
	for (unsigned i=1; i <= 10'000; i++)
		many10k.close_account(i);
	EXPECT_EQ(many10k.size(), 0);
}
