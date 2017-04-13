#include <iostream>

class World {
public:
    World() {
	std::cout << "Hello World!" << std::endl;
    }
    ~World() {
	// destructor never takes any arguments
	std::cout << "Goodbye!" << std::endl;
    }
};

World TheWorld;

int main() {
}
