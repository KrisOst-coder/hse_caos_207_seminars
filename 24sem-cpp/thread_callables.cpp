#include <iostream>
#include <thread>

struct A {
    void operator()() {
        std::cout << "A is called" << std::endl;
    }

    void operator()(int i) {
        std::cout << "A is called with param: " << i << std::endl;
    }
};

struct B {
    static void call_stat() {
        std::cout << "B static is called" << std::endl;
    }

    void call() {
        std::cout << "B is called" << std::endl;
    }
};


int main() {
    A a;
    std::thread t_a(a, 10);
    // std::thread t_a(a);
    t_a.join();

    {
        B b;
        std::thread t_b(&B::call, &b);
        t_b.join();
    }

    {
        B b;
        std::thread t_b(B::call_stat);
        t_b.join();
    }


   int val = 5;
   std::thread t_l(
       [val]() {
           std::cout << "Lambda called with val=" << val << std::endl;
       }
   );
   t_l.join();


    std::thread t_init(a);
    std::thread t_new(std::move(t_init));

    t_new.join();
}
