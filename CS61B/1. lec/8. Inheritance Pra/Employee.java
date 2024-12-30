abstract class Employee {
    private final String name; //set to name cuz we don't want others to change it
    private final String id;
    private final int baseSalary;

    public Employee(String name, String id, int baseSalary) {
        this.name = name;
        this.id = id;
        this.baseSalary = baseSalary;
    }

    public int getBaseSalary() {
        return baseSalary;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public abstract double calculateMonthlySalary();
}
