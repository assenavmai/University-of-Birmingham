#include <iostream>

class Animal{

	public: virtual void speak() {
		std::cout << "Noise\n";
	}
};

class Pig : public Animal {

	public: void speak() {
		std::cout << "Oink!\n";
	}
};
int main(int argc, char const *argv[])
{
	std::cout << "Hello World" << std::endl;

	Animal * peppa = new Pig();
	peppa->speak();


	return 0;
}