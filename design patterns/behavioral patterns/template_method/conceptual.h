#pragma once
#include <iostream>

/**
 * Абстрактный Класс определяет шаблонный метод, содержащий скелет некоторого
 * алгоритма, состоящего из вызовов (обычно) абстрактных примитивных операций.
 *
 * Конкретные подклассы должны реализовать эти операции, но оставить сам
 * шаблонный метод без изменений.
 */

class abstract_class
{
public:
	void template_method() const
	{
		base_operation1();
		required_operation1();
		base_operation2();
		hook1();
		required_operation1();
		required_operation1();
		base_operation3();
		hook2();
	}
	void base_operation1() const {
		std::cout << "AbstractClass says: I am doing the bulk of the work\n";
	}
	void base_operation2() const {
		std::cout << "AbstractClass says: But I let subclasses override some operations\n";
	}
	void base_operation3() const {
		std::cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
	}

   /**
   * А эти операции должны быть реализованы в подклассах.
   */
	virtual void required_operation1() const = 0;
	virtual void required_operation2() const = 0;
	/**
	 * Это «хуки». Подклассы могут переопределять их, но это не обязательно,
	 * поскольку у хуков уже есть стандартная (но пустая) реализация. Хуки
	 * предоставляют дополнительные точки расширения в некоторых критических
	 * местах алгоритма.
	 */
	virtual void hook1() const {}
	virtual void hook2() const {}
};

class concrete_class1 : public abstract_class
{
protected:
	void required_operation1() const override
	{
		std::cout << "ConcreteClass1 says: Implemented Operation1\n";
	}

	void required_operation2() const override
	{
		std::cout << "ConcreteClass1 says: Implemented Operation2\n";
	}
};

class concrete_class2 : public abstract_class {
protected:
	void required_operation1() const override {
		std::cout << "ConcreteClass2 says: Implemented Operation1\n";
	}
	void required_operation2() const override {
		std::cout << "ConcreteClass2 says: Implemented Operation2\n";
	}
	void hook1() const override {
		std::cout << "ConcreteClass2 says: Overridden Hook1\n";
	}
};

void client_code(abstract_class* c)
{
	c->template_method();
}