# <center>LiClock 墨水屏天气时钟

### <center>一种兼具易用性与扩展性的多功能墨水屏天气时钟 

## <center>硬件购买注意事项
屏幕型号：`E029A01`  
ESP32：wroom或solo-1或者其它封装和引脚兼容的模组，建议Flash选大一点  

## <center>软件使用说明

### 程序烧录
手动编译，或者
打开网址：[烧录工具](https://diylxy.github.io/LiClockWebFlash/)  
---
### 拨轮开关使用说明
|  按键   | 短按功能  | 长按功能 |
|  ----  | ----  | ---- |
| 左键  | 输入数字/时间：当前位-1 | 返回上个App<br/>输入数字/时间：光标右移<br/>电子书：上一页 |
| 右键  | 输入数字/时间：当前位+1 | 输入数字/时间：光标右移<br/>电子书：下一页|
| 中键  | 确认 | 重置输入为默认值 |
---
### 点此查看[Lua App编写规范](src/lua/README.md)  

## <center>Blockly
~~因为现在的Lua语言与Blockly并未完全适配，有些“积木”后续会进行修改，其中包括：~~  

### Blockly使用教程  
无

---
### midi转buz
系统需要配置好Python环境（3.9-3.11测试均可用）  
python需要安装模块：`mido`  

`pip install mido`  

之后准备好midi文件，用IDLE或VSCode打开`tools/midi/midi_process.py`，运行python程序  
把midi文件地址（不要加引号）复制到命令窗口  
当提示`请输入模式（1:最高音优先/2:最接近上个音符优先）：`时，输入1或2（建议使用1）  

之后会在midi文件目录下生成若干buz文件，数字对应midi不同音轨，可以分别尝试后选择保留一个  
**PS**: Blockly提供了buz文件播放函数，可以直接在网页端测试播放，注意此函数会立即返回，如需停止，可以再执行`立即终止蜂鸣器播放`  

### 图像转lbm
系统需要配置好Python环境（Python3全版本均可用，不用额外安装库文件）  
首先把图像转为xbm，可以用在线工具，或在电脑上安装GIMP，使用GIMP打开图像后选择“导出”，手动修改后缀名为.xbm后点击确定，后面的配置默认即可    

然后把xbm移动到tools文件夹，打开`tools/xbm_parser.py`，运行，输入y，转换后的图像文件将保存在当前目录下，在网页端上传就能用  

此设备目前只支持lbm图像，其它解码器也不是不能加，只是觉得加了用处不大，还很浪费性能（要做也不难，之前校园生活助手7的打印机就做过Floyd-Steinberg算法）  
