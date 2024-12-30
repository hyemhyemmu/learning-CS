public class EmployeeTest {
    public static void main(String[] args) {
        // 创建一个经理对象：姓名"张三"，工号"M001"，基本工资15000，管理5人团队，绩效分90分
        Manager manager = new Manager("张三", "M001", 15000, 5, 90);

        // 创建一个开发人员对象：姓名"李四"，工号"D001"，基本工资12000，完成2个项目，修复10个bug
        Developer developer = new Developer("李四", "D001", 12000, 2, 10);

        // 计算并输出他们的月薪
        System.out.println("经理 " + manager.getName() + " 的月薪是: " + manager.calculateMonthlySalary());
        System.out.println("开发人员 " + developer.getName() + " 的月薪是: " + developer.calculateMonthlySalary());

        // 输出详细的奖金信息
        System.out.println("经理的奖金是: " + manager.calculateBonus());
        System.out.println("开发人员的奖金是: " + developer.calculateBonus());
    }
}
