# no-reload

* Name:
  No-reload / Infinite ammo
* Type:
  Gameplay hack
* Description:
  No-reload allows more rounds than the regular magazine size to be fired from any weapon without any reload sequence. Quite a simple hack with a simple method of detecting. Other factors are taken into account such as dual-wield.
* Detection Method:
  Each time a player fires a shot, a variable is incremented if the variable's value exceeds the max ammo for that weapon, the player is marked for report. Ammo count is reset when the player switches weapons to reload or reaches the end of their magazine and reloads automatically.
* Callback:
  OnAntiCheatNoReload(playerid, roundsfired)
* Author:
  Southclaw

## Installation

Simply install to your project:

```bash
sampctl package install samp-anti-cheat/no-reload
```

Include in your code and begin using the library:

```pawn
#include <no-reload>
```

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.
