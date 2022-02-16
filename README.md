# 51-MCU-networked-control-IO-port
通过esp8266和免费的云服务器基于mqtt协议进行信息的交互，并通过UART传至51单片机上，进而对继电器和oled显示屏做出操作
首先是云服务平台的选取，在此我选择了一个更小众但是比较简单的云服务平台：巴法云；后续可以将这段主要代码进行修改移植到任何支持mqtt的云服务平台上，在此过程中，我曾用mqtt.fx这款APP进行服务器的调试，直至可以正常连接达到想要的效果。
对esp8266的操作我刷了安信可官方提供的支持mqtt的AT固件，并事先通过串口助手和AT指令进行调试，使其能够连接到指定云服务器并进行信息交换，另外在调试过程中我发现AT指令就是由串口发送一个个的字符，最后加上回车来操作esp8266，这也为后来我程序的书写提供了帮助，具体表现为：首先发送AT，测试连接和芯片是否正常，之后让其进入AP模式，连接手机热点，并通过刚刷入的mqtt固件中的一些特殊的AT指令，可以让其连接至指定云服务器并订阅主题收发消息。在调试过程中，我发现esp8266在掉电重启之后并不会自动连接上云服务器，但可以自动连接手机热点，这说明mqtt连接的三条AT指令是需要单片机通过串口重新发送一遍的。这点在程序中也有体现。
对51单片机的操作是让其初始化时通过串口发送三条AT指令操作esp8266连接至云服务器，并处理收到的数据，操作其他IO口接入的模块作出反应，这也是我写程序的大体思路。
对0.96寸oled液晶显示屏，此模块是通过IIC来进行数据交互的，文件中是商家提供的驱动代码，我也直接使用了，经测试其中的显示图形代码DRAWBMP()函数好像有些问题，后续我可能会重写显示图形代码，商家提供的完整资料也已上传。
对继电器的操作就是接一个IO口和电源正负，实现接线测试其是否能正常吸合断开，后直接接入单片机。
还加入了一个按键来手动控制继电器的IO口。
代码中按键部分是用定时器扫描的，包括开始时单片机发送三条AT指令其中间隔的一些时间都是通过定时器来实现的。
代码最终实现的功能是在云服务平台上发送数字1继电器吸合并且oled显示；发送0则断开并相应变化。若需移植此段代码只需将发送AT指令部分改为自己的云服务器信息，并对esp8266进行重新配置即可，也可在串口接收云服务信息模块作出改进使其能分辨更复杂的信息。
本人目前大二，利用寒假学习了51单片机，本来是想做智能家居的，但过程中蓝牙模块坏了，并且时间不足就只能进行到此。
如有疏漏，感谢指正！
