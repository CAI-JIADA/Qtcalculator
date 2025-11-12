# Qt Calculator (計算機)

A basic calculator application built with Qt5 featuring:

![Calculator Screenshot](screenshot.png)

## Features
- **Process Display**: Shows the calculation expression as you type (e.g., "5 + 3 =")
- **Display Screen**: Large display with right-aligned text showing the result
- **Number Buttons**: 0-9 digits and decimal point
- **Basic Operations**:
  - Addition (+)
  - Subtraction (-)
  - Multiplication (×)
  - Division (÷)
- **Function Buttons**:
  - Equals (=) - Calculate result
  - Clear (C) - Reset calculator
  - Delete (⌫) - Remove last digit
- **Error Handling**: Division by zero protection

## Requirements
- Qt5 (qt5-qmake, qtbase5-dev)
- C++ compiler (g++)
- make

## Building

### Install Dependencies (Ubuntu/Debian)
```bash
sudo apt-get install qt5-qmake qtbase5-dev build-essential
```

### Build the Calculator
```bash
qmake calculator.pro
make
```

## Running
```bash
./calculator
```

## Layout
The calculator features a 4×4 button grid with two display screens on top:
```
┌─────────────────────────┐
│   Process (5 + 3 =)     │  ← Shows calculation expression
├─────────────────────────┤
│      Display (8)        │  ← Shows current number/result
├─────┬─────┬─────┬─────┤
│  C  │  C  │  ⌫  │  ÷  │
├─────┼─────┼─────┼─────┤
│  7  │  8  │  9  │  ×  │
├─────┼─────┼─────┼─────┤
│  4  │  5  │  6  │  -  │
├─────┼─────┼─────┼─────┤
│  1  │  2  │  3  │  +  │
├─────┼─────┼─────┼─────┤
│   0     │  .  │  =  │
└─────────┴─────┴─────┘
```

## Usage
1. Click number buttons to enter digits
2. Click an operation button (+, -, ×, ÷) - the process display will show your first number and the operation
3. Enter the second number - the process display will show the complete expression (e.g., "5 + 3")
4. Click equals (=) to see the result - the process display will show "5 + 3 =" and the main display will show "8"
5. Use Clear (C) to reset or Delete (⌫) to remove the last digit

## License
Open source project