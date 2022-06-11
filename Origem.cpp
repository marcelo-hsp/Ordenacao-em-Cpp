#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#define QUANTIDADE_DE_NUMEROS_ALEATORIOS 100

void foo();
void ordenaInsercao(std::vector<int> v);


int main()
{
	std::thread t1 (foo);
	t1.join();
	return 0;
}

void foo()
{
	std::cout << "foo" << std::endl;
}

void ordenaInsercao(std::vector<int> v) {
	int inicial, atual;
	int aux;

	std::cout << std::endl << "Ordenando crescente pelo metodo de insercao!" << std::endl;
	for (inicial = 1; inicial < n; inicial++) {
		for (atual = inicial - 1; atual >= 0 && v[atual] > v[atual + 1]; atual--) {
			aux = v[atual];
			v[atual] = v[atual + 1];
			v[atual + 1] = aux;
		}
	}
}