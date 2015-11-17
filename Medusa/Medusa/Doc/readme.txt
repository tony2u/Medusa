1. Create window and opengl view before start game

Todo: 
1. 2D渲染可采用脏矩形优化,利用遮挡关系优化,利用4叉树优化
2.给RenderState加上Pool,以加速频繁的创建和删除

Note:
Xcode也可用#pragma once


Application:
Window:
[Views]


游戏统计信息
1、FPS
fps其实就是 frames per second,也就是每一秒游戏执行的帧数,这个数值越小,说明游戏越卡。
 
2、Draw calls
batching之后渲染mesh的数量,和当前渲染到的网格的材质球数量有关。
 
3、Saved by batching 
渲染的批处理数量,这是引擎将多个对象的绘制进行合并从而减少CPU的开销;
很多GUI插件的一个好处就是合并多个对象的渲染,从而降低DrawCalls ,保证游戏帧数。
 
4、Tris 当前绘制的三角面数
 
5、Verts 当前绘制的顶点数
 
6、Used Textures 当前帧用于渲染的图片占用内存大小
 
7、Render Textures 渲染的图片占用内存大小,也就是当然渲染的物体的材质上的纹理总内存占用
 
8、VRAM usage 显存的使用情况,VRAM总大小取决于你的显卡的显存
 
9、VBO Total 渲染过程中上载到图形卡的网格的数量,这里注意一点就是缩放的物体可能需要额外的开销。
 
10、Visible Skinned Meshes 蒙皮网格的渲染数量
 
11、Animations 播放动画的数量


TODO:
FreeType描边阴影等效果尚未实现完全

UI系统升级
1. fixed position。也就是cocos2d-x 1.x版本,cocos2d-iphone目前版本的水平
2. relative position。也就是cocos2d-x 2.x的水平
3. layout, v-box, h-box,也就是Android GUI系统,cocos2d-x 3.0 GUI的水平
4. web那种css, html图文混排的水平。目前我们还没做到。


XAML方案
1.支持矢量图,在GPU里用Shader来渲染SVG
2.多线程架构
3.UI元素的属性可以应用动画
4.可以支持3D渲染
5.支持皮肤系统
6.UI和代码分开


WPF布局原则:
不应显式设定元素的尺寸
不应使用绝对坐标
布局容器应该尽可能为其子元素设置合适的尺寸来利用空间
布局容器可以嵌套

布局的阶段:
测量,包容器询问所有子元素的尺寸
排列,在合适的位置放置子元素

Panel:
StackPanel:在一个水平或垂直的堆栈中放置元素,不换行
WrapPanel:在一系列可换行的行中放置元素,可水平或垂直
DockPanel:根据包容器的整个边界调整元素
Grid:根据一个不可见的网格在列和行中安排元素
UniformGrid:根据一个不可见但是强制所有网格具有相同尺寸的网格中安排元素
Canvas:使用固定的坐标定位元素


C++11特性支持
非静态成员初始化
final 关键字
继承构造函数 using Base::Base
委托构造函数 Info(int):Info(){}
右值引用 move,移动构造,移动赋值
完美转发 forward
初始化列表{}
模板别名 using a=
善于应用auto
decltype
追踪返回类型auto sum(T1,T2)->decltype(T1+T2){}
constexpr
变长参数模板
=default 恢复pod
=delete 删除
lambda
emplace_back,emplace,emplace_front