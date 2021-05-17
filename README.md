<!--
 * @Descripttion: 
 * @version: 0.1
 * @Author: Mengbw
 * @Date: 2021-05-17 20:31:51
 * @LastEditors: Mengbw
 * @LastEditTime: 2021-05-17 20:31:51
-->
# netlib: 基于muduo库实现C++11版本的轻量网络库
> **version：0.1**
>

## Google风格编码
1. 类名、结构体、枚举、typedef 大驼峰 `ThreadPool`
2. 普通变量，小写加下划线 `first_name` 
3. class类成员变量最后加下划线, struct 不用 `ThreadPool::name_`
4. 常量命名：k开头大小写混写   `const int kDaysInAWeek = 7`, 枚举变量同
5. 函数命名：小驼峰


## 更改方面：
1. 时间戳实现封装C++11中的\<chrono>
2. 原子操作即采用C++11中的atomic对int和long类型的特化版本
3. 使用C++11的mutex以及condition替代muduo封装的对应的类型



## git 提交规范：
- 特性新增: 增加了新的功能
- 问题修复: 修复了bug
- 文档补充: 文档补充
- 格式调整: 格式（不影响代码运行的变动）
- 优化重构: 重构（不是新增功能，也不是修复bug的代码变动）
- 测试新增: 增加了新的测试
- 辅助变动: 构建过程或辅助工具的变动

## .vscode 文件夹
该项目是在vscode平台, 通过sshremote插件实现远程连接到云主机
.vscode文件夹是相关的一些设置