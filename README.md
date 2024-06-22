# <center> 贪吃蛇游戏说明文档

## 游戏简介

本游戏是一款基于sfml和经典贪吃蛇代码的改良版本，玩家通过鼠标点击控制蛇的前进方向，在规定时间内通过吃水果和拾取道具获得尽可能高的分数

## 游戏规则

1. 蛇在屏幕内自由移动，玩家通过鼠标点击，蛇头会向着鼠标点击的方向移动，您可以长按鼠标以灵活操纵蛇
2. 每隔一段时间屏幕内的随机位置会出现一些不同颜色的圆形水果，蛇吃不同颜色的水果会增加不同的长度，具体来说：  
   （1）黑色和棕色水果：不增加长度  
   （2）绿色水果：增加1格长度  
   （3）蓝色水果：增加2格长度    
   （4） 红色水果：增加3格长度
3. 屏幕内在随机位置会生成一些障碍（旋转的圆形刀刃），如果蛇头碰到障碍或自身，游戏结束
4. 游戏限时100秒，在右上角显示剩余时间，时间到后游戏结束
5. 蛇穿过屏幕边界后，会从屏幕另一端出现
6. 每隔一段时间，屏幕上会随机生成一种道具，目前有三种道具：  
   （1）护盾：拾起后蛇会进入15秒的无敌时间，期间蛇不会死亡，并且拥有**酷炫的蛇头外形**  
   （2）时钟：拾起后会增加游戏限时20秒  
   （3）奖励星：拾起后会增加游戏分数15分且不会增加蛇的长度
7. 您可以在游戏界面按下esc以进入暂停界面，通过点击屏幕按钮改变游戏设置，其中包括：  
   （1）显示/关闭方格线（show grid）  
   （2）改变背景颜色（白色、黑色、棕色）（注意在黑色和棕色背景下若不打开方格线可能导致看不到该种颜色的水果）



## 与参考版本的差异

### 1. 基本逻辑设计差异  
（1）移动采用鼠标点击而非键盘输入，增加了蛇的灵活性  
（2）采用了精灵绘制蛇，使得游戏界面更美观（效果见游戏截图）  
（3）增加了Screen子类PauseScreen以及Button对象，实现游戏时暂停用鼠标点击按钮切换游戏属性, 效果如下：  
![游戏内PauseScreen截图](GameScreenshot/PauseScreen.png)  
（4）增加了水果种类，并增加了生成水果时的位置判断，确定不会和蛇、障碍和道具过近  
（5）修改了水果生成逻辑，每隔一段时间将屏幕中的水果补到10个，而不是屏幕上没有水果再生成  
（6）增加了障碍物和道具，丰富了游戏可玩性（游戏截图中障碍物为红色共3个，黄色护盾为道具之一）  
（7）设定了游戏限时100秒，到时间后游戏自动结束  
（8）在屏幕右上角增加了得分显示和剩余时间显示（见游戏截图）  
![游戏截图](GameScreen.png)

### 2. 重要的代码细节差异  
#### (1) 蛇节点数组元素类型不同 
   参考版本将蛇的每个节点作为SnakeNode加入SnakeNode对象数组nodes_。  
   而现版本将SnakeNode作为父类，派生出SnakeHead和SnakeBody子类，这主要是考虑到蛇头和蛇身的构造函数需要绑定不同纹理以及部分行为有所差异。  
   因此现版本的nodes存储的是指向蛇节点的智能指针数组，避免了将节点加入数组的切分问题，且更易于管理。  

#### （2）在Game中增加了更多指针成员
原版本的Game只有一个指向Screen的智能指针成员。  
现版本由于要实现在GameScreen和PauseScreen间的切换，切换期间应保存其他屏幕的数据而不应重新创建，因此加入了GameScreen_和PauseScreen_成员。 

#### （3）为GameScreen类添加了一些静态成员 
在游戏结束重启时应该重置GameScreen_成员，清空之前的游戏数据。而GameScreen是否显示网格以及背景颜色都作为静态成员变量存储，这保证了每次创建新的GameScreen实例时这两个属性不会改变，保证了游戏设置的一致性。

#### （4）游戏中蛇与水果、障碍、自身的判定都采用了圆形Hitbox判定
考虑到sfml内置的getGlobalBounds方法返回覆盖对象的矩形作为判定Hitbox，这可能导致碰撞判定过于严格，因此代码中为蛇节点、水果、障碍都作为圆形形状设置半径后来进行碰撞判定（具体见Snake.cpp中的circlesIntersect函数），这更符合这些对象本身的形状，也使得碰撞判定编写时更好操控。  

#### （5）蛇移动方向进行了角度限制
考虑到鼠标点击会让蛇进行360°移动，其中就包括了蛇以接近180°的角度移动，这会直接导致蛇头与身后的节点相撞，使得游戏立即结束。为避免这一点，在蛇更新移动方向前会进行角度判定（具体见Snake.cpp的setDirectionVector函数），使得蛇头旋转角度不大于约148°，这鼓励玩家进行方向设定时不要设定过大的角度以避免自身碰撞。
#### （6）蛇头与自身节点判时忽略了第2、3个节点的判定
考虑到在目前程序所绘制的蛇在正常情况下，蛇头**无论如何也不可能**与第2、3个节点碰撞，因此忽略这两个节点自身碰撞判定，使得蛇在以某些特定角度移动时不会错误地判定碰撞，若要改变蛇的外形可能需要重新考虑这一判定逻辑。（具体见Snake.cpp的checkSelfColiisions方法）

## 安全性和性能讨论
### 安全性
#### (1) 对象行为安全性
程序中在必要的地方都严格限制了对象属性和方法的可更改性，例如对render(),getBounds()等方法，以及texture使用了const修饰，确保了对象行为的安全性，不会随意修改重要参数。
#### （2）内存安全性
程序中资源管理都使用了智能指针，避免了内存泄露的问题；容器使用了STL和SFML内置容器，安全可靠。

### 性能
#### （1）减少了I/O操作
程序中将sprite使用的texture作为类的静态成员，这样可以使得读取纹理文件只进行一次，而不会在每次创建实例时都进行读取。
#### （2）引用和指针的使用
程序中在诸多地方都使用了引用传递参数，例如for循环中的const auto&修饰，传递item和nodes时使用智能指针，这避免了深拷贝导致的性能浪费

## 鸣谢
该项目基于github上已有的代码框架进行开发，https://github.com/jhpy1024/sfSnake%E3%80%82 ，感谢这位作者提供的思路。
