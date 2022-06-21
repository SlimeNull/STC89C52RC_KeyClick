# KeyClick

独立按键点击检测封装. 通过简单的方式来控制按键单击的处理逻辑.

## 使用:

1. 将仓库中 btnclick.h 和 btnclick.c 文件添加到你的项目中
2. 引用头文件
   ```cpp
   #include "btnclick.h"
   ```
3. 在程序中添加主循环逻辑:

    ```cpp
    void main()
    {
        // 其他代码

        while (1)  // 程序主循环
        {
            // 其他代码
            btnclick_loop();     // 按钮检查
        }
    }
    ```

4. 定义按键按下处理函数:

    ```cpp
    void key1click()
    {
        P2 = ~P2;    // 切换 LED 灯显示状态
    }
    ```

5. 订阅按键按下事件

    ```cpp
    void main()
    {
        on_k1_click(key1click);   // 订阅按键按下事件

        while (1)
        {
            btnclick_loop();        // 主循环
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
void on_anyk_click(void (*handler)(int));   // 订阅任意按钮按下事件, 参数为按钮索引
```

## 代码示例

```cpp
#include <REGX52.H>
#include "btnclick.h"

void switch_led(int index) {
	P2 ^= ((1 << (index * 2)) + (1 << (index * 2 + 1)));
}

void main()
{
	on_anyk_click(switch_led);
	
	while(1)
	{
		btnclick_loop();
	}
}
```