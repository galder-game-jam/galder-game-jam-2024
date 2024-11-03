## Style
- Retro 2D platformer - 2 player online VS mode.

## Gameplay
- Players collect coins - most coins wins when entering a portal.
- After a set time (ex: 1 minute) a portal opens. The player with most coins can enter this portal and then wins.
- Basic attach (melee) is free. If it hits the other player the other player loses x amount of coins. These must be picked up (5 sec cooldown until they can be collected)
- Hits should give knockback.
- Special attacks will cost a coin. These can be shooting or explosives etc. Will make the other player lose more coins if it hits.
- Online play: Should be able to play via network. First version: Local networking. Peer to Peer. Valve's networking library.
- Platform collision support: Jump through from bottom. Solid on top. May drop down from platform.

## Player abilities
- Jump: Two jumps
- Powerups

### Powerups
- May spawn every x seconds.
- Powerups overwrites each other if you pick up a new one.
- Powerup: Guns / grenades / Super jump

### Map structure
- Fixed size that should not make it hard for the players to find each other.

## Enemies
- Enemy moving back and forth on platform. Makes a player drop a some coins.
- Flying + grounded. Reuse enemies from previous GGJ with reskin?
