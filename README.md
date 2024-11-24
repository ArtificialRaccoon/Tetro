# Tetro, a Tetris Clone for MS-DOS

![Untitled](https://github.com/ArtificialRaccoon/Tetris/blob/main/Screenshot.png)

A very simple tetris clone for DOS using Allegro, and DJGPP/GCC.  Fully playable,
and supports both 7-Bag and Tetris Grand Master randomization.  Still has some
spitpolish to do, such as a proper top score screen, but it is effectively done.

Tetro has been built with Allegro 4.3.2.1, using GCC/DJGPP. Tetro requires an 
IBM compatible 386 or better with 4 megs of RAM, a VGA graphics card, a math 
co-processor, and a hard disk drive. A Sound Blaster 16 or 100% compatible 
sound cardis recommended.

Tetro has been tested on an AMD 386DX40, though it should run on lower clocked 
machines without issue.  

Tooling:
- DJGPP (targetting GCC 12.1.0)
- Allegro 4.2.3.1 (Unoffical, see below)

## Environment Setup

Install VSCode, and the [DOS-Dev](https://marketplace.visualstudio.com/items?itemName=badlogicgames.dos-dev) extension.  Clang / intellisense will complain about missing headers, etc.  Disable that if it bothers you.

## 3rd Party Libraries

- [Allegro 4.2.3.1](https://github.com/ArtificialRaccoon/allegro-4.2-xc) - Additionally, some minor changes were made to the bundled Allegro headers so they would compile under C++17.
- [Simpleson](https://github.com/gregjesl/simpleson)
