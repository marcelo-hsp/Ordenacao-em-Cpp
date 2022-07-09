// Marcelo Henrique de Sousa Pinheiro [Estrutura de Dados II]
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <thread>
#include <vector>

#define QUANTIDADE_DE_NUMEROS_ALEATORIOS 10000

/* Aula 09 (14/05/2022) Funções disponibilizadas no moodle [adaptadas]. */
void ordenaSelecao(std::vector<int> v);
void ordenaInsercao(std::vector<int> v);
void ordenaBolha(std::vector<int> v);

int main()
{
	setlocale(LC_ALL, "Portuguese"); // Idioma Português para acentuação
	int i;
	std::vector<int> listaAleatoria; // declaração de um vetor listaAleatoria
	
	// Criação de um vetor com a quantidade (QUANTIDADE_DE_NUMEROS_ALEATORIOS) definida na linha 19
	for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++)
	{
		int valorAleatorio = rand() % 100000 + 1; // função rand() obtida através da biblioteca cstdlib. Fornece um inteiro aleatório entre 1 e 10000.
		listaAleatoria.push_back(valorAleatorio); // adicionando o valorAleatorio a ao vetor listaAleatoria utilizando push_back()
	}

	std::fstream meuArquivo;
	meuArquivo.open("vetorDesordenado.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		i = 0;
		meuArquivo << "Vetor para ordenar:" << std::endl << "[";
		for (auto v : listaAleatoria)
		{
			meuArquivo << v << ", ";
			i++;
			if (i == 20)
			{
				meuArquivo << std::endl;
				i = 0;
			}
		}
	}
	
	//Abaixo é definido três threads: t_insercao, t_selecao e t_bolha. Cada uma recebe sua respectiva função e como argumento a mesma lista de números aleatórios
	std::cout << "Iniciando ordenações." << std::endl;
	std::thread t_selecao(ordenaSelecao, listaAleatoria);
	std::thread t_insercao(ordenaInsercao, listaAleatoria);
	std::thread t_bolha(ordenaBolha, listaAleatoria);
	/*
	* join()
	This synchronizes the moment this function returns with the completion of all the operations in the thread: This blocks the execution of the thread that calls this 
	function until the function called on construction returns (if it hasn't yet). (https://cplusplus.com/reference/thread/thread/join/)
	*/
	t_selecao.join();
	t_insercao.join(); 
	t_bolha.join();
	std::cout << "Fim de execução." << std::endl;

	return 0;
}

void ordenaInsercao(std::vector<int> v) 
{
	int inicial, atual;
	int aux;
	auto start = std::chrono::system_clock::now(); // tempo atual (start)
	for (inicial = 1; inicial < QUANTIDADE_DE_NUMEROS_ALEATORIOS; inicial++) 
	{
		for (atual = inicial - 1; atual >= 0 && v[atual] > v[atual + 1]; atual--) 
		{
			aux = v[atual];
			v[atual] = v[atual + 1];
			v[atual + 1] = aux;
		}
	}
	auto end = std::chrono::system_clock::now(); // tempo atual (end)
	// cálculo do tempo decorrido 
	std::chrono::duration<double> elapsed_seconds = end - start; 
	// Gravação em arquivo
	std::fstream meuArquivo;
	meuArquivo.open("insercao.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
	else
	{
		std::cout << "Falha ao abrir o arquivo. Não localizado." << std::endl;
	}
}

void ordenaSelecao(std::vector<int> v) 
{
	int i;
	int valMenor, aux;
	int posMenor;
	int inicial;
	auto start = std::chrono::system_clock::now();
	for (inicial = 0; inicial < QUANTIDADE_DE_NUMEROS_ALEATORIOS - 1; inicial++) 
	{
		valMenor = v[inicial];
		posMenor = inicial;
		for (i = inicial + 1; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++) 
		{
			if (v[i] < valMenor) 
			{
				valMenor = v[i];
				posMenor = i;
			}
		}
		if (posMenor != inicial) 
		{
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
		i = 0;
		meuArquivo << "Tempo decorrido na ordenação: " << elapsed_seconds.count() << std::endl << std::endl;
		meuArquivo << "Vetor ordenado:" << std::endl << "[";
		for (auto j : v)
		{
			meuArquivo << j << ", ";
			i++;
			if (i == 20)
			{
				meuArquivo << std::endl;
				i = 0;
			}
		}
		meuArquivo << "]" << std::endl;
	}
	else
	{
		std::cout << "Falha ao abrir o arquivo. Não localizado." << std::endl;
	}
}

void ordenaBolha(std::vector<int> v) 
{
	int i, troca;
	int aux;
	auto start = std::chrono::system_clock::now();
	do 
	{
		troca = 0;
		for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS - 1; i++) 
		{
			if (v[i] > v[i + 1]) 
			{
				aux = v[i + 1];
				v[i + 1] = v[i];
				v[i] = aux;
				troca = 1;
			}
		}
	} 
	while (troca == 1);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::fstream meuArquivo;
	meuArquivo.open("bolha.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
	else
	{
		std::cout << "Falha ao abrir o arquivo. Não localizado." << std::endl;
	}
}
