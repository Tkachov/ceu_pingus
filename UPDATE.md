# Week 7 (6/07--12/07)

## What I was supposed to do the past week?

Remove C++ `WorldObj` instance from Céu `IWorldObj`;
Port more of `World` (port all of it, if there is time, because it requires porting other classes);
Add a Céu wrapper for `Sprite`.

## What I actually did the past week?

## What I'll do this week?

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
