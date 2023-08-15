# CharmingCraft: Unreal Remaster

<p align="center">
<img src = "https://github.com/Caishangqi/minecraft-modpack-charmingcraft-journey/assets/39553613/290e0607-2e2a-4f35-9149-6abfe15459f7">
</p>

<h4 align="center">Concurrent Development of Game Project from Minecraft ModPack and made by Unreal 5</h4>
<p align="center">
<a href="https://www.codefactor.io/repository/github/caishangqi/charmingcraft"><img src="https://www.codefactor.io/repository/github/caishangqi/minecraft-modpack-charmingcraft-journey/badge" alt="CodeFactor" /></a>
<img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/Caishangqi/CharmingCraft">
<img alt="Lines of code" src="https://img.shields.io/badge/Unreal-5.2-orange">
<img alt="GitHub branch checks state" src="https://img.shields.io/github/checks-status/Caishangqi/CharmingCraft/master?label=build">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Caishangqi/CharmingCraft">
</p>

## 介绍 Introduction

The project is a replica of the Minecraft modpack called Charming Craft, utilizing Unreal Engine 5 to replicate both the
content and gameplay. As the first C++ game project, this endeavor encompasses numerous areas of inefficiency and room
for improvement. Additionally, there is a comprehensive wiki documenting noteworthy aspects of Unreal Engine.

## 构建 Build

Use the `vc solution file` and the `Unreal 5.2 Engine source code` and `uproject file` to build. All dependency is on
this repository.

## 进度 Progress

- 人物弹簧摄像机 `USpringArmComponent` 应用
- 人物基于弹簧摄像头的绝对位移 应用
- 基于C++的投射物蓝图模板实现
- 交互接口以及人物交互功能
- 基于交互接口实现的开宝箱功能及动画
- 基于C++的 `Actor Component` 解耦人物属性
- 使用 Tick() 事件刷新的血量显示
- 使用事件绑定触发的血量刷新和显示 (改进)
- 基于事件绑定和UI参数暴露实现血条衰减
- 基于动画系统实现的数字动画
- 基于数学函数的动态材质
- 使用游戏标签 GameTags 实现箱子和钥匙
- 使用游戏标签 GameTags 实现格挡技能 (R) 键
- 在击中时使材质发亮,显示高光
- 第二套操控输入,支持鼠标点击和长按
- 物品交互高光和玩家遮挡高光
- 物品栏系统,物品原型

## 即将到来

- 人物建模和动画
- 完整的属性UI
- 近战攻击和基础装备系统
- Episodes 35,70 ...

## 等待改进

- 寻路高处可交互物品造成的卡死,抖动
- 在被建筑物遮挡时正确地在建筑物后方移动 (Ray Tracing)
- 动态寻路完善, 玩家在破坏方块或者交互物品时刷新可供的路线
- 丢弃物品的时候是发射行为而不是生成行为

## 项目结构

### 项目资源结构

- assets\ccraft\textures\item

## 概念,设计模式,和知识点

以下内容基于项目所使用的技术编写,并没有包含全部 UE 的内容,未完成的记录不会展现在主页readme而是会在项目的 [**Wiki**](https://github.com/Caishangqi/CharmingCraft/wiki) 中展示。

- [类名规范](https://github.com/Caishangqi/CharmingCraft/wiki/Class-Perfixes)
- [控制器](https://github.com/Caishangqi/CharmingCraft/wiki/Controller)
- [解耦和设计模式](https://github.com/Caishangqi/CharmingCraft/wiki/Decoupling-and-Actor-Component)

## 资源 Resource

- 链接在 [这里](https://www.modongwang.com/)