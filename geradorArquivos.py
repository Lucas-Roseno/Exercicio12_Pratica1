import os
import random

datasets_dir = "datasets"
os.makedirs(datasets_dir, exist_ok=True)

N = 5  

for i in range(1, N + 1):
    filename = os.path.join(datasets_dir, f"{i:02d}.txt")
    with open(filename, "w") as f:
        for _ in range(100000):
            valor = random.uniform(1, 1_000_000)
            f.write(f"{valor}\n")


for k in range(1, N + 1):
    filename = os.path.join(datasets_dir, f"P{k}.txt")
    with open(filename, "w") as f:
        num_linhas = random.randint(5, 10)  
        for _ in range(num_linhas):
            qtd_ids = random.randint(1, N)
            ids = random.sample(range(1, N + 1), qtd_ids)
            ids_str = ", ".join(f"{i:02d}" for i in ids)
            f.write(f"< {ids_str} >\n")
