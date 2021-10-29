#include <iostream>
#include <regex>
#include <mutex>
#include <future>
#include <thread>

class X {
    std::string s;
    std::mutex m;
public:
    X(const std::string& ss) : s(ss) {}
    X& operator=(X&& r) noexcept;
    friend void swap(X& l, X& r);
    std::string& get() { return s; }
};


X& X::operator=(X&& r) noexcept {
    if (this == &r) {
        return *this;
    }

    /*
    std::unique_lock<std::mutex> ull(m);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> ulr(r.m);
    
    std::lock(m, r.m);
    std::lock_guard<std::mutex> l1(m, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(r.m, std::adopt_lock);
    */

    std::scoped_lock guard(m, r.m);

    s = std::move(r.s);

    return *this;
}

void swap(X& l, X& r) {
    if (&l == &r) {
        return;
    }

    /*
    std::unique_lock<std::mutex> ull(l.m);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> ulr(r.m);
    
    std::lock(l.m, r.m);
    std::lock_guard<std::mutex> l1(l.m, std::adopt_lock);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::lock_guard<std::mutex> l2(r.m, std::adopt_lock);
    */

    std::scoped_lock guard(l.m, r.m);

    std::swap(l.s, r.s);
}

int main() {

    if (std::regex_match("The secure channel instance to store is NULL.\x00", std::regex("^.*secure.*$")))
        std::cout << "string:literal => matched\n";

    X x1("David"), x2("Daria");

    std::cout << x1.get() << " : " << x2.get() << std::endl;

    std::thread t1(swap, std::ref(x2), std::ref(x1)); // op 1 on thread 1

  //  std::cout << x1.get() << " : " << x2.get() << std::endl;

    std::thread t2([&x1, &x2]() {x1 = std::move(x2); });
    t1.join();
    t2.join();

    std::cout << x1.get() << " : " << x2.get() << std::endl;

    return 0;
}