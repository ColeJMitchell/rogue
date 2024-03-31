The monsters we are using will be Snake (S, dmg=3), Bat (B, dmg = 2), 
Hobgoblin (H dmg = 5), Emu (E dmg = 3), Zombie(Z dmg = 4), and Dragon(D dmg = 20).

We will need to implement movement as well, but instead of using using h, j, k, and l we will use the arrow keys for
a more intuitive experience.

Corridors will function the same as in the game except that they are being denoted as 
a # sign that expands permanently once a player moves through it.

Unlike the original game you will not regain health by passing time walking around

To simplify the game we will only have one type of potion which restores health.

There will be no player inventory or items that the player can pick up.

Combat will be the same with one round of combat when you encounter an enemy, but enemies will deal more damage.

There is no need to add stair cases because we are only making one floor so no need to implement the > action

Unlike the base game there will also be no traps, the only danger is the monsters.

Enemies will hit the player and immediately die if the player is on an adjacent tile.

Dragons will instantly kill players.

The amulet shown as A will end the game and print a win screen.

In order to end the execution the player presses q.

If the player health <= 0 the game will end and a death screen will be printed.

Rooms not explored by the player will be invisible.

In order to simplify the game the following actions will not be available, identify object, all diagonal movement,
print HP-raise average, using a wand, identifying traps, saving the screen, run that way, run till adjacent, throw 
something, examne/set options, redraw screen, search for trap/secret, go up/down staircase, print current weapon,
print current armor, print current rings, repeat last message, cancel command, save game, shell escape, fight till either of
you dies, print version number, eat food, read scroll, wield a weapon, wear armor, take armor off, put on ring, take
ring off, drop object, call object, fight till or near death, move onto without picking up, pick something up, 
inventory, inventory single item, quaff potion. 



 
