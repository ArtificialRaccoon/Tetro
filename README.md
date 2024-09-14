# Tetris

![Untitled](https://github.com/ArtificialRaccoon/Tetris/blob/main/Screenshot.png)

A very simply tetris clone for DOS using Allegro, GCC, and JGMod.  Currently only slapped the UI and basic state system togeather; will get to the rest later.

Currently runs on hardware and DOSBOX without issue (for now).  

Tooling:
- DJGPP (targetting GCC 12.1.0)
- Allegro 4.2.3.1 (Unoffical, see below)
- JGMOD (Unoffical, see below)

## Environment Setup

Install VSCode, and the [DOS-Dev](https://marketplace.visualstudio.com/items?itemName=badlogicgames.dos-dev) extension.  Clang / intellisense will complain about missing headers, etc.  Disable that if it bothers you.

## 3rd Party Libraries

- [Allegro 4.2.3.1](https://github.com/ArtificialRaccoon/allegro-4.2-xc) - Additionally, some minor changes were made to the bundled Allegro headers so they would compile under C++17.
- [Simpleson](https://github.com/gregjesl/simpleson)
- [JGMOD](https://github.com/ArtificialRaccoon/JGMOD)
