# Quest-for-Crystal-Kingdom
The player is on a quest to retrieve a legendary crystal from a dangerous and enchanted forest. The forest is filled with enemies and obstacles, and the player must navigate through it to find the crystal.
Player will always start from (0,0) 

## Game Entities:
- Safe paths (C): Nodes where the player can move without restrictions.
- Obstacles (#): Nodes with costly weights; the player should avoid these.
- Your Path (-): Shows where your own path. 
#### Rewards:
- Jewels (J): +50 points to the score.
- Potions (P): +70 points to the score.
- Weapons (W): +30 points to the score.
#### Enemies:
- Dragon (&): Causes the loss of a Jewel and its score.
- Goblin ($): Causes the loss of a Potion and its score.
- Werewolf (@): Causes the loss of a Weapon and its score.
- Death points (%): Nodes that cause the player to die and restart the game from (0,0).
- Crystal (*): The goal point.

## Controls:
- A -> Move left
- W -> Move up
- D -> Move right
- S -> Move down
- Press one of these keys, then press enter. 
  
Example of starting field:
![DS_proj](https://github.com/user-attachments/assets/5bb6d4ac-773d-4710-a745-4bbfbf09eac0)
