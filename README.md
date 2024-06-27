# <center> 贪吃蛇游戏说明文档 Itroduction to SfSnake Game

## 游戏简介 Basic Introduction

本游戏是一款基于SFML和经典贪吃蛇代码的改良版本，玩家通过鼠标点击控制蛇的前进方向，在规定时间内通过吃水果和拾取道具获得尽可能高的分数  
This game is an improved version of the classic game Snake based on SFML. Player controls the snake by clicking. Try to get as many scores as possible in limited time!  

## 程序配置 How to start
确保您运行程序时已经安装了SFML并且包含了所有资源文件且未损坏，您可以自己配置CmakeLists文件以完成链接以及sfml的下载，我的仓库里已经提供了一份仅供参考。  
Make sure you have installed SFML and can be found by program when running the game. Also make sure all the resource files are complete.  
You can write CMakelists.txt yourself to download SFML, but I have also provided one in my repository for reference.  

## 游戏规则 Game Rules

1. 蛇在屏幕内自由移动，玩家通过鼠标点击，蛇头会向着鼠标点击的方向移动，您可以长按鼠标以灵活操纵蛇  
   The snake moves freely around the screen, and the head of the snake moves in the direction of the mouse click. You can press and hold the mouse to manipulate the snake flexibly  
2. 每隔一段时间屏幕内的随机位置会出现一些不同颜色的圆形水果，蛇吃不同颜色的水果会增加不同的长度，具体来说：  
   （1）黑色和棕色水果：不增加长度  
   （2）绿色水果：增加1格长度  
   （3）蓝色水果：增加2格长度    
   （4） 红色水果：增加3格长度  
Every once in a while, some round fruits of different colors will appear at random locations in the screen, and the snake will increase different lengths by eating fruits of different colors, specifically:    
   (1) Black and brown fruits: do not increase the length  
   (2) Green Fruits: Increases the length of 1 block  
   (3) Blue Fruit: Increases the length of 2 blocks    
   (4) Red Fruits: Increases the length of 3 blocks
3. 屏幕内在随机位置会生成一些障碍（旋转的圆形刀刃），如果蛇头碰到障碍或自身，游戏结束  
Obstacles (rotating circular blades) spawn at random locations within the screen, and if the snake's head hits the obstacle or itself, the game ends  
4. 游戏限时100秒，在右上角显示剩余时间，时间到后游戏结束  
The game is limited to 100 seconds, and the remaining time is displayed in the upper right corner.The game ends when the time is up   
5. 蛇穿过屏幕边界后，会从屏幕另一端出现  
After the snake crosses the screen border, it will appear from the other end of the screen  
6. 每隔一段时间，屏幕上会随机生成一种道具，目前有三种道具：  
   （1）护盾：拾起后蛇会进入15秒的无敌时间，期间蛇不会死亡，并且拥有**酷炫的蛇头外形**  
   （2）时钟：拾起后会增加游戏限时20秒  
   （3）奖励星：拾起后会增加游戏分数15分且不会增加蛇的长度  
Every once in a while, a random prop will be generated on the screen, and there are currently three types of items:  
   (1) Shield: After picking up, the snake will enter an invincible time of 15 seconds, during which the snake will not die, and has a **cool snake head appearance**  
   (2) Clock: After picking it up, the game time limit will be increased by 20 seconds  
   (3) Bonus Stars: Picking them up will increase the game score by 15 points and will not increase the length of the snake
7. 您可以在游戏界面按下esc以进入暂停界面，通过点击屏幕按钮改变游戏设置，其中包括：  
   （1）显示/关闭方格线（show grid）  
   （2）改变背景颜色（白色、黑色、棕色）（注意在黑色和棕色背景下若不打开方格线可能导致看不到该种颜色的水果）  
You can press ESC to enter the pause screen, and change the game settings by clicking the on-screen buttons, including:  
(1) Show/Close Grid  
(2) Change the background color (white, black, brown) (note that if you do not open the grid line on a black and brown background, you may not be able to see the fruit of that color)

## 与参考版本的差异 Differences from the original version

