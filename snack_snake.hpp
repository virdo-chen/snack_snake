#include <cstdlib>
#include <vector>


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
    u_int8_t x;u_int8_t y;
    bool operator==(const pos& other) const {
        return x == other.x && y == other.y;
    }
};

bool in_list(pos * vecA, pos a, std::vector<pos> list) {
    for (pos element : list) {
        if (element == a && vecA!=&element) return true;
    }
    return false;
}



class GameMap
{
    char direction = 'u';

    bool eat() {
        // Implement the logic to check if the snake eats a snack
        // For example, check if the snake's head position matches any snack position
        for (short i = this->current_snack; i; --i) {
            if (this->snakes[0].x == this->snacks[i-1].x && this->snakes[0].y == this->snacks[i-1].y) {
                this->deal_with_eat(i-1); 
                return true; // Snake has eaten a snack
            }
        }
        return false; // No snack eaten
    }

    void deal_with_eat(short idxm1) { // index minus one
        // Implement the logic to handle the snake eating a snack
        // For example, increase the snake length and generate a new snack
        if ((this->snakeLength + this->snack)<this->width * this->height) {
            do
            {
                this->snacks[idxm1].x = rand() % this->width;
                this->snacks[idxm1].y = rand() % this->height;
            }
            while(in_list(&(this->snacks[idxm1]), this->snacks[idxm1], this->snakes)
                ||in_list(&(this->snacks[idxm1]), this->snacks[idxm1], this->snacks));
            // ++this->current_snack;
        }
        else {
            for (short i = idxm1; i < this->current_snack - 1; ++i) {
                this->snacks[i] = this->snacks[i + 1];
            };
            --this->current_snack;
        };
    };


public:
    short width = 10;
    short height = 10;
    short snack = 10;
    short current_snack = snack;

    std::vector<pos> snacks = std::vector<pos>(snack);
    std::vector<pos> snakes = std::vector<pos>(width * height);
    short snakeLength = 2;

    void init() {
        this->snakeLength = 2;
        this->direction = 'u';
        this->current_snack = this->snack;
        this->snakes[0].x = this->width / 2;
        this->snakes[0].y = this->height / 2;
        this->snakes[1].x = this->width / 2 + 1;
        this->snakes[1].y = this->height / 2;
        

        for (short i = 0; i < this->snack; ++i) 
        do
        {
            this->snacks[i].x = rand() % this->width;
            this->snacks[i].y = rand() % this->height;
        }
        while(in_list(&(this->snacks[i]), this->snacks[i], this->snakes)
            ||in_list(&(this->snacks[i]), this->snacks[i], this->snacks));
        // ++this->current_snack;
    };

    int step() {  // 0失败，1继续，2胜利
        // Implement the logic for moving the snake and checking for snacks
        // 拉蛇身
        for (short length_i = this->snakeLength; length_i; --length_i) {
            this->snakes[length_i] = this->snakes[length_i - 1];
        }
        
        // 移头部
        switch (this->direction) {
            case 'u':
                this->snakes[0].y -= 1;
                break;
            case 'd':
                this->snakes[0].y += 1;
                break;
            case 'l':
                this->snakes[0].x -= 1;
                break;
            case 'r':
                this->snakes[0].x += 1;
                break;
        }
    
        // 检查是否吃到食物
        if (this->eat()) ++this->snakeLength;        

        // 检查是否撞到自己
        for (short i = 1; i < this->snakeLength; ++i)
        {
            if (this->snakes[0] == this->snakes[i]){
                // 撞到自己了，游戏结束
                return 0; // 或者其他处理方式
            }
        }

        // 检查是否撞墙
        if (this->snakes[0].x < 0 || this->snakes[0].x >= this->width ||
            this->snakes[0].y < 0 || this->snakes[0].y >= this->height) {
            // 撞墙了，游戏结束
            return 0; // 或者其他处理方式
        }

        // 检查是否胜利
        if (!this->current_snack) {
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
        // delete this->snacks;
        // delete this->snakes;
        0;
    }
};