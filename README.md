# Zhang_CSCI2270_FinalProject
Micah Zhang CSCI2270 Data Structures Final Project

PHASE 1
Imagine you are a rich trillionaire 50 years in the future. You have a fleet of rockets with a wide range of prices and performance. 
You are planning to travel to Jupiter, and you'd perfer to enjoy the comfort and privacy of using your own private rocket. However,
being a trillionaire, you are stingy, and want to use as little money as possible for the trip.
You understand that the greater the range of the rocket, the greater its operating expenses. 

Thus, you want to choose the "right rocket for the job", by optimizing the price of the rocket versus the distance you need to travel.

This is where my program comes in.

A weighted graph represents the solar system, with a user set *home planet* and *destination planet*.
Two factors contribute to the weight, which represnts the amount of fuel needed, of each path: its physical distance and level of risk.
For example, a shorter path might involve navigating through an asteroid field, requiring more fuel and resulting in a relatively high weight.

A binary search tree represents the user's inventory of rockets.
Each node in the tree contains both the name of the rocket and the maxmimum distance it can travel on a full tank of fuel. 

Dijkstra's algorithm will be used to find the optimum path from the home planet to the destination planet.
It will return a number corresponding to the minimum amount of fuel needed to complete the trip.

Then, using the rocket inventory, the program will find the rocket that has a fuel capacity closest to the minimum.

It will then return both the name of the rocket and a visual representation of optimal path for the trip. 

PHASE 2

Project Summary:
*TBD*

How to Run:
*TBD*

Dependencies:
*TBD*

System Requirements:
This repository can be run using any operating system, include Windows, MacOS, and Linux provided the user has the ability to compile and run programs written in c++.

My Name:
Micah Zhang

Open issues/bugs:
*TBD*
