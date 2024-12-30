public class Developer extends Employee implements Bonus {
    int completedProjects;
    int bugFixCount;

    public Developer(String name, String id, int baseSalary, int completedProjects, int bugFixCount) {
        super(name, id, baseSalary);
        this.completedProjects = completedProjects;
        this.bugFixCount = bugFixCount;

    }


    @Override
    public double calculateBonus() {
        return 2000 * this.completedProjects + 100 * this.bugFixCount;
    }

    @Override
    public double calculateMonthlySalary() {
        // 月薪 = 基本工资 + 奖金
        return getBaseSalary() + calculateBonus();
    }
}
