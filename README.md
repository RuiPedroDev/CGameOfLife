# Game of Life in C

This C program simulates Conway's Game of Life by mathematician John Conway. The Game of Life operates on a grid of cells, where each cell can be either alive or dead. The state of each cell evolves over time based on specific rules.
The code is designed to be cross-platform, supporting both Windows and Unix-like systems.

## Installation and Compilation

Firstly clone the repository to your local machine:

```bash
git clone https://github.com/RuiPedroDev/CGameOfLife
```

To compile the program, use a C compiler such as `gcc`. Open a terminal and navigate to the directory containing the source code file. Then, run the following command:

```bash
gcc GameOfLife.c -o GameOfLife
```

## Usage

To run the program, execute the compiled executable with the desired pattern and, optionally, a sleep time for visualization. Here's the general syntax:

```bash
./GameOfLife <pattern> <sleepTime>
```

- `<pattern>`: Select a pattern for the initial configuration.
  - 0: BLINKER
  - 1: TOAD
  - 2: BEACON
  - 3: PULSAR
  - 4: PENTADECATHLON
  - 5: GLIDER
  - 6: GOSPER GLIDER GUN
  - 7: LWSS
  - 8: RANDOM

- `<sleepTime>` (optional): Specify the sleep time between iterations in milliseconds (0 to 10000). Default is 0.

## Examples

```bash
./GameOfLife 5 100   # Run with GLIDER pattern with 100ms of sleep time between each iteration
./GameOfLife 8       # Run with RANDOM pattern with the default sleep time
```

## Notes

- The program will display the evolving state of the Game of Life grid, updating for a predefined number of iterations (NITERS) or until the grid stabilizes.

- Press Ctrl+C to terminate the simulation at any time.
