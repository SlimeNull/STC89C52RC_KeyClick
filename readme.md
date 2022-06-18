# KeyClick

独立按键点击检测封装. 通过简单的方式来控制按键单击的处理逻辑.

## 使用:

1. 将仓库中 loops.c 文件添加到你的项目中
2. 在程序中添加主循环逻辑:

    ```cpp
    extern void button_loop();   // 声明按钮循环函数

    void main()
    {
        // 其他代码

        while (1)  // 程序主循环
        {
            // 其他代码
            button_loop();     // 按钮检查
        }
    }
    ```

3. 定义按键按下处理函数:

    ```cpp
    void key1click()
    {
        P2 = ~P2;    // 切换 LED 灯显示状态
    }
    ```

4. 订阅按键按下事件

    ```cpp
    extern void on_k1_click(void (*handler)());

    void main()
    {
        on_k1_click(key1click);   // 订阅按键按下事件

        while (1)
        {
            button_loop();        // 主循环
        }
    }
    ```

## 函数

在 loops.c 文件中, 定义了以下函数:

```cpp
void button_loop();                         // 按钮主循环
void on_k1_click(void (*handler)());        // 订阅按钮1按下事件
void on_k2_click(void (*handler)());        // 订阅按钮2按下事件
void on_k3_click(void (*handler)());        // 订阅按钮3按下事件
void on_k4_click(void (*handler)());        // 订阅按钮4按下事件
void on_anyk_click(void (*handler)(int));   // 订阅任意按钮按下事件
```

## 代码示例

```cpp
#include <REGX52.H>
extern void button_loop();
extern void on_k1_click(void (*handler)());
extern void on_k2_click(void (*handler)());
extern void on_k3_click(void (*handler)());
extern void on_k4_click(void (*handler)());
extern void on_anyk_click(void (*handler)(int));

void switch_led(int index) {
	P2 ^= ((1 << (index * 2)) + (1 << (index * 2 + 1)));
}

void main()
{
	on_anyk_click(switch_led);
	
	while(1)
	{
		button_loop();
	}
}
```