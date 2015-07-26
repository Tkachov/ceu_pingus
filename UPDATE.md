# Week 10 (27/07--2/08)

## What I was supposed to do the past week?

* port screens and components which left;
* ScreenManager?

## What I actually did the past week?

## What I'll do this week?

# Week 9 (20/07--26/07)

## What I was supposed to do the past week?

* port screens, components, worldmap classes.

## What I actually did the past week?

* ported screens:
	* StartScreen;
	* ResultScreen;
	* WorldmapScreen;
	* PingusMenu;
	* StoryScreen;
	* Credits.

* ported components:
	* ButtonPanel;
	* MenuButton.

* ported worldmap classes (all but structs for graph/path/story representation):
	* Worldmap (=> PingusWorldmap);
	* Drawable (=> Dot, LevelDot, Pingus, PathDrawable, SpriteDrawable, StoryDot).

## What I'll do this week?

* port screens and components which left;
* ScreenManager?

# Week 8 (13/07--19/07)

## What I was supposed to do the past week?

* work on `GameSession`:
	* port what's possible to port;
	* port `Smallmap` and `Playfield` components (are used in `GameSession`);
	* port `Server` (is used in `GameSession` and `DemoSession`).
* may be work more on `Sprite` wrapper and components.

## What I actually did the past week?

* ported `GameSession` as far as it could be done:
	* `SmallMap` and `Playfield` ported;
	* ported `Server` almost as far as it could be done;
	* `WorldObjFactory` ported into `World`.
* worked more on `Sprite` wrappers and autonomous sprites:
	* `Sprite2` - Céu implementation of C++ `SpriteImpl`;
	* `Sprite3` - autonomous sprite implementation which reacts on global `draw` and `update` events;
	* simple cache in C++ `FramebufferSurface`;
	* ported `Direction`;
	* `RightLeftSprite` - Céu replacement for C++ `StateSprite` (uses `Sprite3`);
	* used `Sprite2`, `Sprite3` and `RightLeftSprite` everywhere (actions, world objects);
	* documented that as good example of code transformation.

What else:

* switched to new version of Céu `recurse` compiler;
* some small fixes (like using `loop` to iterate vectors);
* ported `ButtonPanel` of `DemoSession`
* ported `LinearMover` & `PinguCollider` (used in `Faller` and `Bomber` actions) - game lagged because of lots of dynamically spawned `PinguCollider` organisms;
* removed state machines in some world objects.

## What I'll do this week?

* port screens, components, worldmap classes.

# Week 7 (6/07--12/07)

## What I was supposed to do the past week?

Remove C++ `WorldObj` instance from Céu `IWorldObj`;
Port more of `World` (port all of it, if there is time, because it requires porting other classes);
Add a Céu wrapper for `Sprite`.

## What I actually did the past week?

* Removed `WorldObj` completely (ported into `IWorldObj`);
* Ported `World` completely;
* Added a `Sprite` wrapper and replaced `_Sprite&?` with `Sprite` in world objects code and other places.

What else:

* Worked on bad code transformations (fixed some);
* Worked on some `GUI_Component` stuff:
	* added `x` and `y` in `mouse_move` event;
	* added `EventProxy` for `draw` and `update` events;
	* ported `Playfield`'s `mouse_move` and `update`;
	* ported `PingusCounter`;
	* completely ported `Armageddon`, `Forward` and `Pause` buttons;
	* ported lots of `Smallmap` reactions to `GUI_Component` events.
* ported `Server`'s armageddon event and related code;
* ported `GoalManager`;
* added `DemoSession` and `GameSession` classes;
* removed C++ `PinguHolder`;
* ported `SmallMapImage`.

## What I'll do this week?

* work on `GameSession`:
	* port what's possible to port;
	* port `Smallmap` and `Playfield` components (are used in `GameSession`);
	* port `Server` (is used in `GameSession` and `DemoSession`).
* may be work more on `Sprite` wrapper and components.

# Week 6 (29/06--5/07)

## What I was supposed to do the past week?

Port world objects;
Sprites;
Document bad and good examples of ported code?

## What I actually did the past week?

Ported all world objects;
Ported `World`'s part where it contains and iterates over `WorldObj`s;
Documented bad and good examples of ported code.

## What I'll do this week?

Remove C++ `WorldObj` instance from Céu `IWorldObj`;
Port more of `World` (port all of it, if there is time, because it requires porting other classes);
Add a Céu wrapper for `Sprite`.

# Week 4 and 5 (15/06--28/06)

## What I was supposed to do the past weeks?

Port actions and Pingu completely (this will require partial porting of other classes).
Transfer SDL events?

## What I actually did the past weeks?

Ported actions and Pingu completely.
Moved some world objects partically.
World, Server, ServerEvent and some other classes ported a little bit.

## What I'll do this week?

Work on world objects;
Sprites;
Document bad and good examples of ported code?

# Week 3 (08/06--14/06)

## What I was supposed to do the past week?

Work on more actions;  
May be port some code from classes which control the game (Server, World, etc);  
May be transfer SDL events directly to Céu and react on some of those in already ported classes.

## What I actually did the past week?

* closed issue #5 (BomberAction state machine);
* ported all actions `draw()` and `update()` to Céu;
* removed `update()` and `draw()` from C++ Pingu and PinguAction;
* completely ported all the actions but Basher, Blocker, Bridger, Climber, Faller and Floater.

Less important stuff:
* removed Smashed and Telepored;
* converted sounds and some textures;
* added `type`, `CATCHABLE` & `CHANGE_ALLOWED` fields in PinguAction;
* made a StateSprite wrapper and added some functions to work with Sprite, CollisionMask, Sound, WorldObj and Movers::LinearMover;

## What I'll do this week?

Port actions and Pingu completely (this will require partial porting of other classes).
Transfer SDL events?

# Week-2 (01/06--07/06)

## What I was supposed to do the past week?

Start porting Pingus;  
Falling, normal walk, maybe digging.

## What I actually did the past week?

* ported a part of Pingu, so it can start actions inside Céu;
* ported 5 actions' `update()` (falling, walking, digging, exploding and floating).

Less important stuff:
* decided to remove countdown_action from C++ Pingu as it was never used;
* made a little clean-up with renaming and moving code around;
* converted some .jpg backgrounds to .png;
* fixed compiler to WRN about "pointer across `await`".

## What I'll do this week?

Work on more actions;  
May be port some code from classes which control the game (Server, World, etc);  
May be transfer SDL events directly to Céu and react on some of those in already ported classes.

# Week-1 (25/05--31/05)

## What I was supposed to do the past week?

First week of the project.

## What I actually did the past week?

I've converted .jpg to .png and .it to .wav.

I've fixed fade_over(), at least it looks like a transition effect now.

Added C++-to-Céu proxy events and a few Céu classes which react to those.

Ported some mouse reacting behavior of MenuButton, ArmageddonButton and 
ForwardButton.

## What I'll do this week?

Start porting Pingus?
Falling, normal walk, maybe digging?
