#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

const int framesBeforeDrop[20] = { 48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 5, 5, 4, 4, 4, 3, 3, 2, 1 };
const int blockSize = 8;
const int playGridWidth = 10;
const int playGridHeight = 20;
const int tilesetWidth = 16;
const int tilesetHeight = 8;
const int tileWidth = 8;
const int tileHeight = 8;
const int tileStartXpos = 72;
const int tileStartYpos = 56;
const int backgroundWidth = 40;
const int backgroundHeight = 25;
const int dialogWidth = 14;
const int dialogHeight = 4;
const int menuXStart = 140;
const int menuYStart = 100;
const int menuYRandom = 112;
const int menuYExit = 124;
const unsigned FLIPPED_HORIZONTALLY_FLAG  = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG    = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG    = 0x20000000;

#endif // GAMECONSTANTS_H