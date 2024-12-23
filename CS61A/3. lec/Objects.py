# class
class Account:
    def __init__(self, account_holder):
        # define attributes
        self.balance = 0
        self.holder = account_holder

    def deposit(self,amount):
        self.balance=self.balance+amount
        return self.balance

    def withdraw(self,amount):
        if amount>self.balance:
            return 'Insufficient funds'
        self.balance=self.balance-amount
        return self.balance