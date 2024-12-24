# class
class Account:
    interest = 0.05

    def __init__(self, account_holder):
        # define attributes
        self.balance = 0
        self.holder = account_holder

    def deposit(self, amount):
        self.balance = self.balance + amount
        return self.balance

    def withdraw(self, amount):
        if amount > self.balance:
            return 'Insufficient funds'
        self.balance = self.balance - amount
        return self.balance


class CheckingAccount(Account):
    interest = 0.02
    withdraw_fee = 1

    def withdraw(self, amount):
        return Account.withdraw(self, amount + self.withdraw_fee)


class Bank:
    """a bank **has** accounts"""
    def __init__(self):
       self.accounts=[]

    def open_accounts(self,holder,amount,kind=Account):
        account=kind(holder)
        account.deposit(amount)
        self.accounts.append(account)
        return account

    def pay_interest(self):
        for a in self.accounts:
            a.deposit(a.balance*a.interest)

    def too_big_to_fail(self):
        return len(self.accounts)>1