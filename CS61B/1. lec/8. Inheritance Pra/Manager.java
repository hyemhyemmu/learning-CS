public class Manager extends Employee implements Bonus {
    int teamSize;
    int performanceScore;

    public Manager(String name, String id, int baseSalary, int teamSize, int performanceScore) {
        super(name, id, baseSalary);
        this.performanceScore = performanceScore;
        this.teamSize = teamSize;
    }

    public double calculateBonus() {
        return this.getBaseSalary() * 0.2 + ((double) this.performanceScore / 100) + 500 * this.teamSize;
    }

    @Override
    public double calculateMonthlySalary() {
        return getBaseSalary() + calculateBonus();
    }

}
