import os
import subprocess
import sys
import plot
import csv
import time
import threading


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
            average_time: float = 0.0
            for i in range(0, 10):
                command = [executable_path, alg, city]
                result = subprocess.run(command, capture_output=True, text=True)
                average_time += float(result.stdout)
                print(result)
            output.append(str(average_time/10.0))

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


def run_algorithm(executable_path, alg, city, output, lock, stop_flag):
    command = [executable_path, alg, city]
    result = subprocess.run(command, capture_output=True, text=True)
    print(result)

    with lock:
        if result.stdout != '':
            output[0] += float(result.stdout)
            stop_flag.set()
        else:
            output[0] += 300
            output[1] += 1
    

def bb_collect_data():
    for alg in algorithms:
        file_name = alg.replace(' ', '_')
        create_file(file_name)
        output_time = []
        output_percentage = []
        lock = threading.Lock()

        def worker(city, output):
            nonlocal lock
            stop_flag = threading.Event()
            t = threading.Thread(target=run_algorithm, args=(executable_path, alg, city, output, lock, stop_flag,))
            t.start()
            total_time = 0
            total_sleep_time = 60 * 4

            while total_time < total_sleep_time and not stop_flag.is_set():
                time.sleep(0.001)
                total_time += 0.0015

            if not stop_flag.is_set():
                os.system("taskkill /f /im travelling-salesman-problem.exe") 
                print("Process killed due to timeout.")

        for city in cities:
            output = [0.00000, 0]
            for i in range(0, 10):
                worker(city, output=output)

            output_time.append(output[0] / 10.00000)  
            output_percentage.append((output[1] / 10) * 100)  

        add_column_to_csv(f'{file_name}.csv', alg, output_time)
        add_column_to_csv(f'{file_name}.csv', alg, output_percentage)


executable_path = (
    R"../testing-module/travelling-salesman-problem.exe")

cities = [
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
    "13",
    "14",
    "15",
    "16",
    "17",
    "18",
    "19",
    "20",
    "21",
    "22",
    "23",
    "24",
    "25",
    "26",
    "27",
    "28",
    "29",
    "30",
    "31",
    "32",
    "33",
    "34",
    "35",
    "36",
    "37",
    "38",
    "39",
    "40",
    "41",
]

files = [
    "tsp_6_1.txt",
]

algorithms = ['DFS Branch and Bound', 'LC Branch and Bound']


if __name__ == '__main__':
    bb_collect_data()
