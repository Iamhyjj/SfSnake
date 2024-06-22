#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
using namespace sfSnake;

int main()
{
	Game game;
	game.run();
	// Fruit f(sf::Vector2f(200,200));
	// SnakeNode sn(sf::Vector2f(300,200));
	// sf::RenderWindow window(sf::VideoMode(800,600),"SFML window");
    // int i=0;
    // while(window.isOpen()){
    //     // 处理事件
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         // 如果关闭按钮被点击，则关闭窗口
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
    //     if(i%1000){
    //         sn.move(1,0);
    //     }
    //     window.clear(); // 清空窗口
    //     f.render(window); // 绘制水果
	// 	sn.render(window);
    //     window.display(); // 更新窗口显示
    //     i++;
    // }
	return 0;
}