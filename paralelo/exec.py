import os
import random


def exec_program(v):

    os.system("mpirun -n 8 ./proyectocompilado")


def generate_array(length):
    aux = []
    for _ in range(length):
        aux.append(random.randint(0, length))

    return aux


def main():
    lengths = [10, 100]
    for l in lengths:
        print("Generating array of length: %s" % l)
        array = generate_array(l)
        exec_program(array)

    return


if __name__ == "__main__":
    main()
