import os
import shutil
import sys

def generate_file(filename, n, saturation=30):
    with open(filename, 'w') as file:
        file.write(f"{n}\n{saturation}\n")

def generate_file_non_hamilton(filename, n, saturation=50):
    with open(filename, 'w') as file:
        file.write(f"{n}\n{saturation}\n")


if __name__ == "__main__":

    # if len(sys.argv) != 3:
    #     print("Usage: python generate.py <start_exponent> <end_exponent>")
    #     sys.exit(1)
    # try:
    #     start_exponent = int(sys.argv[1])
    #     end_exponent = int(sys.argv[2])
    # except ValueError as e:
    #     print(f"Error: {e}")
    #     print("Usage: python generate.py <start_exponent> <end_exponent>")
    #     sys.exit(1)

    # Directory where files will be saved
    directory = 'benchmark'

    # Clear the contents of the benchmark directory
    if os.path.exists(directory):
        shutil.rmtree(directory)
    os.makedirs(directory)

    max_n_length_h = 13
    max_n_length = 30  # Determine the length of the largest n
    for i in range(1, max_n_length_h+1):
        n = 2**i
        filename = os.path.join(directory, f"h_generate.{n:0{max_n_length_h}}")
        generate_file(filename, n)

    for i in range(10, 15 + 1):
        n = i
        filename = os.path.join(directory, f"n-h_generate.{n:0{max_n_length}}")
        generate_file_non_hamilton(filename, n)