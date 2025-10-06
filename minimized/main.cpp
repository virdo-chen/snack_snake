#include <iostream>
#include "./snack_snake_ex_min.hpp"



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



int main(){
    GameMap game;
    game.width = 32;
    game.height = 8;
    game.snack = 12;
    game.init();
    char map[game.width][game.height];
    for (int y = 0; y < game.height; ++y) {
            for (int x = 0; x < game.width; ++x) {
                map[x][y] = '.';
            }
        }
    
    while (true) {
        // 游戏循环
        // 可以添加输入处理、渲染等逻辑
        std::cout << "direction: ";

        // 获取用户输入
        switch (std::cin.get()){
            case ',':
                game.setDirection('u');
                break;
            case 'o':
                game.setDirection('d');
                break;
            case 'a':
                game.setDirection('l');
                break;
            case 'e':
                game.setDirection('r');
                break;
        }
        
        
        std::cin.ignore(); // 清除输入缓冲区

        int sit = game.step();

        // 蛇头身写入地图
        std::cout << "game.snakeLength:" << game.snakeLength << '\n';
        map[game.snakes[0].x()][game.snakes[0].y()] = 'H';
        for (int i = 1; i < game.snakeLength; ++i) {
            map[game.snakes[i].x()][game.snakes[i].y()] = 'S';
        }
        // 食物写入地图
        std::cout << "game.current_snack:" << game.current_snack << '\n';
        for (int i = 0; i < game.current_snack; ++i) {
            map[game.snacks[i].x()][game.snacks[i].y()] = 'F';
        }
        // 打印地图
        for (int y = 0; y < game.height; ++y) {
            for (int x = 0; x < game.width; ++x) 
                std::cout << map[x][y];
            std::cout << std::endl;
        }

        // 清空地图
        for (int y = 0; y < game.height; ++y) {
            for (int x = 0; x < game.width; ++x) {
                map[x][y] = '.';
            }
        }
        if (!sit) {
            // 游戏结束
            std::cout << "Game Over!" << std::endl;
            break; // 或者其他处理方式
        } else if (sit == 2) {
            // 胜利
            std::cout << "You Win!" << std::endl;
            break; // 或者其他处理方式
        }
    }
    game.release();
    
    std::cout << "Cache released." << std::endl;
    return 0;
}