工程打开路径 Project->MDK5->LED.uvprojx
hardware里每个.c文件对应一个外设，几乎都有**_test()函数，可直接放在main()中调用
如果不会调用可以参考menu.c文件