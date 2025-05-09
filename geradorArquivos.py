import os
import random

# Criar pasta datasets se não existir
datasets_dir = "datasets"
os.makedirs(datasets_dir, exist_ok=True)

N = 5  # Número de processos e arquivos de dados

# Gerar arquivos de dados: 01.txt até 05.txt
for i in range(1, N + 1):
    filename = os.path.join(datasets_dir, f"{i:02d}.txt")
    with open(filename, "w") as f:
        for _ in range(100000):
            valor = random.uniform(1, 1_000_000)
            f.write(f"{valor}\n")

# Gerar arquivos de processo: P1.txt até P5.txt
for k in range(1, N + 1):
    filename = os.path.join(datasets_dir, f"P{k}.txt")
    with open(filename, "w") as f:
        num_linhas = random.randint(5, 10)  # 5 a 10 linhas por processo
        for _ in range(num_linhas):
            qtd_ids = random.randint(1, N)
            ids = random.sample(range(1, N + 1), qtd_ids)
            ids_str = ", ".join(f"{i:02d}" for i in ids)
            f.write(f"< {ids_str} >\n")
