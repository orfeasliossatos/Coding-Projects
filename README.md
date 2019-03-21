# Coding-Projects
A collection of projects, graphical or otherwise.

This project uses SFML 2.5.1

To run any of the programs, create a main.cpp file, include "program.h" and write Program.run(window);

example for Visual Studio 2017 to run LorenzAttractor:

main.cpp

#include "stdafx.h"
#include "LorenzAttractor.h"
#include <SFML/Graphics.hpp>

int main()
{
  /// Create a window
  
  bool isFullscreen = true;
  sf::RenderWindow window;
	window.create(sf::VideoMode(1980, 1080), "Coding Projects", (isFullscreen ? sf::Style::Fullscreen : sf::Style::Default), sf::ContextSettings());
	window.setPosition(sf::Vector2i(0, 0));
  window.setVerticalSyncEnabled(true); 
	window.setFramerateLimit(60);
  
  
  /// Important part is here
  
  LorenzAttractor.run(window);
}
