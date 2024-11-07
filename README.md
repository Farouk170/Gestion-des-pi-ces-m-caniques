# Quality Control and Packaging System for 3D-Printed Mechanical Parts

This repository contains the design, code, and resources for a quality control and packaging system used in a 3D manufacturing environment. The system uses a PIC16F877 microcontroller to evaluate parts based on weight and shape criteria, then automates the packaging process.

## Project Overview

In this project, parts produced through 3D printing are subjected to quality checks before packaging. The system evaluates each part’s weight and shape, directing them into appropriate boxes. The microcontroller governs the quality control and packaging processes using various sensors, LEDs, and an LCD display.

### Quality Control Process

1. **Weight Check**: 
   - Parts are inspected to ensure they do not exceed 250g.
   - If weight is satisfactory, the LCD displays: `Qualité_P: satisfaisante`.
   - If weight is unsatisfactory, the LCD displays: `Qualité_P: Insatisfaisante`.

2. **Shape Check**: 
   - The shape sensors identify parts as either Shape A or Shape B.
   - For Shape A, the LCD displays: `Qualité_P&FA: Satisfaisante`, and a blue LED blinks three times.
   - For Shape B, the LCD displays: `Qualité_P&FB: Satisfaisante`, and a green LED blinks three times.

### Packaging Process

- **Part Counting and Packaging**:
  - Parts are grouped by shape for packaging. Boxes are filled with 20 parts of Shape A or 50 parts of Shape B.
  - A 7-segment display shows the current count for each box, resetting to zero when filled.

### Error Handling

- **Fault Detection**:
  - If a fault occurs in any part of the process, a buzzer sounds for 5 minutes, and the LCD displays `EN PANNE`.
  - The system logs faults in EEPROM, with the count displayed for 30 seconds when the `PBC` button is pressed.

## Components

- **Microcontroller**: PIC16F877 at 4 MHz
- **Sensors**:
  - Weight sensor (analog, connected to ADC module)
  - Two shape sensors (digital)
  - Two count sensors (one for each shape)
- **LEDs**:
  - Green: Indicates presence of Shape A
  - Blue: Indicates presence of Shape B
- **Buttons**:
  - `PBD`: Start process
  - `PBS`: Stop system
  - `PB2`: Reset part count
  - `PBC`: View fault count
- **Displays**:
  - 7-segment display for part count
  - LCD for status messages
- **Buzzer**: Alerts when faults are detected

## Project Structure

1. **Design**:
   - Identify inputs and outputs
   - Define interrupt sources and flowcharts for system operation

2. **Simulation**:
   - Assemble circuit in Proteus ISIS
   - Verify connections and component placements

3. **Code**:
   - Write C code for all functionalities in MikroC for PIC
   - Integrate all features to meet project requirements

## Getting Started

### Prerequisites

- **Software**:
  - MikroC for PIC (for code development)
  - Proteus ISIS (for circuit simulation)

### Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/Farouk170/Gestion-des-pi-ces-m-caniques
