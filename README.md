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

This project build based ib Unreal Engine 5.3 to create a Top-Down voxel RPG game. It draws inspiration from Minecraft, such
as its inventory system and artistic style, as well as the Top-Down perspective, combat system, and isometric indoor
scene design of the game Minecraft: Dungeon. CharmingCraft aims to offer a more relaxed gameplay experience, where
players can freely explore the map, gather resources to craft weapons, complete quests, and more...

## Build

Use the `vc solution file` and the `Unreal 5.3.1 Engine source code` and `uproject file` to build. All dependency is on
this repository.

## Feature

### Inventory system (Reformated version)

![Inventory System](https://github.com/Caishangqi/CharmingCraft/assets/39553613/fc5dc7c2-f917-46b6-8202-8f1a388e62ed)

- **Quick hotbar** allow player siwtch different modes (**`Z` battle**, **`X` Inventory hotbar**, **`C` Building**, **`V` Team**)
- The complete inventory system includes **merging** items, **using** items, **drop** items, **transferring** items, and more.
- **Detailed item pannel** show item attributes and large preview.
- Quickly close and open container, support player open inventory when moving.
- **Auto open player inventory** when open any container, close both pannel when player inventory is opened by container not by player. (else close only container)
- 10 Equipment slot with **equip model binding**.

### Build system
![Build System](https://github.com/Caishangqi/CharmingCraft/assets/39553613/25aab4d0-cb80-47e3-b726-656243074b34)
- When switching game modes, automatically load **ContextMapping layouts** according to the mode to prevent key conflicts.
- Supports building, rotation (using `Q` and `E` keys), build specification preview, collision highlighting, destruction, and other functions (press `F` to switch between **Build** / **Destroy** mode).
- In build mode, automatically disable the interaction between players and interactive objects.
- Supports **filters** that only allow building in appropriate areas, such as preventing players from building in mining areas.

### Chunk System (Refactory of Biome Actor)
![chunk-system](https://github.com/Caishangqi/CharmingCraft/assets/39553613/cf80141b-1730-4815-9a3b-e701ed820743)
- The Chunk system allows the game map to be divided into several cubes of the size 10 x 10 x 10. A single Chunk **can be activated as needed**, conserving system resources.

- A single Chunk Tile calculates the grid it occupies in the [**Construction Script**](https://github.com/Caishangqi/CharmingCraft/blob/afe8917e7482ab9eae9adc91169e57414c760a2b/Source/CharmingCraft/Core/Resource/Chunk/LandChunk.cpp#L44) based on the chunk's size **(snapped to 100)**. These grid points **(Blue in graph)**, stored inside the Chunk, play a significant role in resource generation.

- The Chunk system has **integrated** the previously **Biome box area Actors**. Now, it's only necessary to allocate Biome data within a single Chunk, **eliminating the need to create Biome boxes** and adjust their sizes. After adjusting the Biome and world resource data, the Chunk will randomly generate resources upon activation.

- Because a Chunk records all the grid points it occupies upon creation, these snap-to-grid points can be easily used for ray tracing.
<p align="center">
<img src = "https://i.imgur.com/EF6t6WA.png">
</p>





![chunk-system](https://github.com/Caishangqi/CharmingCraft/assets/39553613/052ca797-7bb0-4865-a1c5-685c44a386f1)
<p align="center">
The new version of the Chunk system integrates the Biome Box Actor to manage and generate natural resources in Chunk units.
</p>

#### Resource Collision Enhance

- To avoid resource collisions or parts being suspended in air within a Chunk, the four corners of the bottom face of the box are used for **pre-generation** judgment.

- First, a point is randomly selected from the **GridPoints pre-stored in the Chunk** for pre-generation.

- The [**four corner coordinates**](https://github.com/Caishangqi/CharmingCraft/blob/afe8917e7482ab9eae9adc91169e57414c760a2b/Source/CharmingCraft/Core/Resource/Lib/GenerateTraceLibrary.h#L24) of the bottom face of the resource Actor's HitBox are used as starting points for ray tracing downwards. If the Z values of the HitResult's return are the same, it can preliminarily be judged as a plane.

- If the randomly selected point for ray tracing is not obstructed or is the expected terrain, then the Resource Actor can be generated.
### Equipment assembly

https://github.com/Caishangqi/CharmingCraft/assets/39553613/aa4a85df-a49b-488b-8887-5868ce0d31ec

- Just like how people make weapons, you can use any material to create different weapon parts and assemble them
  together

### Smart enemy AI

https://github.com/Caishangqi/CharmingCraft/assets/39553613/5bc09e55-ef8d-457f-99bc-cf73020b48cf

- Many enemies will interact with the scene and they will use their best advantage to try to defeat you
- Current enemies: Slime, Skeleton, Skeleton Shaman

### Flexible action system

https://github.com/Caishangqi/CharmingCraft/assets/39553613/e0d9ac26-1a67-4d21-806d-84155a471d44

- Although it is a TopDown perspective game, you can click on the target to attack or hold down shift to attack to
  specify the click direction.
- Different weapons have different attack animations, and the speed of these attack animations depends on your character
  and equipment attributes.

### Scene switching

https://github.com/Caishangqi/CharmingCraft/assets/39553613/eda346ab-ff80-4fdc-a8c1-e8a36b4b55ba

- When you walk into the room from the outside, the scene switching will be smooth and stylized.

### GAS, Buff and RPG elements

- Use the chain of responsibility design pattern to handle multiple types of damage. The damage is packaged into HitData
  by struct.
- Use BuffInfo, BuffData, BuffHandler to callback BuffModels implement Buff System.
- Magic, arcane, and some weird stuff...

#### The skill binding RPG HUD

![2024-01-22 22-13-31](https://github.com/Caishangqi/CharmingCraft/assets/39553613/4bdc2f1f-f216-413e-92ca-e760df3e8223)

#### Current Skills

| Skill Name               | Can Level Up | Resource Cost  | CoolDown | Basic Damage             | Description                                                                                                                                                                  |
|--------------------------|--------------|----------------|----------|--------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Parry                    | Yes          | None           | `2`      | Depends on Projectile    | Parry and Reflect the ranged attack                                                                                                                                          |
| Sword Draw Slash         | Yes          | **Mana** `20`  | `5`      | Depends on Weapon        | Draw weapon forward and perform a long-range slash, dealing 1.5 times weapon's hit damage.                                                                                   |
| Sneak                    | Yes          | **Mana** `50`  | `5`      | `110%` **Critic Damage** | Causing the enemy to lose their target, ensuring a critical hit on the next attack.                                                                                          |
| Sprint                   | Yes          | None           | `3`      | None                     | Dash a distance, and become immune to some damage during the dash.                                                                                                           |
| Arcane Endowment         | Yes          | **Mana** `75`  | `10`     | Depends on Buff          | Randomly select 3 `(+)`buffs from the Buff pool, lasting for 30 seconds                                                                                                      |
| Enhanced Arcane Missiles | Yes          | **Mana** `150` | `2`      | `30%`   **Magic Damage** | launch arcane missiles toward the mouse pointer direction, with increased damage for each shot, castable up to 3 times, with the third shot causing AOE damage and stunning. |

#### Buff System

- Support Stack Buff, Forever Buff.
- User could customize buff atttributes through Duration, Tick time, or pass a **TMap** contain [**internal Data**](https://github.com/Caishangqi/CharmingCraft/blob/2fc42016c812861645d0e85a4a690637bda0d7ff/Source/CharmingCraft/Core/Buff/UBuffData.h#L39).
- 3 Buff time **update** choices: `Add`, `Replace`, and `Keep`.
- 2 Buff **remove** Stack choices: `Clear` and `Reduce`.
- 7 Customize [**Buff Callback**](https://github.com/Caishangqi/CharmingCraft/blob/2fc42016c812861645d0e85a4a690637bda0d7ff/Source/CharmingCraft/Core/Buff/UBuffData.h#L55): `On Create`, `On Remove`, `On Tick`, `On Hit`, `On Be Hit`, `On Kill`,
  and `On Be Killed`.
- User
  could [**implements different Callback**](https://github.com/Caishangqi/CharmingCraft/blob/2fc42016c812861645d0e85a4a690637bda0d7ff/Source/CharmingCraft/Core/Buff/Modules/ModifyPropertyBuffModel.cpp#L14)
  to customize buff behaviour.

![BuffSystem](https://github.com/Caishangqi/CharmingCraft/assets/39553613/08a67844-f027-446a-a95f-02f6104415c1)

| Buff Name           | Icon                                                                                                                                    | Allow Stack | Default Duration / Tick | Default Max Stack | Description                                                                                                                                                                          |
|---------------------|-----------------------------------------------------------------------------------------------------------------------------------------|-------------|-------------------------|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Burning             | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/710ec398-ff5b-45ef-a16f-6fc2059b838f" height="200%" width="200%"> | Yes         | 10    / 1               | 5                 | Inflicts magic damage over time on the tick unit and reduces the unit's life regeneration.                                                                                           |
| Damage Enhance      | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/d5c8a7b5-9a32-4608-a8b6-7999d18cf8a3" height="200%" width="200%"> | No          | 10    / 0               | 1                 | Increases the bearer's attack power.                                                                                                                                                 |
| Stealth             | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/4aad4657-df58-4687-bc9e-6c22826b9391" height="200%" width="200%"> | No          | 20 / 1                  | 1                 | Cannot be detected by enemies; becomes ineffective after the bearer attacks.                                                                                                         |
| Spawn Down          | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/29b838ff-c6b3-48b6-b4de-12b2483f24be" height="200%" width="200%"> | Yes         | 30 / 0                  | 5                 | Reduce Nearby Enemy Spawn Rate                                                                                                                                                       |
| Negative Resistance | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/a8bdc125-cbb7-4e26-a644-764373c1f4b1" height="200%" width="200%"> | No          | 60 / 0                  | 1                 | Immune to Negative Effects, Excluding Control                                                                                                                                        |
| Frozen              | <img src="https://github.com/Caishangqi/CharmingCraft/assets/39553613/0a3a42aa-100c-4c24-b4eb-bb34a6d86347" height="200%" width="200%"> | Yes         | 10 / 1                  | 5                 | Slow the bearer, freeze the bearer when the maximum stacks are reached. If damaged by physical attacks while frozen, it inflicts a percentage of maximum health as **magic** damage. |                                                                                            |

### Player Select Menu (Ring DLL)

https://github.com/Caishangqi/CharmingCraft/assets/39553613/d3d29d4b-3049-4419-b735-747bfdb202fe

- Use Ring Structure Double link list to manipulate player save slot and Update preview render.
- Support player create, delete, select, and switch.

#### Ring Double Link List

![Render Ring DLL](https://github.com/Caishangqi/CharmingCraft/assets/39553613/db802d62-68db-451a-81e4-b621f2d87f9b)

#### Save Slot Structure

- SaveGames
    - save - `uuid`
        - _LevelData.sav_
        - _PlayerData.sav_
        - _ProgressData.sav_
        - _RealmData.sav_
        - 
### Resource Gathering System

The Resource Gathering System enables players to collect various resources in the game by inheriting from [ResourceEntityActor](https://github.com/Caishangqi/CharmingCraft/blob/main/Source/CharmingCraft/Core/Resource/Gather/ResourceEntityActor.h) to define resource entities that appear in the game. Additionally, the game's Biome system will refresh resources within a specified area over a period of time, ensuring a certain quantity is maintained. Structure See [here](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/resource-system-structure.md).

![Resource Gathering System](https://github.com/Caishangqi/CharmingCraft/assets/39553613/b4e8b2ca-508e-4b02-b186-36732db0fd0f)

### Levels

![Spawn](https://github.com/Caishangqi/CharmingCraft/assets/39553613/b2fe8dd6-fe09-480e-84ab-e2dba4aedb46)
<p align="center">
World Spawn - Build using blender and Unreal Cube grid tool
</p>
<p align="center">
<img src = "https://i.imgur.com/EF6t6WA.png">
</p>

![085b835d6aa2bbfdfa9b2f7ca4df50b8](https://github.com/Caishangqi/CharmingCraft/assets/39553613/98fb8dec-facb-40ec-b8a4-9ddd14db5ac8)
<p align="center">
Pub Interior - Build using blender and Unreal Cube grid tool, Design reference 《Unpacking》

</p>

## Progress

**Stability**: 🟩 Stable / 🟨 Unstable / ❔ Not Test / 🟥 Failed

- Implementation of projectile blueprint templates based on C++ 🟩
- Interactive interface and character interaction functionality 🟩
- Chest opening feature and animation implemented through the interactive interface 🟩
- Health bar decay implemented using event binding and UI parameter exposure 🟩
- Digital animations realized through the animation system 🟨
- Dynamic materials based on mathematical functions 🟩
- Implementation of chests and keys using GameTags 🟩
- Block skill (R key) implemented using GameTags 🟩
- Material highlight and glow upon impact 🟩
- Interactive item highlight and player obstruction glow 🟩
- Inventory system and item prototypes 🟩
- Armor forging station 🟩
- Rendering 3D items in 2D 🟩
- Item assembly mechanism, crafting items from different materials 🟩
- Weapon assembly, assembling different types and materials of parts for various weapon parts ❔
- Attack animations and ranges based on different weapon types 🟩
- Dota-style mouse movement attack system, including character rotation and new stationary attacks 🟨
- Damage number animations based on player's attack direction 🟩
- Comprehensive AI system, including EQS, Behavior Trees, Decorators, and Services 🟩
- Scene transitions implemented using scene streaming 🟩
- UI bind GAS system 🟩
- Buff System Include BuffData, BuffInfo, BuffHandler, and BuffModel (Callback) 🟩
- Game Start UI and World Select UI 🟩
- Game Serialization System (Json, FString) to UObject ❔
- Game resource system with regenerated resource 🟩
- Resource fracture mechanism implement by Chaos Destruction system 🟩
- GameMode system that support key mapping base on different ganemodes 🟩
- Build system and visual enhancement support place, rotate and break 🟩
- Chunk Based Resource Generation 🟩

## Content and Mechanism

- [Attribute Multiplier and Damage Calculator](https://github.com/Caishangqi/CharmingCraft/wiki/Attribute-Multiplier-and-Damage-Calculator)

## Coming Soon / TODO

| Context                                                   | Priority | State |
|:----------------------------------------------------------|:--------:|:-----:|
| Game Start UI and World Select UI                         | Highest  |   ✅   |
| Game context serialization                                | Highest  |   ✅   |
| Chunk and build system                                    |   High   |  ✅   |
| Skill indicator Component                                 |   High   |  📝   |
| Complete attribute UI                                     |  Normal  |  ✅   |
| Per Item Ability System                                   |  Normal  |  📝   |
| Quest system with related NPCs                            |  Normal  |  📌   |
| Random dungeons and sub-worlds are loaded non-streamingly |  Normal  |  📌   |
| Resource collection system, ores, trees, farmland         |  Normal  |  ✅   |
| Expand the Level to 1000 x 1000                           |   Low    |  📌   |
| Biome: Respawn of monsters, resources, creatures          |   Low    |  ✅   |
| Developing an engaging storyline                          |  Lowest  |  📌   |
| Reset inventory UI and drag method                        |  Lowest  |   ✅   |

## Awaiting Improvement

- If the player cancels the interaction, ray tracing will still be performed, causing widespread resource actror damage.
- Fixing stuck and jittery issues when interacting with items on high ground (**Fixed**)
- Correct movement behind buildings when obstructed (Ray Tracing)
- Dynamic pathfinding improvements, refreshing available routes when players destroy blocks or interact with items (**Fixed**)
- Changing item dropping from generation to a throwing action
- Rendering 3D items into 2D images requires manual placement of RenderTargetActor in the world, otherwise it fails (**Fixed**)
- The `OnHit()` method of weapons is determined by the weapon type, consider passing in a weapon class template for the
  interaction component to execute the template class method for **HitData** transmission (**Fixed**)
- Some User Widget component can create template for example, give all widget an close button that bind a function pointer.
- Combind ItemAbility System to part of Build Module, allow Ability data structure contained visual enhancement object.
## Project Structure

### Asset Structure

- Assets
    - models
    - textures

### Code Structure

- Source
    - **Core**  (Game Logic and Mechanism)
      - Attribute (RPG attribute system)
      - Buff (RPG buff system)
      - Builds (Build System and Block)
      - Container (Widget and Container hold itemstack)
      - Damage (RPG Damage system)
      - Decoration (Decoration system)
      - Entity (Drop Entity and Creatures template)
      - GameMode (Gamemode for different cases)
      - Interact (Interact system)
      - Item (Item system and Inventory)
      - Log (Log system and naming)
      - Save (Save system and Seriliazation)
      - Skill (RPG skill system)
      - UI (UI handler and UI template)
      - World (World system)
      - Resource (Resource System)
    - Controller (Different Controller)
    - Camera (Different Camera)
    - **Content** (**Content** that Extend from **Core** Mechanism)

## Concepts, Design Patterns, and Implementation Principles

The following content is written based on the technology used in the project. It does not cover all aspects of Unreal
Engine. Unfinished records are not displayed on the main README but are shown in the
project's [Wiki](https://github.com/Caishangqi/CharmingCraft/wiki).

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
- [Buff System](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/impl-meel-attack.md)

### Errors and Solutions

- [GameSave DEP (ZH_CN)](https://github.com/Caishangqi/CharmingCraft/blob/main/Page/gamesave-dep.md)

## WorkFlow

### Animation Assets

- [Fast Create Animation Asset](https://www.mixamo.com/)

### Components and Native

## Resource

- Link is [Here](https://www.modongwang.com/)
