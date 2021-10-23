#include <iostream>

/**
 * Целевой класс объявляет интерфейс, с которым может работать клиентский код.
 */
class Target {
public:
	virtual ~Target() = default;
	virtual std::string request() const {
		return "Target: The default target's behavior.";
	}
};

/**
 * Адаптируемый класс содержит некоторое полезное поведение, но его интерфейс
 * несовместим с существующим клиентским кодом. Адаптируемый класс нуждается в
 * некоторой доработке, прежде чем клиентский код сможет его использовать.
 */
class Adaptee {
public: 
	std::string specific_request() const {
		return ".eetpadA eht fo roivaheb laicepS";
	}
};

/**
 * Адаптер делает интерфейс Адаптируемого класса совместимым с целевым
 * интерфейсом.
 */
class Adapter : public Target {
	Adaptee* adaptee;
public:
	Adapter(Adaptee* adaptee_) : adaptee(adaptee_) {}
	std::string request() const override {
		std::string to_reverse = adaptee->specific_request();
		std::reverse(to_reverse.begin(), to_reverse.end());
		return "Adapter: (TRANSLATED) " + to_reverse;
	}
};

/*
 * Клиентский код поддерживает все классы, использующие целевой интерфейс.
 */
void clientCode(const Target* target) {
	std::cout << target->request();
}

int main() {
	std::cout << "Client: I can work just fine with the Target objects:\n";
	Target* target = new Target;
	clientCode(target);
	std::cout << "\n\n";

	Adaptee* adaptee = new Adaptee;
	
	std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
	std::cout << "Adaptee: " << adaptee->specific_request();
	std::cout << "\n\n";

	std::cout << "Client: But I can work with it via the Adapter:\n";
	Adapter* adapter = new Adapter(adaptee);
	clientCode(adapter);
	std::cout << "\n";

	delete target;
	delete adaptee;
	delete adapter;

	return 0;
}