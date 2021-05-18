# 技术文档说明（大规模火山场景的渲染）

# 李源

# 最终的实现结果(非立体视觉版本）

<img src="images/技术文档说明0.png" width=500px />

有5种不同的效果

1\. <span style="color:#FF0000">地形</span> （基于perlinnoise实现）

2\. <span style="color:#FF0000">烟花</span> （基于最简单的粒子系统实现）

3\. <span style="color:#FF0000">烟雾</span> （基于noise\+解析梯度实现）

4\. <span style="color:#FF0000">岩浆</span> （基于physx实现失败，最终使用基于noise\+解析梯度实现）

5\. <span style="color:#FF0000">云朵</span> \(基于解析梯度和noise实现）

# 实现的难点

1\.数学库的优雅实现（经历多次重构，util/EigenLidan\,Matrix\.h…\)

2\.基于opengl管线的优雅实现（opengl/\*）

3\.基于glsl的光线追踪实现\(光线与noise所构建地形，云朵等的match）

4\.支持可交互（但是仅仅只能点击放烟花）

5\.简单的烟花粒子系统（没有使用物理引擎，仅仅使用shader模拟了重力，速度关系）

对老师要求的匹配: 1\. <span style="color:#FF0000">5</span>  <span style="color:#FF0000">种地物</span>  <span style="color:#FF0000">\(</span>  <span style="color:#FF0000">匹配：见上页），</span>  <span style="color:#FF0000">2\.</span>  <span style="color:#FF0000">物理引擎（没有使用，但是自行模拟了最简单的烟花粒子系统），</span>  <span style="color:#FF0000">3\.</span>  <span style="color:#FF0000">可交互（放烟花）。</span>

# 最终VR效果（因为opengl的立体视觉非常简单）（使用红蓝眼睛观看）

<img src="images/技术文档说明1.png" width=500px />

# 原始效果

# 立体视觉

# 总结

1\.综上所述，基本完成老师的要求

2\.优点：我最满意的是数学库和opengl管线的优雅实现。 以及第一次接触了，使用noise和noise的解析梯度去构造地形等物体，并使用路径追踪去渲染这些物体。 提供了立体视觉的实现。

3\.缺点：没有使用物理引擎，只是简单实现了一个粒子系统。交互性仅仅只能放烟花。

# reference

1\.[http://iquilezles\.org/www/articles/morenoise/morenoise\.htm\(noise](http://iquilezles.org/www/articles/morenoise/morenoise.htm(noise)函数及noise解析梯度计算，解析梯度可以帮助快速计算法向量）

[2\.](http://iquilezles.org/www/articles/rmshadows/rmshadows.htm)[http://iquilezles\.org/www/articles/rmshadows/rmshadows\.htm](http://iquilezles.org/www/articles/rmshadows/rmshadows.htm)（有限光线追踪中软阴影的实现）

3\.[http://iquilezles\.org/www/articles/fog/fog\.htm](http://iquilezles.org/www/articles/fog/fog.htm)\(雾的计算，以及烟的计算）

4\.软件noise lab，（提供valued noise，perlinnoise等2d噪声的实现demo）

5\.岩浆noise实现（[https://www\.shadertoy\.com/view/lslXRS](https://www.shadertoy.com/view/lslXRS)）

以上博文和软件，在我的实验中有很多帮助。

# 心得体会

Noise加解析梯度可以渲染你想要的任何东西，只要raymatch函数你写的出来。

