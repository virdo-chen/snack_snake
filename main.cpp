#include <iostream>
#include "./snack_snake copy.hpp"


/*
Copyright 2025 virdo-chen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache3.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/


int main(){
    GameMap game;
    std::cout << "C++老版文字版贪吃蛇，封装的GameMap类可移植哦\n每一个输入后要回车确定哦\n";
    std::cout << "输入地图宽度（建议偶数）：";std::cin >> game.width;
    std::cout << "输入地图高度（建议偶数）：";std::cin >> game.height;
    std::cout << "输入食物数量（建议不超过15：";std::cin >> game.snack;
    
    
    game.init();
    std::cin.get(); // 清除输入缓冲区
    
    
    char map[game.width][game.height];
    for (int y = 0; y < game.height; ++y) {
        for (int x = 0; x < game.width; ++x) {
            map[x][y] = '.';
        }
    }
    // 蛇头身写入地图
    map[game.snakes[0].x][game.snakes[0].y] = 'H';
    for (int i = 1; i < game.snakeLength; ++i) {
        map[game.snakes[i].x][game.snakes[i].y] = '+';
    }
    // 食物写入地图
    for (int i = 0; i < game.current_snack; ++i) {
        map[game.snacks[i].x][game.snacks[i].y] = 'F';
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


    
    while (true) {
        // 游戏循环
        // 可以添加输入处理、渲染等逻辑
        std::cout << "方向(wasd或,aoe): ";

        // 获取用户输入
        switch (std::cin.get()){
            case 'w':
            case ',':
                game.setDirection('u');
                break;
            case 's':
            case 'o':
                game.setDirection('d');
                break;
            case 'a':
                game.setDirection('l');
                break;
            case 'd':
            case 'e':
                game.setDirection('r');
                break;
        }
        
        
        std::cin.ignore(); // 清除输入缓冲区

        int sit = game.step();
        // std::cout << "sit:" << sit << std::endl;
        // std::cout << "current_snack:" << game.current_snack << std::endl;
        if (!sit) {
            // 游戏结束
            std::cout << "你无辣～" << std::endl;
            break; // 或者其他处理方式
        }
        if (sit == 2) {
            // 胜利
            std::cout << "你赢辣～" << std::endl;
            break; // 或者其他处理方式
        }
        // 蛇头身写入地图
        map[game.snakes[0].x][game.snakes[0].y] = 'H';
        for (int i = 1; i < game.snakeLength; ++i) {
            map[game.snakes[i].x][game.snakes[i].y] = '+';
        }
        // 食物写入地图
        for (int i = 0; i < game.current_snack; ++i) {
            map[game.snacks[i].x][game.snacks[i].y] = 'F';
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

        
    }
    game.release();
    
    std::cout << "内存释放。" << std::endl;
    return 0;
}