import os
import random


def exec_program_paralel(comm_size, array_length):

    args = tuple([comm_size, array_length])
    command = "mpirun -n %d ./compiladoparalelo %d" % args
    print(command)
    os.system(command)


def exec_program_sec(array_length):

    command = "mpirun -n 1 ./compiladosecuencial %d" % array_length
    print(command)
    os.system(command)


def generate_array(length):
    aux = []
    for _ in range(length):
        aux.append(random.randint(0, length))

    return aux


def main():
    lengths = [1000, 10000]
    comm_sizes = [1, 2, 4, 8]
    for c in comm_sizes:
        for l in lengths:
            print("-----------------------------------------\n")
            args = tuple([l, c])
            exec_program_paralel(c, l)

    for l in lengths:
        exec_program_sec(l)
    return


if __name__ == "__main__":
    main()
