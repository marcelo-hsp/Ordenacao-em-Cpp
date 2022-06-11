#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>  
#include <fstream>

#define QUANTIDADE_DE_NUMEROS_ALEATORIOS 100

void foo();
void ordenaInsercao(std::vector<float> v);
void ordenaSelecao(std::vector<float> v);
void ordenaBolha(std::vector<float> v);

int main()
{
	std::vector<float> listaAleatoria;

	std::thread t1 (foo);
	t1.join();

	int i;
	for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++)
	{
		float valor = rand() % 10000 + 1;
		float raizQuadradaDoValor = sqrt(valor);
		listaAleatoria.push_back(raizQuadradaDoValor);
	}

	ordenaBolha(listaAleatoria);
	ordenaInsercao(listaAleatoria);
	ordenaSelecao(listaAleatoria);
	return 0;
}

void foo()
{
	std::cout << "foo" << std::endl;
}

void ordenaInsercao(std::vector<float> v) {
	int inicial, atual;
	int aux;
	auto start = std::chrono::system_clock::now();
	for (inicial = 1; inicial < QUANTIDADE_DE_NUMEROS_ALEATORIOS; inicial++) {
		for (atual = inicial - 1; atual >= 0 && v[atual] > v[atual + 1]; atual--) {
			aux = v[atual];
			v[atual] = v[atual + 1];
			v[atual + 1] = aux;
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
	std::fstream meuArquivo;
	meuArquivo.open("insercao.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
}

void ordenaSelecao(std::vector<float> v) {
	int i;
	int valMenor, aux;
	int posMenor;
	int inicial;
	auto start = std::chrono::system_clock::now();
	for (inicial = 0; inicial < QUANTIDADE_DE_NUMEROS_ALEATORIOS - 1; inicial++) {
		valMenor = v[inicial];
		posMenor = inicial;
		for (i = inicial + 1; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++) {
			if (v[i] < valMenor) {
				valMenor = v[i];
				posMenor = i;
			}
		}
		if (posMenor != inicial) {
			aux = v[posMenor];
			v[posMenor] = v[inicial];
			v[inicial] = aux;
		}
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::fstream meuArquivo;
	meuArquivo.open("selecao.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
}

void ordenaBolha(std::vector<float> v) {
	int i, troca;
	int aux;
	auto start = std::chrono::system_clock::now();
	do {
		troca = 0;
		for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS - 1; i++) {
			if (v[i] > v[i + 1]) {
				aux = v[i + 1];
				v[i + 1] = v[i];
				v[i] = aux;
				troca = 1;
			}
		}
	} while (troca == 1);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::fstream meuArquivo;
	meuArquivo.open("bolha.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
}


//std::vector<int> listaAleatoria()
//{
//	std::vector<int>listaAleatoria;
//	int i;
//	for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++)
//	{
//		float valor = rand() % 10000 + 1;
//		float raizQuadradaDoValor = sqrt(valor);
//		listaAleatoria.push_back(raizQuadradaDoValor);
//	}
//	return listaAleatoria;
//}