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


Select Other Language README: [Chinese](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/README_CN.md)

## Introduction

This project utilizes Unreal Engine 5.3 to create a Top-Down voxel RPG game. It draws inspiration from Minecraft, such as its inventory system and artistic style, as well as the Top-Down perspective, combat system, and isometric indoor scene design of the game Minecraft: Dungeon. CharmingCraft aims to offer a more relaxed gameplay experience, where players can freely explore the map, gather resources to craft weapons, complete quests, and more...


## Build

Use the `vc solution file` and the `Unreal 5.3.1 Engine source code` and `uproject file` to build. All dependency is on
this repository.

## Feature

### Equipment assembly

- Just like how people make weapons, you can use any material to create different weapon parts and assemble them together

### Smart enemy AI

- Many enemies will interact with the scene and they will use their best advantage to try to defeat you
- Current enemies: Slime, Skeleton, Skeleton Shaman

### Flexible action system

- Although it is a TopDown perspective game, you can click on the target to attack or hold down shift to attack to specify the click direction.
- Different weapons have different attack animations, and the speed of these attack animations depends on your character and equipment attributes.

### Scene switching

- When you walk into the room from the outside, the scene switching will be smooth and stylized.

### Inventory system

- The complete inventory system includes merging items, using items, discarding items, transferring items, and more.

### RPG elements

- Use the chain of responsibility design pattern to handle multiple types of damage. The damage is packaged into HitData by struct.
- Magic, arcane, and some weird stuff...

## Progress

- Implementation of projectile blueprint templates based on C++
- Interactive interface and character interaction functionality
- Chest opening feature and animation implemented through the interactive interface
- Health bar decay implemented using event binding and UI parameter exposure
- Digital animations realized through the animation system
- Dynamic materials based on mathematical functions
- Implementation of chests and keys using GameTags
- Block skill (R key) implemented using GameTags
- Material highlight and glow upon impact
- Interactive item highlight and player obstruction glow
- Inventory system and item prototypes
- Armor forging station
- Rendering 3D items in 2D
- Item assembly mechanism, crafting items from different materials
- Weapon assembly, assembling different types and materials of parts for various weapon parts
- Attack animations and ranges based on different weapon types
- Dota-style mouse movement attack system, including character rotation and new stationary attacks
- Damage number animations based on player's attack direction
- Comprehensive AI system, including EQS, Behavior Trees, Decorators, and Services
- Scene transitions implemented using scene streaming


## Content and Mechanism

- [Attribute Multiplier and Damage Calculator](https://github.com/Caishangqi/CharmingCraft/wiki/Attribute-Multiplier-and-Damage-Calculator)

## Coming Soon

- Complete attribute UI
- Game serialization and saving
- Refreshable areas: Respawn of monsters, resources, creatures
- Reset inventory UI and drag method
- Quest system with related NPCs and quest interfaces
- Developing an engaging storyline (currently no ideas)

## Awaiting Improvement

- Fixing stuck and jittery issues when interacting with items on high ground (**Fixed**)
- Correct movement behind buildings when obstructed (Ray Tracing)
- Dynamic pathfinding improvements, refreshing available routes when players destroy blocks or interact with items (**Fixed**)
- Changing item dropping from generation to a throwing action
- Rendering 3D items into 2D images requires manual placement of RenderTargetActor in the world, otherwise it fails (**Fixed**)
- The `OnHit()` method of weapons is determined by the weapon type, consider passing in a weapon class template for the interaction component to execute the template class method for **HitData** transmission (**Fixed**)

## Project Structure

### Asset Structure

- Assets
    - models
    - textures

### Code Structure

Refactoring...

## Concepts, Design Patterns, and Implementation Principles

The following content is written based on the technology used in the project. It does not cover all aspects of Unreal Engine. Unfinished records are not displayed on the main README but are shown in the project's [Wiki](https://github.com/Caishangqi/CharmingCraft/wiki).

- [Class Naming Conventions](https://github.com/Caishangqi/CharmingCraft/wiki/Class-Perfixes)
- [Controllers](https://github.com/Caishangqi/CharmingCraft/wiki/Controller)
- [Decoupling and Design Patterns](https://github.com/Caishangqi/CharmingCraft/wiki/Decoupling-and-Actor-Component)

### Implementation Principles

- [Principles of Melee Attack Implementation](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Rendering 3D Items in 2D](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Minecraft Item Structure](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Equipment Assembly - Armor](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Equipment Assembly - Weapons](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Skill System](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Combat Damage Transmission Chain](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)
- [Vector Multi-Damage Indicators](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)


## WorkFlow

### Animation Assets

- [Fast Create Animation Asset](https://www.mixamo.com/)

### Components and Native

## Resource

- Link is [Here](https://www.modongwang.com/)
