#include <cstdlib>


/*
Copyright 2025 virdo-chen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


struct pos {
    u_int8_t xy;
    bool operator==(const pos& other) const {
        return x() == other.x() && y() == other.y();
    }

    u_int8_t x() const {
        return xy >> 3;
    }

    u_int8_t y() const {
        return xy & 0x07;
    }

    void set_x(u_int8_t x) {
        xy = (xy & 0x07) | (x << 3);
    }

    void set_y(u_int8_t y) {
        xy = (xy & 0xF8) | (y & 0x07);
    }
};

bool in_list(pos a, pos * list, u_int8_t size) {
    for (u_int8_t i = 0; i < size; ++i) {
        if (list[i] == a) return true;
    }
    return false;
}



class GameMap
{
    char direction = 'u';

    bool eat() {
        // Implement the logic to check if the snake eats a snack
        // For example, check if the snake's head position matches any snack position
        for (u_int8_t i = this->current_snack; i; --i) {
            if (this->snakes[0] == this->snacks[i-1]) {
                this->deal_with_eat(i-1); 
                return true; // Snake has eaten a snack
            }
        }
        return false; // No snack eaten
    }

    void deal_with_eat(u_int8_t idxm1) { // index minus one
        // Implement the logic to handle the snake eating a snack
        // For example, increase the snake length and generate a new snack
        if ((this->snakeLength + this->snack)<this->width * this->height) {
            do
            {
                this->snacks[idxm1].set_x(rand() % this->width);
                this->snacks[idxm1].set_y(rand() % this->height);
            }
            while(in_list(this->snacks[idxm1], this->snakes, this->snakeLength) 
                ||in_list(this->snacks[idxm1], this->snacks, idxm1)
                ||in_list(this->snacks[idxm1], this->snacks + idxm1 + 1, this->current_snack - idxm1 - 1));
            // ++this->current_snack;
        }
        else {
            for (u_int8_t i = idxm1; i < this->current_snack - 1; ++i) {
                this->snacks[i] = this->snacks[i + 1];
            };
            --this->current_snack;
        };
    };


public:
    u_int8_t width = 32;
    u_int8_t height = 8;
    u_int8_t snack = 10;
    u_int8_t current_snack = snack;

    pos * snacks = new pos[snack];
    pos * snakes = new pos[width * height];
    u_int8_t snakeLength = 2;

    void init() {
        this->snakeLength = 2;
        this->direction = 'u';
        this->current_snack = this->snack;
        this->snakes[0].set_x(this->width / 2);
        this->snakes[0].set_y(this->height / 2);
        this->snakes[1].set_x(this->width / 2 + 1);
        this->snakes[1].set_y(this->height / 2);
        

        for (u_int8_t i = 0; i < this->snack; ++i) 
        do
        {
            this->snacks[i].set_x(rand() % this->width);
            this->snacks[i].set_y(rand() % this->height);
        }
        while(in_list(this->snacks[i], this->snakes, this->snakeLength) 
            ||in_list(this->snacks[i], this->snacks, i)
            ||in_list(this->snacks[i], this->snacks + i + 1, this->current_snack - i - 1));
        // ++this->current_snack;
    };

    int step() {
        // Implement the logic for moving the snake and checking for snacks
        // 检查是否撞墙
        if (
            ((this->snakes[0].x()==0)&&(this->direction=='l'))||
            ((this->snakes[0].x()==this->width-1)&&(this->direction=='r'))||
            ((this->snakes[0].y()==0)&&(this->direction=='u'))||
            ((this->snakes[0].y()==this->height-1)&&(this->direction=='d'))
           ) {
            // 撞墙了，游戏结束
            return 0; // 或者其他处理方式
        }

        // 拉蛇身
        for (u_int8_t length_i = this->snakeLength; length_i; --length_i) {
            this->snakes[length_i] = this->snakes[length_i - 1];
        }
        
        // 头部移动
        switch (this->direction) {
            case 'u':
                this->snakes[0].set_y(this->snakes[0].y() - 1);
                break;
            case 'd':
                this->snakes[0].set_y(this->snakes[0].y() + 1);
                break;
            case 'l':
                this->snakes[0].set_x(this->snakes[0].x() - 1);
                break;
            case 'r':
                this->snakes[0].set_x(this->snakes[0].x() + 1);
                break;
        }

        // 检查是否吃到食物
        if (this->eat()) ++this->snakeLength;

        // 检查是否撞到自己
        for (u_int8_t i = 1; i < this->snakeLength; ++i)
        {
            if (this->snakes[0] == this->snakes[i]){
                // 撞到自己了，游戏结束
                return 0; // 或者其他处理方式
            }
        }

        // 检查是否胜利
        if (this->snakeLength >= this->width * this->height) {
            // 胜利条件，游戏结束
            return 2; // 或者其他处理方式
        }
        return 1; // 继续游戏
    }; 

    void setDirection(char dir) {
        // 设置蛇的移动方向
        switch (this->direction){
        case 'u':
            if (dir != 'd') this->direction = dir;
            break;
        case 'd':
            if (dir != 'u') this->direction = dir;
            break;
        case 'l':
            if (dir != 'r') this->direction = dir;
            break;
        case 'r':
            if (dir != 'l') this->direction = dir;
            break;
        }
    }

    void release() {
        delete[] this->snacks;
        delete[] this->snakes;
    }
};