# [PROI Project L23] - Dueling Drifters

## Description
Dueling Drifters is a 2D car game where you can compete with your friends in a duel or tag match. The game is written in C++ with SFML library. The game is still in development, so there are still a lot of bugs and missing features. If you want to contribute to the project, please contact us.

## How to play
* There are two game modes to choose from:
  * Duel mode: two players compete against each other on the map. Whoever be pushed out of the map first loses this round. The first player to win predetermined number of rounds wins the game.
  * Tag mode: In this mode, map border became a wall and there is a  **flag** ![Flag](/assets/images/items/flag.png) in the center of the map. The goal is to capture the flag and hold it until the end of the round. You can steal the flag from your opponent by touch him. At the moment the clock reaches zero, the player who has the flag wins the round. The first player to win predetermined number of rounds wins the game.
* The developers of the game think that the game isn't "hard" enough, so they add ton of item with unique effect randomly on the map. If your car touch it, who knows what will happen... Actually, we know:
    * ![Speed Up](/assets/images/items/speedOrb.png) **Speed Up:** Your car will be faster for a short period of time.
    * ![Bomb](/assets/images/items/bomb.png) **Bomb:** Your car will explode and you will be pushed away to the opposite direction of the explosion.
    * ![Dash](/assets/images/items/dash.png) **Dash:** Your car will be pushed forward by some magic force. Look out for the direction of the arrow.
    * ![Opponent Slow](/assets/images/items/opponentSlow.png) **Opponent Slow:** Your opponent will be slower for a short period of time. Catch me if you can!
    * ![Reverse](/assets/images/items/reverse.png) **Reverse:** This is actually a bottle of alcohol to make you drunk. You try to go forward and hit your opponent but drive backward and fly out of the map instead.
    * ![Stun](/assets/images/items/stun.png) **Stun:** Use the force to stun your opponent for a short period of time.
    * ![Swap](/assets/images/items/swap.png) **Swap:** Swap your position with your opponent. 