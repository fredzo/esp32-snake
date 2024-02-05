#ifndef SNAKE_H
#define SNAKE_H

#include <Arduino.h>
#include <Esp32SnakeConf.h>
#include <Adafruit_GFX.h>

const unsigned short M_RED = 0xF801;

class Snake
{
    public :
        enum Direction {UP, DOWN, LEFT, RIGHT};
        class Cell
        {
            public :
                Cell* previous = NULL;
                Cell* next = NULL;
                int x = 0;
                int y = 0;                
        };

        Snake()
        {
            head = new Cell();
            tail = head;
        };

        ~Snake()
        {
            Cell* cell = head;
            while (cell != NULL)
            {
                delete(cell);
                cell = cell->next;
            }
        };

        void setDirection(Direction direction)
        {
            this->direction = direction;
        };

        void advance(bool grow)
        {
            Cell* newHead = new Cell();
            newHead->x = head->x;
            newHead->y = head->y;
            switch(direction)
            {
                case UP:
                    newHead->y--;
                    if(newHead->y < 0) newHead->y = SCREEN_HEIGHT-1;
                    break;
                case DOWN:
                    newHead->y++;
                    if(newHead->y >= SCREEN_HEIGHT) newHead->y = 0;
                    break;
                case LEFT:
                    newHead->x--;
                    if(newHead->x < 0) newHead->x = SCREEN_WIDTH-1;
                    break;
                case RIGHT:
                    newHead->x++;
                    if(newHead->x >= SCREEN_WIDTH) newHead->x = 0;
                    break;
            }
            newHead->next = head;
            head->previous = newHead;
            head = newHead;
            if(!grow)
            {   // Si on ne grossit pas, on supprime la dernière cellule
                Cell* newTail = tail->previous;
                if(newTail != NULL)
                {
                    newTail->next = NULL;
                }
                else
                {   // Cas du snake de 1 cellule
                    newTail = head;
                }
                delete(tail);
                tail = newTail;
            }
        };

        void render(Adafruit_GFX* display)
        {
            Cell* cell = head;
            while (cell != NULL)
            {
                display->drawPixel(cell->x,cell->y,M_RED);
                cell = cell->next;
            }
        };

    private :
        Direction direction = RIGHT;
        Cell* head;
        Cell* tail;

};

#endif 