### 1. 基本逻辑设计差异 Basic logical differnces  
（1）移动采用鼠标点击而非键盘输入，增加了蛇的灵活性  
Using mouse cliks instead of keyboard input to increase the flexibility of the snake  
（2）采用了精灵绘制蛇，使得游戏界面更美观（效果见游戏截图）   
 Using sprite to draw the snake, which makes the game interface more beautiful(shown in the game screenshot below)  
（3）增加了Screen子类PauseScreen以及Button对象，实现游戏时暂停用鼠标点击按钮切换游戏属性, 效果如下：    
Added the Screen subclass PauseScreen and Button objects, so that the game can be paused and the game properties can be toggled with mouse clicks, and the effect is as follows:   
![游戏内PauseScreen截图](https://i.imgur.com/2lzApFi.png)  
（4）增加了水果种类，并增加了生成水果时的位置判断，确定不会和蛇、障碍和道具过近  
Added fruit types, and increased the position of fruit spawning to make sure it doesn't get too close to the snake, obstacles, and items    
（5）修改了水果生成逻辑，每隔一段时间将屏幕中的水果补到10个，而不是屏幕上没有水果再生成  
Changed the fruit spawning logic so that the number of fruits in the screen is replenished to 10 at regular intervals, instead of regenerating when there's no fruit on the screen   
（6）增加了障碍物和道具，丰富了游戏可玩性（游戏截图中障碍物为红色共3个，黄色护盾为道具之一）  
Added obstacles and props to enrich the playability of the game (there are 3 obstacles in red in the game screenshot, and the yellow shield is one of the props)   
（7）设定了游戏限时100秒，到时间后游戏自动结束  
Set a time limit of 100 seconds  
（8）在屏幕右上角增加了得分显示和剩余时间显示（见游戏截图）  
Added a score display and remaining time display in the upper right corner of the screen(shown in the game screenshot below)    
![游戏截图](https://i.imgur.com/GFaMwET.png)

### 2. 重要的代码细节差异  Important Code Differences
#### (1) 蛇节点数组元素类型不同 The element type of the nodes array is different
   参考版本将蛇的每个节点作为SnakeNode加入SnakeNode对象数组nodes_。
   而现版本将SnakeNode作为父类，派生出SnakeHead和SnakeBody子类，这主要是考虑到蛇头和蛇身的构造函数需要绑定不同纹理以及部分行为有所差异。  
   因此现版本的nodes存储的是指向蛇节点的智能指针数组，避免了将节点加入数组的切分问题，且更易于管理。  
   The original verison directly uses SnakeNode as elements.
   The current version uses SnakeNode as a base class and derives SnakeHead and SnakeBody subclasses, mainly due to the fact that the constructors of the snake head and snake body need to be bound to different textures and some behaviors are different.  
   Therefore, the current version of nodes stores an array of smart pointers to snake nodes, which avoids the slicing problem of adding nodes to the array, and is easier to manage.   

#### （2）在Game中增加了更多指针成员 Added more pointer members of Game
原版本的Game只有一个指向Screen的智能指针成员。  
现版本由于要实现在GameScreen和PauseScreen间的切换，切换期间应保存其他屏幕的数据而不应重新创建，因此加入了GameScreen_和PauseScreen_成员。   
The original version only sets one smart pointer member in the class Game  
The current version added GameScreen_ and PauseScreen_ member to switch screens. The data of different screens should be saved instead of recreated when switching.   

#### （3）为GameScreen类添加了一些静态成员 Added some static members of GameScreen
在游戏结束重启时应该重置GameScreen_成员，清空之前的游戏数据。而GameScreen是否显示网格以及背景颜色都作为静态成员变量存储，这保证了每次创建新的GameScreen实例时这两个属性不会改变，保证了游戏设置的一致性。  
When the game ends and restarts, the GameScreen_ members should be reset to erase the previous game data. The GameScreen displays the grid and the background color are stored as static member variables, which ensures that these two properties do not change every time a new GameScreen instance is created, ensuring the consistency of the game settings. 

#### （4）游戏中蛇与水果、障碍、自身的判定都采用了圆形碰撞判定 The Hitbox of furit,obstacles and snake nodes are circles 
考虑到sfml内置的getGlobalBounds方法返回覆盖对象的矩形作为判定Hitbox，这可能导致碰撞判定过于严格，因此代码中为蛇节点、水果、障碍都作为圆形形状设置半径后来进行碰撞判定（具体见Snake.cpp中的circlesIntersect函数），这更符合这些对象本身的形状，也使得碰撞判定编写时更好操控。    
Considering that the built-in getGlobalBounds method of SFML returns the rectangle of the covered object as the judgment Hitbox, which may lead to too strict collision judgment, so the code sets the radius for snake nodes, fruits, and obstacles as circular shapes and then performs collision judgment (see the circlesIntersect function in Snake.cpp for details), which is more in line with the shape of these objects themselves, and also makes the collision judgment better to control when compiling.    

#### （5）蛇移动方向进行了角度限制  The snake movement is angle-limited
考虑到鼠标点击会让蛇进行360°移动，其中就包括了蛇以接近180°的角度移动，这会直接导致蛇头与身后的节点相撞，使得游戏立即结束。为避免这一点，在蛇更新移动方向前会进行角度判定（具体见Snake.cpp的setDirectionVector函数），使得蛇头旋转角度不大于约148°，这鼓励玩家进行方向设定时不要设定过大的角度以避免自身碰撞。  
Considering that mouse clicks cause the snake to move 360°, including moving at an angle close to 180°, this will directly cause the snake's head to collide with the node behind it, causing the game to end immediately. To avoid this, the snake is angled before it updates its direction of movement (see Snake.cpp's setDirectionVector function) so that the snake's head rotates no more than about 148°, which encourages the player not to set too much angle to avoid colliding with itself.  
#### （6）蛇头与自身节点判时忽略了第2、3个节点的判定 Ignoring the collision judgement of the 2nd and 3rd snake node
考虑到在目前程序所绘制的蛇在正常情况下，蛇头**无论如何也不可能**与第2、3个节点碰撞，因此忽略这两个节点自身碰撞判定，使得蛇在以某些特定角度移动时不会错误地判定碰撞，若要改变蛇的外形可能需要重新考虑这一判定逻辑。（具体见Snake.cpp的checkSelfColiisions方法）    
Considering that under normal circumstances, the snake's head **can never** collide with the second and third nodes under normal circumstances, so ignoring the collision judgment of these two nodes themselves, so that the snake will not incorrectly judge the collision when moving at some specific angles, and this judgment logic may need to be reconsidered if you want to change the shape of the snake. (See Snake.cpp's checkSelfColiisions method for details)    
## 安全性和性能讨论 Security and performance discussions
### 安全性 Security
#### (1) 对象行为安全性 Object behavior security  
程序中在必要的地方都严格限制了对象属性和方法的可更改性，例如对render(),getBounds()等方法，以及texture使用了const修饰，确保了对象行为的安全性，不会随意修改重要参数。  
The program strictly restricts the changeability of object properties and methods in necessary places, such as the use of const modification for render(), getBounds() and texture, to ensure the safety of object behavior, and not to modify important parameters arbitrarily.   
#### （2）内存安全性 Memory security
程序中资源管理都使用了智能指针，避免了内存泄露的问题；容器使用了STL和SFML内置容器，安全可靠。  
Smart pointers are used for resource management in the program to avoid memory leakage. The container uses STL and SFML built-in containers, which are safe and reliable.  

### 性能 Performance
#### （1）最大化减少了I/O操作 Reduced I/O operations
程序中将sprite使用的texture作为类的静态成员，这样可以使得读取纹理文件只进行一次，而不会在每次创建实例时都进行读取。  
The texture used by the sprite is used as a static member of the class, which allows the texture file to be read only once, rather than every time an instance is created.  
#### （2）引用和指针的使用 Using reference and pointers
程序中在诸多地方都使用了引用传递参数，例如for循环中的const auto&修饰，传递item和nodes时使用智能指针，这避免了深拷贝导致的性能浪费
There are many places in the program that use reference passing parameters, such as const auto& in the for loop, and smart pointers when passing items and nodes, which avoids the performance waste caused by deep copies  
## 鸣谢 Acknowledgement
该项目基于github上已有的代码框架进行开发，https://github.com/jhpy1024/sfSnake%E3%80%82 ，感谢这位作者提供的思路。  
The project is developed based on the existing code framework on GitHub, https://github.com/jhpy1024/sfSnake%E3%80%82, thanks to this author for the ideas.
