public class Car {
    String model;
    int wheels;

    public Car(String m) {
        this.model = m;
        this.wheels = 4;
    }

    public void drive() {
        if (this.wheels == 4) {
            System.out.println(this.model + "goes vroom");
        } else {
            System.out.println(this.model + "goes pbtt");
        }
    }

    public void drive_into_ditch(int wheelslost) {
        this.wheels -= wheelslost;
    }

    public static void main(String[] args) {
        Car c1 = new Car("Tesla");
        c1.drive();
        c1.drive_into_ditch(3);
        c1.drive();
    }

}


