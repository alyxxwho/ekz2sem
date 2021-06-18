#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>

class Boat {
protected:
    std::string name;
    double max_speed{};
public:
    // Конструктор по умолчанию
    Boat() :  name("Null"), max_speed(0) {}

    // Деструктор
    virtual ~Boat() = default;

    // Оператор присваивания копированием
    Boat& operator=(const Boat& rhs) = default;

    // Пользовательский конструктор
    Boat(std::string _name, double _max_speed) {
        name = std::move(_name);
        max_speed = _max_speed;
    }

    // Метод для печати полей в поток вывода
    virtual void Print() const {
        std::cout << "Name: " << name << "; Maximum speed: " << max_speed;
    }

////////////////////////////////
//    friend std::ostream &operator<<(std::ostream &out, const Boat &b);

};
/*
std::ostream &operator<<(std::ostream &out, const Boat &b) {
    out << "Name: " << b.name << "; Maximum speed: " << b.max_speed;
}
*/

//////////////////////////////////////////////////

class Liner : public Boat {
private:
    int max_pass;
public:
    Liner() : Boat("Null", 0) { max_pass = 0; };

    ~Liner() = default;

    Liner& operator=(const Liner& rhs) = default;

    Liner(std::string _name, double _max_speed, int _max_pass) :
    Boat(_name, _max_speed) { max_pass = _max_pass; }

    void Print() const override{
        Boat::Print();
        std::cout << "; " << "Maximum passengers: " << max_pass << std::endl;
    }

};

////////////////////////////////////////////////

struct L_Boat {
    std::string Name;
    double Max_speed;
    int Max_pass;
};

std::mutex m;

void print(std::vector<L_Boat> c) {
//    for (const L_Boat &a : c) {
//        std::lock_guard<std::mutex> lock(m);
//        std::cout << a.Name << " " << a.Max_speed << " " << a.Max_pass << std::endl;
//     }
    m.lock();
    for (const L_Boat &a : c) {
        std::cout << a.Name << " " << a.Max_speed << " " << a.Max_pass << std::endl;
    }
    m.unlock();
}


////////////////////////////////////////////////

int main() {
    Boat b0 = Boat();
    b0.Print();
    std::cout << std::endl << std::endl;

    Boat b1 = Boat("Alexa", 113.2);
    b1.Print();
    std::cout << std::endl << std::endl << std::endl;

    /////////////

//    Boat b2 = Boat("Nina", 99);
//    std::cout << b2;

    /////////////////////////////

    Liner l0 = Liner();
    l0.Print();
    std::cout << std::endl;

    Liner l1 = Liner("Maria", 235, 1028);
    l1.Print();
    std::cout << std::endl << std::endl << std::endl;

    //////////////////////////////

    std::vector<L_Boat> c1 = {{"A", 0, 0},
                             {"B", 123, 100},
                             {"C", 234, 200}};
    std::vector<L_Boat> c2 = {{"D", 0.2,  1},
                             {"E", 150, 199},
                             {"F", 250, 299}};
//    std::vector<L_Boat> c3 = {{"G", 0.2,  1},
//                              {"H", 150, 199},
//                              {"J", 250, 299}};

    std::thread t1(print, c1);
    std::thread t2(print, c2);
//    std::thread t3(print, c3);

    t1.join();
    t2.join();
//    t3.join();

    return 0;
}
