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
    for city in cities:
        f.write(f'{city}\n')


def add_column_to_csv(csv_file, new_column_name, new_column_data):
    rows = []
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        rows = list(reader)
        # Add the new column header to the first row
        print(rows)

    for i in range(1, len(rows)):
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


executable_path = (R"C:\Users\Zosia\Desktop\travelling-salesman-problem\cmake-build-release\travelling-salesman"
                   R"-problem.exe")


cities = [
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13"
]

algorithms = ['Brute Force']

if __name__ == '__main__':
    collect_data_single_algorithm()
