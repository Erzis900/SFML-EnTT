# Player Entity

| Component | Data Type | Description                                      |
|-----------|-----------|--------------------------------------------------|
| Health    | Int       | The current health of the player.     |
| MaxHealth | Int       | The maximum health the player can have.     |
| Velocity  | Vector2f  | The speed at which the player is moving.     |
| Direction | Vector2f  | The direction in which the player is traveling. |
| Position  | Vector2i  | The current location of the player in the game world. |

# Enemy Entity

| Component | Data Type | Description                                      |
|-----------|-----------|--------------------------------------------------|
| Health    | Int       | The current health of the enemy.     |
| MaxHealth | Int       | The maximum health the enemy can have.     |
| Velocity  | Vector2f  | The speed at which the enemy is moving.     |
| Direction | Vector2f  | The direction in which the enemy is traveling. |
| Position  | Vector2i  | The current location of the enemy in the game world. |
| Target    | Entity    | The entity the enemy is currently targeting. |

# Hitbox Entity

| Component | Data Type | Description                                      |
|-----------|-----------|--------------------------------------------------|
| Source    | Entity    | The origin or entity that fired the hitbox.  |
| Speed     | Float     | The speed at which the hitbox is moving.     |
| Direction | Vector2f  | The direction in which the hitbox is traveling. |
| Position  | Vector2i  | The current location of the hitbox in the game world. |
| Damage    | Float     | The amount of hp it will substract from enemy entity. |
