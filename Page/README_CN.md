# CharmingCraft: Journey (Unreal Build)
![project_title](https://github.com/Caishangqi/CharmingCraft/assets/39553613/afff6fe3-e541-455d-978c-84dfd8df58f3)
<p align="center">
<img src = "https://i.imgur.com/EF6t6WA.png">
</p>

<h4 align="center">A Pixel Low poly top-down RPG game implement by Unreal Engine 5.3</h4>
<p align="center">
<a href="https://www.codefactor.io/repository/github/caishangqi/charmingcraft"><img src="https://www.codefactor.io/repository/github/caishangqi/minecraft-modpack-charmingcraft-journey/badge" alt="CodeFactor" /></a>
<img alt="Lines of code" src="https://img.shields.io/tokei/lines/github/Caishangqi/CharmingCraft">
<img alt="Lines of code" src="https://img.shields.io/badge/Unreal-5.3.1-orange">
<img alt="GitHub branch checks state" src="https://img.shields.io/github/checks-status/Caishangqi/CharmingCraft/master?label=build">
<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/Caishangqi/CharmingCraft">
</p>

## 介绍

本项目使用 Unreal Engine 5.3 开发了一款顶视角体素 RPG 游戏。该游戏从《Minecraft》中汲取灵感，比如其背包系统、艺术风格，以及《Minecraft: Dungeon》的顶视角、战斗系统和等距室内场景设计。《CharmingCraft》旨在创造一种更加休闲的游戏体验，玩家可以自由地探索地图、收集资源制作武器、完成任务等等。

## 构建

Use the `vc solution file` and the `Unreal 5.3.1 Engine source code` and `uproject file` to build. All dependency is on
this repository.

## 特性

Waiting for the release of the first playable demo.

等待第一个试玩版本发布

## 进度

- 基于C++的投射物蓝图模板实现
- 交互接口以及人物交互功能
- 基于交互接口实现的开宝箱功能及动画
- 基于事件绑定和UI参数暴露实现血条衰减
- 基于动画系统实现的数字动画
- 基于数学函数的动态材质
- 使用游戏标签 GameTags 实现箱子和钥匙
- 使用游戏标签 GameTags 实现格挡技能 (R) 键
- 在击中时使材质发亮,显示高光
- 物品交互高光和玩家遮挡高光
- 物品栏系统,物品原型
- 盔甲锻造台
- 3D物品渲染2D
- 物品装配机制, 不同材料打造物品
- 武器装配,不同武器部分可装配不同类型和材料的零件
- 基于不同武器类型的攻击动画和攻击范围
- Dota 鼠标移动攻击系统, 例如角色转身,和新加原地攻击等...
- 基于玩家攻击方向的 伤害数字 动画

## 内容机制

- [属性乘区和伤害计算](https://github.com/Caishangqi/CharmingCraft/wiki/Attribute-Multiplier-and-Damage-Calculator)

## 即将到来

- 完整的属性UI
- 近战攻击和基础装备系统
- Episodes 35,70 ...

## 等待改进

- 寻路高处可交互物品造成的卡死,抖动 (**已修复**)
- 在被建筑物遮挡时正确地在建筑物后方移动 (Ray Tracing)
- 动态寻路完善, 玩家在破坏方块或者交互物品时刷新可供的路线
- 丢弃物品的时候是发射行为而不是生成行为
- 渲染成3D物品至2D图像时必须放置手动在世界放置RenderTargetActor否则失效 (**已修复**)
- 武器的 `OnHit()` 方法是由武器类型决定的, 可以考虑传入武器类模板让交互组件执行模板类的方法实现 **HitData** 传递

## 项目结构

### 项目资产结构

- Assets
    - models
    - textures

### 项目源码结构

- Source
    - Object
        - Class
            - Core
            - Item
            - Util
        - Component
        - Enum
        - Struct
            - model
                - sword
                    - blade
                    - fuller
                    - guard
                    - hilt
                    - pommel
    - Interface
        - Meta
            - model

## 概念,设计模式,和实现原理

以下内容基于项目所使用的技术编写,并没有包含全部 UE 的内容,未完成的记录不会展现在主页readme而是会在项目的 **[Wiki
](https://github.com/Caishangqi/CharmingCraft/wiki)** 中展示

- [类名规范](https://github.com/Caishangqi/CharmingCraft/wiki/Class-Perfixes)
- [控制器](https://github.com/Caishangqi/CharmingCraft/wiki/Controller)
- [解耦和设计模式](https://github.com/Caishangqi/CharmingCraft/wiki/Decoupling-and-Actor-Component)

### 实现原理

- [近战攻击实现原理](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [3D物品渲染2D](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Minecraft 物品结构](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [装备组装 - 盔甲](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [装备组装 - 武器](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [技能系统](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [战斗伤害传递链](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [向量多伤害指示器](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
-

## WorkFlow

### Animation Assets

- [Fast Create Animation Asset](https://www.mixamo.com/)

### Components and Native

## 资源 Resource

- 链接在 [这里](https://www.modongwang.com/)
