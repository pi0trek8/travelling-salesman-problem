import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import csv

plt.style.use('seaborn-v0_8-whitegrid')


def plot(file: str, directory=''):
    file_path = (file if directory == '' else f'{directory}/{file}')

    df = pd.read_csv(file_path, header=None, names=['num_elements', 'time'], delimiter=',')
    label = file.replace('_', ' ')
    # label = f'{labels[0]} algorithm, {labels[1]} graph implementation, density: {labels[2].removesuffix(".csv")}'
    plt.plot(df['num_elements'], df['time'], marker='.', markersize=7, markerfacecolor='#000000',
             markeredgecolor='#000000', label=f'{label.split(".")[0]}')
    plt.title(f'Time vs Number of cities for {label.split(".")[0]}')
    plt.legend()
    plt.xlabel('Number of elements [n]')
    plt.ylabel('Time (seconds)')
    fig = plt.gcf()
    # plt.show()
    if not os.path.exists('img'):
        os.mkdir('img')
    fig.savefig(f'img/{file.removesuffix(".csv")}.png', bbox_inches='tight')


def plot_multiline(file: str):
    data = pd.read_csv(file, sep=',')
    fileHeader = data.columns[0]
    columns = data.columns[1:]
    plt.figure(figsize=(15, 8))

    for column in columns:
        plt.plot(data[fileHeader], data[column], label=column, marker='.', markersize=7)

    plt.title('Time taken vs files - tsp')
    plt.legend()
    plt.xlabel('Files with number of cities [n]')
    plt.ylabel('Time (seconds)')

    # Set a subset of ticks for better readability
    plt.xticks(rotation='vertical')

    plt.yscale('log')
    fig = plt.gcf()

    if not os.path.exists('img'):
        os.mkdir('img')

    fig.savefig(f'img/{file.removesuffix(".csv")}.png', bbox_inches='tight')



def get_csv_files(directory=''):
    return [f for f in os.listdir() if f.endswith('.csv')]


# plot_multiline(R"files.csv")
#
# for i in range(6, 42):
#     print(f'"{i}",')
