# UI Unreal Programmer - World of Warcraft UI
Developed with Unreal Engine 5

## Features

- [x] Main Menu - Separate Level (Map)

Main Menu should be set as a separate level (map) that loads some 
kind of a main UI manager. We can consider this manager as some static Object
that is accessible throughout the game. 

This manager should be responsible for lifetime of ingame widgets and screens.

Only one UI manager should be active at a time.

- [x] In-Game Mouse Controls 

Replace the default behavior by changing the enhanced input mapping. We should disable the default rotation towards movement.

- [ ] UnitFrames

Create two permanent widgets that represents the UnitFrame for the current player and current target. 

Target can be a different Character or an NPC. 

UnitFrames should be hooked into a callback scripts that are sending a feedback from the UI Manager. Either a separate event bus or delegate that will be invoking the events upon changing of the relevant stats on the player/character/target. 

- [ ] Inventory

Permanent widget that renders the UI Grid of the Current Player. Inventory is a logical data structure handled by scripts. Player UI Inventory only represents the data.
    
**Tooltips should be also implemented. Display a tooltip when hovering on top of the item.** 


UI Inventory should be updated only when the data changes.

- [ ] Nameplates

Dynamic widgets that are displayed when certain NPCs or Characters are nearby. Nameplates should be pooled in the UI Manager or a separate Nameplate manager that is responsible for the lifetime and object pooling of the nameplates.

- [ ] Minimap

Permanent widget that represents a satelite view of the current map with minimal graphic details. Minimap should be rendering a separate camera view that is looking from the top to the player's position. 

- [ ] Quest Log

Permanent widget that represents the current quests that the player has. Quest Log should be updated only when the data change and entries in the quest log should be pooled. Only entries are dynamic in terms of pooling. The actively displayed quest is refresh on the separate widget that is showing only a quest detail at the moment.

- [ ] Drag and drop dialogs + Tooltips

TODO!