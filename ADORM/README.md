#  数据结构课程设计--<<基于社会网络分析技术的《红楼梦》人物关系分析>>
# 开发时间：2016-2017 第二学期华中科技大学 

# 选题 -- 《题目二 基于社会网络分析技术的《红楼梦》人物关系分析》
## 设计内容
    用图模型设计与表示《红楼梦》人物关系网，并以文件形式保存相关信息；运用社会网络分析技术与算法对红楼梦人物关系网进行分析，获取有意义的结果，并以图形方式呈现；提供对人物属性与人物关系的查询功能。
## 设计要求
⑴设计一定的界面，能够将分析所得人物关系结果直观显示，支持人物关系的查询。人物关系数据以文件形式保存。若界面友好，有特色，可酌情加分。
⑵选用两种以上分析模型如核心人物分析、中心性分析、小团体分析、相似子结构分析等进行分析处理，分析模型在社会网络分析相关文献中具有严格定义，设计中对分析模型的表示与处理基于对应的定义，以避免仅从字面理解而出现不严谨、简单化的设计。
⑶设计程序中处理的不同人物数量不少于100人，并根据人物数量情况、所使用的分析模型与算法的复杂程度分易、中、难三级评分。

# 开发环境
QT+C++

# 系统需求分析
1.开发语言C++，开发环境IDE  Qt5.0
2.以图的形式展示人物之间的关系
3.以直方图的方式展示与某个人物有关系的人物数量
4.以折线图的方式展示人物的重要性（越是主要人物越显重要，在折线图表现为越靠近x轴）
5.展示界面美观，适当添加背景，图片，qss样式。
6.用qss样式渲染组件，实现解耦。如需改变样式，只需要修改qss文件，而不用改动代码。
7.提供了简单查询和高级查询： 按照名字查询，按照ID查询
8.数据以文本的形式存放


# 功能设计
1.人物关系图

![此处输入图片的描述][1]

2.功能概述图

![此处输入图片的描述][2]
![此处输入图片的描述][3]

# 效果图

![此处输入图片的描述][4]
![此处输入图片的描述][5]
![此处输入图片的描述][6]
![此处输入图片的描述][7]
![此处输入图片的描述][8]
![此处输入图片的描述][9]
![此处输入图片的描述][10]
![此处输入图片的描述][11]
![此处输入图片的描述][12]
![此处输入图片的描述][13]
![此处输入图片的描述][14]
![此处输入图片的描述][15]
![此处输入图片的描述][16]
![此处输入图片的描述][17]
![此处输入图片的描述][18]
![此处输入图片的描述][19]
![此处输入图片的描述][20]
![此处输入图片的描述][21]
![此处输入图片的描述][22]
![此处输入图片的描述][23]
![此处输入图片的描述][24]
![此处输入图片的描述][25]
![此处输入图片的描述][26]
![此处输入图片的描述][27]
![此处输入图片的描述][28]
![此处输入图片的描述][29]
![此处输入图片的描述][30]
![此处输入图片的描述][31]
![此处输入图片的描述][32]
![此处输入图片的描述][33]
![此处输入图片的描述][34]
![此处输入图片的描述][35]
![此处输入图片的描述][36]



  [1]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/1.png
  [2]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/2.png
  [3]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/3.png
  [4]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/4.png
  [5]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/5.png
  [6]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/6.png
  [7]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/7.png
  [8]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/8.png
  [9]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/9.png
  [10]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/10.png
  [11]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/11.png
  [12]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/12.png
  [13]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/13.png
  [14]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/14.png
  [15]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/15.png
  [16]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/16.png
  [17]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/17.png
  [18]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/18.png
  [19]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/19.png
  [20]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/20.png
  [21]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/21.png
  [22]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/22.png
  [23]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/23.png
  [24]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/24.png
  [25]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/25.png
  [26]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/26.png
  [27]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/27.png
  [28]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/28.png
  [29]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/29.png
  [30]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/30.png
  [31]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/31.png
  [32]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/32.png
  [33]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/33.png
  [34]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/34.png
  [35]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/35.png
  [36]: https://github.com/qinjiaw2019/curriculum-design-hust/blob/master/ADORM/shotcut/36.png