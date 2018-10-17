# SLINK_SDK #

----------

SLINK V1.0

快速对接各种云平台
采用“数据原子”模型  快速开发智能硬件
开发环境  
ubuntu 14.04  +  xtensa..-gcc 工具链

## 简介 ##

底层系统 ： FreeRtos
硬件平台 ： ESP8266
开发语言 ： C 
SDK基于  ： 涂鸦云SDK 以及  ESP8266SDK


## 目录说明 ##

app                   为应用开发目录      在此文件夹 开发相关基于SLINK的应用
bin                   为程序固件输出目录  

ex.../xtensa          外部库引用          不用管
include               SDK引用头文件       不用管
ld lib                SDK引用库           不用管
tools                 SDK编译依赖工具     不用管
.output/eagle/debug   为编译中间输出      不用管  
  
## 编译路径 ##

For Linux:

    $export SDK_PATH=~/ESP8266_RTOS_SDK
    $export BIN_PATH=~/ESP8266_BIN

For Windows:

    set SDK_PATH=/c/ESP8266_RTOS_SDK
    set BIN_PATH=/c/ESP8266_BIN

ESP8266_RTOS_SDK/examples/project_template is a project template, you can copy this to anywhere, e.g., to ~/workspace/project_template.

   
## 编译脚本 ##
详见 编译说明

## 常见问题 ##
1.在linux 平台下 执行编译脚本xxx.sh后 报错 
因为windows对于sh文本保存后会自动加上 一些特殊换行符   
所以如果报错 ，对相应的报错文件  执行 vim  xxx.sh    
然后：set fileformat=unix
接着: wq  




