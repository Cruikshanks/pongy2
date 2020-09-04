# Pongy II - The Smell of Garbage

> Do not use this as a current reference. This code is now almost 20 years old!

<img src="/screenshots/title_screen.jpg" alt="Screenshot of Pongy 2 title screen" />

<img src="/screenshots/game_screen.jpg" alt="Screenshot of Pongy 2 gameplay" />

This is an improvement over [Pongy](https://github.com/Cruikshanks/pongy), and built on my DirectX skills and C++ experience at the time. In this version, we have sound, a title screen, and Direct3D is used instead of DirectDraw. This means that everything you see is made up of primitives, which are then textured. The main reason for this was in order to use transparency, (I couldn't see how to implement transparency in surfaces at the time).

I also tried to improve the C++ code. Pongy II includes attempts at encapsulation, and makes use of inheritance, and polymorphism.

## Pre-requisites

- C++
- DirectX 8

## User Guide

> Taken from my notes at the time 😳

It is very simple to control. You are the bat on the left of the screen. Use the up and down arrows on the keyboard to control it. Press escape to quit a game, and again to quit the application.

Pongy II features Coefficient Response Algorithm Procedure (CRAP) AI, in order to challenge you, rather than simply implementing levels. This means if you are sh*t, the computer opponent will take pity on you and lower its response time. Think your slick, and it'll increase it reflexs and beat you down! How many points ahead of the computer can you get?

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).

> If you don't add a license it's neither free or open!
