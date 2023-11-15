import os
import subprocess
import sys
import plot
import csv
import time


def create_file(output_file):
    file = f"{output_file}.csv"
    if os.path.exists(file):
        os.remove(file)
    f = open(f"{output_file}.csv", 'a+')
    for file in files:
        f.write(f'{file}\n')


def add_column_to_csv(csv_file, new_column_name, new_column_data):
    rows = []
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        rows = list(reader)
        # Add the new column header to the first row
        print(rows)

    for i in range(0, len(rows)):
        # Add the new column data to the remaining rows
        rows[i].append(new_column_data[i - 1])

    with open(csv_file, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(rows)


def collect_data_single_algorithm():
    for alg in algorithms:
        file_name = alg.replace(' ', '_')
        create_file(file_name)
        output = []
        for city in cities:
            command = [executable_path, alg, city]
            result = subprocess.run(command, capture_output=True, text=True)
            output.append(result.stdout)
            print(result)
        add_column_to_csv(f'{file_name}.csv', alg, output)
        plot.plot(f"{file_name}.csv")


def collect_data_from_files():
    for alg in algorithms:
        file_name = alg.replace(' ', '_')
        create_file(file_name)
        output = []
        for file in files:
            if int(file.split('.')[0].split('_')[1]) > 14 and alg == 'Brute Force':
                continue
            command = [executable_path, alg, f"C:\\Users\\Admin\\Desktop\\travelling-salesman-problem\\data\\{file}"]
            result = subprocess.run(command, capture_output=True, text=True)
            output.append(result.stdout)
            print(result)
        add_column_to_csv(f'{file_name}.csv', alg, output)
        plot.plot(f"{file_name}.csv")


executable_path = (
    R"C:\Users\Admin\Desktop\travelling-salesman-problem\cmake-build-release\travelling-salesman-problem.exe")

cities = [
    "32",
    "33",
    "34",
    "35",
]

files = [
    "tsp_6_1.txt",
    "tsp_6_2.txt",
    "tsp_10.txt",
    "tsp_12.txt",
    "tsp_13.txt",
    "tsp_14.txt",
    "tsp_15.txt",
    "tsp_17_1.txt",
    "tsp_18_1.txt",
    "tsp_19_1.txt",
    "tsp_20_1.txt"
]

algorithms = ['LC Branch and Bound', 'DFS Branch and Bound', 'Dynamic Programming', 'Brute Force']
if __name__ == '__main__':
    collect_data_from_files()
