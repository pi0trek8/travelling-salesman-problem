import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import csv

plt.style.use('seaborn-v0_8-whitegrid')
# from IPython.display import set_matplotlib_formats
# set_matplotlib_formats('retina', quality=100)


def plot(file: str, directory=''):
    file_path = (file if directory == '' else f'{directory}/{file}')

    df = pd.read_csv(file_path, header=None, names=['num_elements', 'time'], delimiter=',')
    label = file.replace('_', ' ')
    bars1 = ax.bar(df['num_elements'], y_values_bar1, width=0.4, color='#3d85c6', alpha=0.7, label='Bar 1 (Percentage)')


    # label = f'{labels[0]} algorithm, {labels[1]} graph implementation, density: {labels[2].removesuffix(".csv")}'
    plt.plot(df['num_elements'], df['time'], marker='.', markersize=7, markerfacecolor='#000000',
             markeredgecolor='#000000', label=f'{label.split(".")[0]}')
    plt.title(f'Time vs Number of cities for {label.split(".")[0]}')
    plt.legend()
    plt.xticks([6, 8, 10, 12, 14, 16, 18, 20, 22, 24])
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
    plt.figure(figsize=(12, 6))

    for column in columns:
        plt.plot(data[fileHeader], data[column], label=column, marker='.', markersize=7)

    plt.title('Time vs number of cities')
    plt.legend()
    plt.xlabel('Number of cities [n]')
    plt.ylabel('Time (seconds)')

    # Set a subset of ticks for better readability
    # plt.xticks(rotation='vertical')
    plt.xticks([5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27])

    # plt.yscale('log')
    fig = plt.gcf()
    plt.show()

    if not os.path.exists('img'):
        os.mkdir('img')

    fig.savefig(f'img/{file.removesuffix(".csv")}.png', bbox_inches='tight')



def get_csv_files(directory=''):
    return [f for f in os.listdir() if f.endswith('.csv')]


def plot_bars_and_lines_from_csv(csv_file_path):
    # Load data from the CSV file
    df = pd.read_csv(csv_file_path, header=None, names=['cities', 'time_DFS', 'time_LC', 'bar_DFS', 'bar_LC'], delimiter=',')

    # Extract data columns
    x_values = df['cities']
    y_values_bar1 = df['bar_DFS']
    y_values_bar2 = df['bar_LC']
    y_values_line1 = df['time_DFS']
    y_values_line2 = df['time_LC']

    # Create a figure and axis
    fig, ax = plt.subplots(figsize=(10, 7))

    # Plot the bar graphs
    bars1 = ax.bar(x_values, y_values_bar2, width=0.8, color='gray', alpha=0.45, label='Process terminations out of 20')
    # # bars2 = ax.bar(x_values + 0.2, y_values_bar2, width=0.4, color='grey', alpha=0.9,label='Bar 2 (Percentage)')
    #
    for bar, value in zip(bars1, y_values_bar2):
        if value > 0:
            ax.text(bar.get_x() + bar.get_width() / 2, bar.get_height(), f'{value}%', ha='center', va='bottom')
    # for bar, value in zip(bars2, y_values_bar2):
    #     if value > 0:
    #         ax.text(bar.get_x() + bar.get_width() / 2, bar.get_height(), f'{value}%', ha='center', va='bottom')

    # Plot the line plots on the same graph
    # ax.plot(x_values, y_values_line1, marker='.', color='#3d85c6', markersize=7, label='DFS Branch and Bound', markerfacecolor='#000000', markeredgecolor='#000000')
    ax.plot(x_values, y_values_line2, marker='.', color='gray', markersize=7, label='LC Branch and Bound', markerfacecolor='#000000', markeredgecolor='#000000')


    # Set labels and title
    ax.set_xlabel('Number of cities [n]')
    ax.set_ylabel('Time [s]')
    ax.set_title('Time vs number of cities - branch and bound algorithm')
    ax.legend()
    fig.tight_layout()
    # plt.yscale('log')
    # Show the plot
    plt.show()
    fig.savefig(f'img/tsp_all.png', bbox_inches='tight')








plot_multiline(R"tsp_algorithms.csv")
#
# for i in range(6, 42):
#     print(f'"{i}",')
