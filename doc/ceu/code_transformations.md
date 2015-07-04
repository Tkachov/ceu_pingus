# Code Transformations

## Good examples

### Pingu's actions

Now actions themselves don't have to use `set_action()` of Pingu to request the transition to another action. We can use `escape _A_NEW_ACTION;` for that.

World objects or other code may use `emit pingu.e_CHANGE_ACTION => _A_NEW_ACTION;` to change action.

### Single update event

Pingus/actions receive `PINGU_UPDATE_ALL`. That's not a common event for the whole game, but that's a start.

In C++, we had to pass the `update()` from one object to another, and in Céu we can just subscribe for appropriate event.

### World objects creation

In Pingus C++ code, we have a template factory for different world object classes.

Instead, I created a usual class which uses an `int` parameter as Céu event id. When factory's method is evoked, that event is emitted and all necessary information is passed with it. Céu `World` organism processes these events and spawns different organisms for different events.

### Typified world objects pools

In C++ we had a lot of factories and never knew the exact type of the object after it's created. All these objects were storaged in `vector<WorldObj*>`, and thus world objects like `Teleporter` or `SwitchDoorSwitch` which needed an object of exact `TeleporterTarget` or `SwitchDoorDoor` classes, had to `dynamic_cast` the pointer to check that.

Instead, as all organisms are spawned in one place, we can have typified pools of these organisms in `World`. It also contains functions to find an object with needed id.

That also simplifies iterating over a collection of objects with similar type:

```
            loop entrance in entrances do
                if entrance:owner_id == package:player_id then
                    ...
                end
            end
```

## Bad ones

### Having `PTR2REF` and `deref` hacks

Sometimes we have to use pointers. So we need some means to say Céu "no, that's fine", "that attribution is ok", "this is a valid pointer/reference", etc.

If C++ methods are getting reference arguments, even having a reference in Céu won't be enough. At the same time, we can't dereference a reference (even though it's a pointer inside and we actually want to dereference it), so we need a `deref` define as well.

### `struct`s passed as event parameters

Sometimes we need more than one parameter passed with event. For that I use special `struct`s, which contain all of these parameters.

And may be that's fine in case of C++-to-Céu interaction, because I was unable to call Céu methods from C++. But when we have to use these inside Céu - that looks even more weird. There's only one place where I had to use that, but there probably could be more.

`IPinguHolder` keeps `Pingu`s inside and can spawn those on demand. Unfortunately, we can't `spawn` in a function. As we have to pass more than one parameter, we have to use a `struct` for these and emit an internal event of `IPinguHolder`, passing it along.

### Doing things in exact order

In some cases we can't have a single event for all organisms as we have them ordered and thus we need them to draw/update/etc in that order.

For example, we have `PINGU_DRAW_WALKER` and `PINGU_DRAW_OTHERS` events, because we want to draw non-Walkers on top of the Walkers, because they probably need more player's attention than Walkers.

### No "none" value in actions enum

In Pingus C++ code `PinguAction` smart pointers were used to determine whether an action was set or not. If it's `null`, there is no action set. Otherwise, we can get action's type.

As it's using only action's type, there is no real need of having a pointer to an object. We can have a enum variable for that. But as there is no `A_NONE` value, we have to use a boolean value to determine whether it's set (and that means two variables where we could use one).

Having a special "none" value can give us more headache, though. Can a Pingu change its action to "none"? Or what should it do if its action is "none"?

### Having `WORLDOBJ_STARTUP`

That exact event should be passed to a world object only once. But as it's emitted in C++, we can't make that a Céu class method yet. That means each time there is a new world object, all others will get an event and ignore it, as it's not for them. I'm not sure if that world object even have to get such event, so I can't just move it out of `par` section for organism to first await his startup event, and then function as usual.
