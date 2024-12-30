public class BasicAccount implements Account {
    public int balance = 0;
    public int withdrawal = 10;
    public double interest = 0.02;
    String name;

    public BasicAccount(String name) {
        this.name = name;
    }

    @Override
    public int deposit(int amount) {
        this.balance = balance + amount;
        return this.balance;
    }

    @Override
    public String withdraw(double amount) {
        if (amount > balance) {
            return "Insufficient funds";
        }
        if (amount > withdrawal) {
            return "Can't withdraw that amount";
        }
        this.balance -= (int) amount;
        return "New balance: " + this.balance;
    }
}
