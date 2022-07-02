/*
UDESC - Universidade do Estado de Santa Catarina
Estrutura de Dados II

Na expectativa de se anallisar o tempo de execução de três Threads, uma thread para cada método de ordenação utilizei algumas ferramentas
fornecidas pela biblioteca <chrono>, <cstdlib>, <fstream>, <iostream>, <thread> e <vector>. Todas elas se complementam e permitem
que eu determine a velocidade que determinada função de ordenação alocada em thread executa por completo.

Gerar os resultados em arquivos de texto são em geral mais rápidos que escritas em tela.


Marcelo Henrique de Sousa Pinheiro
*/

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#define QUANTIDADE_DE_NUMEROS_ALEATORIOS 10000

void ordenaSelecao(std::vector<int> v);
void ordenaInsercao(std::vector<int> v);
void ordenaBolha(std::vector<int> v);

int main()
{
	int i;
	std::vector<int> listaAleatoria;
	// Criação de um vetor com a quantidade QUANTIDADE_DE_NUMEROS_ALEATORIOS definida na linha 21
	// 10000 valores aleatórios geram uma carga de trabalho possível de avaliar o tempo de execução
	for (i = 0; i < QUANTIDADE_DE_NUMEROS_ALEATORIOS; i++)
	{
		int valor = rand() % 10000 + 1;
		listaAleatoria.push_back(valor);
	}

	std::thread t_insercao(ordenaInsercao, listaAleatoria);
	std::thread t_selecao(ordenaSelecao, listaAleatoria);
	std::thread t_bolha(ordenaBolha, listaAleatoria);
	t_insercao.join();
	t_selecao.join();
	t_bolha.join();
	return 0;
}

/*
Funções
*/

void ordenaInsercao(std::vector<int> v) {
	int inicial, atual;
	int aux;
	auto start = std::chrono::system_clock::now(); // uma instância de auto definida como 'start' captura o tempo atual
	for (inicial = 1; inicial < QUANTIDADE_DE_NUMEROS_ALEATORIOS; inicial++) 
	{
		for (atual = inicial - 1; atual >= 0 && v[atual] > v[atual + 1]; atual--) 
		{
			aux = v[atual];
			v[atual] = v[atual + 1];
			v[atual + 1] = aux;
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	// Gravação em arquivo
	std::fstream meuArquivo;
	meuArquivo.open("insercao.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
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
	// calcula o tempo decorrido na execução
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	// Gravação em arquivo
	std::fstream meuArquivo;
	meuArquivo.open("selecao.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
}

void ordenaBolha(std::vector<int> v) {
	int i, troca;
	int aux;
	auto start = std::chrono::system_clock::now();
	do {
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
	// Gravação em arquivo
	std::fstream meuArquivo;
	meuArquivo.open("bolha.txt", std::ios::out);
	if (meuArquivo.is_open())
	{
		meuArquivo << elapsed_seconds.count() << std::endl;
	}
}
