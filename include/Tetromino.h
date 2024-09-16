#ifndef TETROMINOSTATE_H
#define TETROMINOSTATE_H

#include "allegro.h"
#include "GameConstants.h"

class Tetromino 
{
    public: //Functions
        Tetromino() {};
        Tetromino(int type);
        void Draw(BITMAP* BUFFER, BITMAP* tileset, bool preview = false);
        void LockPiece(int** playGrid);

    public: //Movement Handlers
        void Left(int** playGrid) 
        {
            if(CanMove(playGrid, x - 1, y)) 
                x--; 
        }

        void Right(int** playGrid)
        {
            if(CanMove(playGrid, x + 1, y)) 
                x++; 
        }

        void Down(int** playGrid)
        {
            if (CanMove(playGrid, x, y + 1))
                y++;
        }

        void HardDrop(int** playGrid)
        {
            while (CanMove(playGrid, x, y + 1)) { y++; }
        }

        void Rotate(int** playGrid)
        {
            if(CanRotate(playGrid, (rotation + 1) % 4))
                rotation = (rotation + 1) % 4; 
        }
        
        bool ShouldLock(int** playGrid)
        {
            return !CanMove(playGrid, x, y + 1);
        } 

    public: //Getters
        int GetType() { return this->Type; }

    private:
        void DrawBlock(BITMAP* BUFFER, BITMAP* TILESET, int x, int y);
        bool CanMove(int** playGrid, int x, int y);
        bool CanRotate(int** playGrid, int nextRotation);

    private:
        int shape[4];
        int x;
        int y;
        int rotation;
        int Type;
        int tetrominoes[7][4] = 
        {
            {0x0F00, 0x2222, 0x00F0, 0x4444},  // I 0
            {0x44C0, 0x8E00, 0x6440, 0x0E20},  // J 1
            {0x4460, 0x0E80, 0xC440, 0x2E00},  // L 2
            {0xCC00, 0xCC00, 0xCC00, 0xCC00},  // O 3
            {0x06C0, 0x8C40, 0x6C00, 0x4620},  // S 4
            {0x0C60, 0x4C80, 0xC600, 0x2640},  // Z 5
            {0x0E40, 0x4C40, 0x4E00, 0x4640}   // T 6
        };
};


#endif // TETROMINOSTATE_H