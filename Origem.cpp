#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>  
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include <Windows.h>

#define QUANTIDADE_DE_NUMEROS_ALEATORIOS 100
#define QUANTIDADE_DE_EXECUCOES_DE_UMA_THREAD 5

void ordenaInsercao(std::vector<float> v);
void ordenaSelecao(std::vector<float> v);
void ordenaBolha(std::vector<float> v);
std::array<std::thread, 3> threads;

int main()
{
	int i;
	std::vector<float> listaAleatoria;
	
	for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++)
	{
		float valor = rand() % 10000 + 1;
		float raizQuadradaDoValor = sqrt(valor);
		listaAleatoria.push_back(raizQuadradaDoValor);
	}

	//for (i = 0; i < QUANTIDADE_DE_EXECUCOES_DE_UMA_THREAD; i++)
	//{
	//	std::thread t_bolha(ordenaBolha);
	//	std::thread t_insercao(ordenaInsercao);
	//	std::thread t_selecao(ordenaSelecao);
	//	t_bolha.join();
	//	t_insercao.join();
	//	t_selecao.join();
	//	Sleep(10);
	//}
	///*for (i = 0; i < QUANTIDADE_DE_EXECUCOES_DE_UMA_THREAD; i++)
	//{
	//	std::thread t_insercao(ordenaInsercao);
	//	t_insercao.join();
	//	Sleep(10);
	//}
	//for (i = 0; i < QUANTIDADE_DE_EXECUCOES_DE_UMA_THREAD; i++)
	//{
	//	std::thread t_selecao(ordenaSelecao);
	//	t_selecao.join();
	//	
	//	Sleep(10);
	//}*/
	std::thread t_insercao(ordenaInsercao, listaAleatoria);
	std::thread t_selecao(ordenaSelecao, listaAleatoria);
	std::thread t_bolha(ordenaBolha, listaAleatoria);
	t_bolha.join();
	t_insercao.join();
	t_selecao.join();
	//ordenaInsercao(listaAleatoria);
	//ordenaSelecao(listaAleatoria);
	return 0;
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
