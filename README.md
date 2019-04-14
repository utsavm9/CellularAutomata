# Cellular Automata Simulator

## Project Description

I developed this program to understand how animation and graphic-like abilities were achieved in the era of command-line interfaces. The program simulates the two most popular cellular automata: [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) and [Wolfram's Elementary Cellular Automata](http://mathworld.wolfram.com/ElementaryCellularAutomaton.html).

The screenshot below of the program running on Turbo C++ IDE is showing a generation from Conway's Game of Life. This particular pattern is known as the Gosper's Glider Gun as it creates patterns akin to a shooting gun.

![Screenshot of Conway's Game of Life as running on this program](https://raw.githubusercontent.com/utsavm9/CellularAutomata/master/Conway.png)

This program can also simulate Wolfram's Elementary Cellular Automaton. The screenshot below depicts the pattern from Rule 18 which generates an increasingly-bigger Sierpinski's Triangle.

![Screenshot of Wolfram's Elementary Cellular Automaton as running on this program](https://github.com/utsavm9/CellularAutomata/raw/master/Wolfram.png)

## Getting started 
This program is designed to run on TurboC++ compiler and has been tested to run successfully on compiler version 3.2. Download the Turbo C++ compiler from [its website.](https://developerinsider.co/download-turbo-c-for-windows-7-8-8-1-and-windows-10-32-64-bit-full-screen/)

Then, move the file `AUTOMATA.CPP` inside the `bin` folder located in the Turbo C++ directory, which is by default in `C:` for Windows users. The program can then be opened and run inside the Turbo C++ IDE.

## Implementation
The algorithm implemented to achieve animation re-prints the entire screen for each generation. Some of the challenges we overcome in this project are:

* Turning rectangle MS-DOX "grids" into a square grid.
* Matrix operations
* Window-like user interface in a command-line environment
