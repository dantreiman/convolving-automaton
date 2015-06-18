# ConvolvingAutomaton

![screenshot](https://raw.githubusercontent.com/dantreiman/convolving-automaton/master/screenshots/fullscreen_1.png)

## About
This project is a fast GPU implementation of "[Generalization of Conway's "Game of Life" to a continuous domain, Rafler 2011](http://arxiv.org/abs/1111.1567)".

It is the fastest implementation of SmoothLife to date thanks to the parallel FFT shader inspired by [GPU FFT, J.R. Frisvad 2009](http://www2.compute.dtu.dk/pubdb/views/publication_details.php?id=5771). We can compute two convolutions in parallel by packing two complex meshes into a single GL texture.

## Motivation

The end goal of this project is to automate the search for cellular automata with certain properties.
(i.e. symmetries, property conservation, gliders, self-replication...)

Project Outline:
* Provide a fast, GPU-accelerated implementation of the SmoothLife algorithm in 2D.
* Generalize the algorithm to support any number of dimensions and neighborhood kernels.
* Support for arbitrary update functions.
* Output results to a classification framework, for automated searching of the parameter space.

## Quickstart

#### Requirements
* Mac OSX with developer tools installed

In Terminal:
    make
    ./convolving_automaton

If it doesn't compile, you may have to rebuild glfw for your system.
