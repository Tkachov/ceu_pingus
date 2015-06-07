# Week 3 (08/06--15/06)

## What I was supposed to do the past week?

Work on more actions;  
May be port some code from classes which control the game (Server, World, etc);  
May be transfer SDL events directly to Ceu and react on some of those in already ported classes.

## What I actually did the past week?

## What I'll do this week?

# Week-2 (01/06--07/06)

## What I was supposed to do the past week?

Start porting Pingus;  
Falling, normal walk, maybe digging.

## What I actually did the past week?

* ported a part of Pingu, so it can start actions inside Ceu;
* ported 5 actions' `update()` (falling, walking, digging, exploding and floating).

Less important stuff:
* decided to remove countdown_action from C++ Pingu as it was never used;
* made a little clean-up with renaming and moving code around;
* converted some .jpg backgrounds to .png;
* fixed compiler to WRN about "pointer across `await`".

## What I'll do this week?

Work on more actions;  
May be port some code from classes which control the game (Server, World, etc);  
May be transfer SDL events directly to Ceu and react on some of those in already ported classes.

# Week-1 (25/05--31/05)

## What I was supposed to do the past week?

First week of the project.

## What I actually did the past week?

I've converted .jpg to .png and .it to .wav.

I've fixed fade_over(), at least it looks like a transition effect now.

Added C++-to-Ceu proxy events and a few Ceu classes which react to those.

Ported some mouse reacting behavior of MenuButton, ArmageddonButton and 
ForwardButton.

## What I'll do this week?

Start porting Pingus?
Falling, normal walk, maybe digging?
