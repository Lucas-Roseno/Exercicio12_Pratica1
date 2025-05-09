#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <chrono>

int main() {
    int N;
    std::cout << "Digite o número de processos (N): ";
    std::cin >> N;

    std::vector<double> resultados;

    auto t0 = std::chrono::high_resolution_clock::now();

    for (int k = 1; k <= N; ++k) {
        std::ifstream proc("datasets/P" + std::to_string(k) + ".txt");
        if (!proc.is_open()) {
            std::cerr << "Erro ao abrir P" << k << ".txt\n";
            return 1;
        }

        std::string linha;
        double resultadoAnterior = 0.0;
        double resultadoFinal = 0.0;

        while (std::getline(proc, linha)) {
            linha.erase(std::remove(linha.begin(), linha.end(), '<'), linha.end());
            linha.erase(std::remove(linha.begin(), linha.end(), '>'), linha.end());

            std::stringstream ss(linha);
            std::string token;
            std::vector<std::string> ids;
            while (std::getline(ss, token, ',')) {
                token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c){ return std::isspace(c); }), token.end());
                if (!token.empty()) ids.push_back(token);
            }

            double soma = 0.0;
            for (auto &id : ids) {
                std::ifstream f("datasets/" + id + ".txt");
                double valor;
                while (f >> valor) {
                    soma += std::sqrt(valor);
                }
                f.close();
            }

            resultadoFinal = soma - resultadoAnterior;
            resultadoAnterior = soma;
        }

        resultados.push_back(resultadoFinal);
        proc.close();
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dur = t1 - t0;

    std::ofstream saida("datasets/output.txt");
    for (double r : resultados) saida << r << std::endl;
    saida.close();

    std::cout << "Tempo de execução (Algoritimo base): " << dur.count() << " segundos\n";
    return 0;
}