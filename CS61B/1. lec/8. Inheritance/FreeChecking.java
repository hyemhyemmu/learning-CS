public class FreeChecking extends BasicAccount {
    int withdraw_fee = 1;
    int free_withdrawals = 2;
    int withdrawals = 0;

    public FreeChecking(String name) {
        super(name);
    }

    @Override
    public String withdraw(double amount) {
        withdrawals++;
        if (withdrawals > free_withdrawals)
            amount += withdraw_fee;
        return super.withdraw(amount);
    }
}
