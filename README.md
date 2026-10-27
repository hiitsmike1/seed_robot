# Autonomous Seed-Planting Robot Firmware

Arduino Mega firmware for an autonomous over-terrain vehicle (OTV) developed for the ENES100 engineering design project at the University of Maryland.

## Overview

The firmware controls the robot's drivetrain, uses ultrasonic sensors to detect obstacles and measure distances, and uses localization data to help guide the robot. It also controls servo-driven mechanisms for seed planting and sample collection.

## Features

- **Motor control:** Forward, reverse, turning, spinning, and stopping.
- **Distance sensing:** Ultrasonic sensors measure distances to nearby objects.
- **Navigation:** Uses ENES100 position and heading data to adjust the robot's orientation and movement.
- **Plot prediction:** Requests a machine-learning prediction through the ENES100 library made by my teammates to determine the target plot.
- **Servo control:** Operates mechanisms for planting and sample collection.

## Hardware

- Arduino Mega
- Motor drivers and four drive motors
- Two ultrasonic distance sensors
- Two servo motors
- ENES100 localization and communication system

## Software Requirements

- Arduino IDE
- Arduino Mega board support
- `Servo` library
- `Enes100` library

## Setup

1. Clone or download this repository.
2. Open the `.ino` sketch in the Arduino IDE.
3. Install the required libraries.
4. Connect the hardware according to the pin assignments in the source code.
5. Select **Arduino Mega 2560** as the target board.
6. Upload the sketch to the board.

**Note:** The firmware depends on the ENES100 system being available for localization and machine-learning predictions.

## Project Context

This firmware was developed as part of a team engineering project to build an autonomous vehicle capable of navigating a course and performing seed-planting and sample-collection tasks.

See the [project website](https://hiitsmike1.github.io/michaelcrandall.github.io/) for additional project information, photos, and documentation.
