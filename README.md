# PV Planning Tool

An educational and accessible photovoltaic (PV) planning and yield estimation tool developed in C.

This project was created to make solar energy planning more understandable, transparent, and inclusive for people around the world, regardless of technical background, country, or economic context.

Unlike many existing planning tools that focus primarily on Europe or the United States, this project includes solar irradiation references from multiple continents and supports multiple languages to encourage broader participation in the renewable energy transition.

---

# Why This Project Matters

The transition toward renewable energy is one of the most important engineering and societal challenges of our time.

Solar energy plays a critical role in:
- reducing greenhouse gas emissions
- increasing energy independence
- lowering long-term electricity costs
- improving energy access worldwide
- supporting more resilient and sustainable societies

Making solar planning tools more accessible helps democratize technical knowledge and empowers more people to participate in the energy transition, from students and homeowners to future engineers and communities around the world.

---

# Project Goals

This project aims to combine:
- educational clarity
- engineering realism
- accessibility
- inclusiveness
- beginner-friendly software design

The program was designed to:
- explain photovoltaic concepts progressively
- provide realistic engineering estimations
- remain understandable for beginners
- support multilingual interaction
- encourage exploration and learning

---

# Features

## Current Features

- Quick estimation mode
- Advanced engineering estimation mode
- Input validation and error handling
- Roof orientation and roof type factors
- Shading and system aging considerations
- Performance Ratio (PR) modeling
- Global solar irradiation reference values
- Location comparison
- Multilingual support:
  - English
  - Español
  - Deutsch
- Currency estimation support:
  - EUR
  - USD
  - CNY
- Beginner-friendly terminal interaction
- Modular and readable C code structure

---

# Repository Contents

This repository includes:

- Source code in C
- MIT License
- README documentation
- Windows executable version (`.exe`)
- Educational engineering calculations
- Multilingual terminal interface

---

# Technologies Used

- C
- GCC
- Git
- GitHub

---


# How to Compile

## Linux / WSL / macOS

gcc pv_yield_estimator.c -o pv_yield_estimator



# How to Run

./pv_yield_estimator



# Windows Executable

A precompiled Windows executable is included in the repository for users who do not want to compile the program manually.

PV_Yield_Estimator_v1.0.zip



# Example Workflow

## Quick Estimation Mode

The user can:

1. Select language
2. Select quick estimation mode
3. Enter approximate roof area
4. Select location or irradiation value
5. Enter electricity price
6. Enter Performance Ratio (PR)
7. Receive estimated yearly PV yield and savings

## Advanced Engineering Mode

Includes additional engineering variables such as:

- module dimensions
- roof orientation
- roof type
- shading level
- system quality
- location comparison
- currency flexibility



# Engineering Assumptions

This software uses simplified but realistic engineering assumptions for educational purposes.

The results are approximate estimations and should not replace professional photovoltaic system design or certified engineering studies.



# Inclusiveness and Global Perspective

A central principle of this project is accessibility.

The software includes:

- irradiation data from multiple world regions
- multilingual interaction
- beginner-friendly explanations
- realistic but understandable assumptions

The goal is to help make renewable energy knowledge more globally accessible and less regionally exclusive.



# License

This project is licensed under the MIT License.



# Author

Developed by Oscar Matallana

GitHub:
https://github.com/oscarmatallana

LinkedIn:
https://www.linkedin.com/in/matallana/

Questions, suggestions and contributions are welcome through GitHub Issues.
