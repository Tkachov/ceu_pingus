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

### Autonomous sprites

Written already, but yet experimental, `Sprite3` and `RightLeftSprite` are promising classes for code simplification.

All we need to play animation is declare a variable and initialize it's fields.

**Old `StateSprite` C++ wrapper**
```
    var StateSprite sprite;
    load_file_directions(sprite, "/exit/");

    par do
        every gc in pingu.e_DRAW_CALLED do
            _gc_color_draw2(gc, sprite.get(pingu.direction().value), _toVector3f((call/rec pingu.get_pos())));
        end
    with
        every global:e_PINGU_UPDATE_ALL do
            sprite.get(pingu.direction().value):update();

            if sprite.get(pingu.direction().value):is_finished() then
                escape _A_EXITED;
            end
        end
    end
```


**New `RightLeftSprite`**
```
    var RightLeftSprite sprite with
        this.pingu = pingu;
        this.pos_giver = pingu;
        this.left_name = _new_String(_concat2(pingu.get_owner_str(), "/exit/left"));
        this.right_name = _new_String(_concat2(pingu.get_owner_str(), "/exit/right"));
    end;

    await sprite.finished;
    escape _A_EXITED;
```

## Bad ones

### Having `PTR2REF` and `deref` hacks

Sometimes we have to use pointers. So we need some means to say Céu "no, that's fine", "that attribution is ok", "this is a valid pointer/reference", etc.

If C++ methods are getting reference arguments, even having a reference in Céu won't be enough. At the same time, we can't dereference a reference (even though it's a pointer inside and we actually want to dereference it), so we need a `deref` define as well.

### `struct`s passed as event parameters

Sometimes we need more than one parameter passed with event. For that I use special `struct`s, which contain all of these parameters.

That's just temporary code for C++-to-Céu interaction, though. Sometimes it's used because I was unable to call Céu methods from C++. I think that after porting this will be replaced with function calls and Céu events with multiple parameters.

### Doing things in exact order

In some cases we can't have a single event for all organisms as we have them ordered and thus we need them to draw/update/etc in that order.

For example, we have `PINGU_DRAW_WALKER` and `PINGU_DRAW_OTHERS` events, because we want to draw non-Walkers on top of the Walkers, because they probably need more player's attention than Walkers.

**UPD:** `draw` requests are sorted before actual rendering and I decided that `update` could be done in any order.

### No "none" value in actions enum

In Pingus C++ code `PinguAction` smart pointers were used to determine whether an action was set or not. If it's `null`, there is no action set. Otherwise, we can get action's type.

As it's using only action's type, there is no real need of having a pointer to an object. We can have a enum variable for that. But as there is no `A_NONE` value, we have to use a boolean value to determine whether it's set (and that means two variables where we could use one).

Having a special "none" value can give us more headache, though. Can a Pingu change its action to "none"? Or what should it do if its action is "none"?

### Having `WORLDOBJ_STARTUP`

That exact event should be passed to a world object only once. But as it's emitted in C++, we can't make that a Céu class method yet. That means each time there is a new world object, all others will get an event and ignore it, as it's not for them. I'm not sure if that world object even have to get such event, so I can't just move it out of `par` section for organism to first await his startup event, and then function as usual.

### Particles holders and `GroundMap` ports

These keep a `std::vector` of special particle `struct`s or `MapTile` `class` and iterate over it during `DRAW` and `UPDATE` events. Instead of doing something like

```
	loop i in v.size() do
		...
	end
```

I just left all code in C++ as global (in a namespace) functions. Now Céu organisms call these, passing inner fields (like `vector` or some sprites) as parameters of these functions.

I needed the classes ported to remove `WorldObj`, so that was the simplest solution. I'll do an actual port of these later.

**UPD:** particles holders are ported; `GroundMap` is left in C++.

### `Container`

The `Container` class is needed to storage Céu organisms and iterate over that collection inside Céu.

I tried the approach with Céu `SortedList` class, which was a linked list of `Node` organisms, and it actually worked... more or less. Somehow `loop` iterations were stopping and then continuing after a few seconds. Usually it just crashed with segfault after first stop.

So, when C++ iterates over whole collection and calls `update()`, it's OK. When C++ iterates over it and emits Céu `UPDATE` events, that's also OK. When C++ emits one `UPDATE` event and in Céu we do a `loop` and emit `e_UPDATE` events of organisms themselves, that either stops (not all organisms are updated) or crashes.

That's why I decided that `Container` will have an `iterate(int event)` method, in which C++ will iterate over storaged pointers to Céu organisms and emit passed `event`. As we usually want to iterate a collection to notify about some event we just been notified about, it becomes something like that:

```
par do
    every WORLD_UPDATE do
        ...
        container.iterate(_CEU_IN_WORLD_UPDATE_OBJECT);
    end
with
    every object in WORLD_UPDATE_OBJECT do
        emit object:e_UPDATE;
    end
end
```

Yes, it guarantees that **all** objects are updated in **necessary order**. But as `Container` can't emit an event of object itself, we have to add more Céu events. More than that, if we want to pass a parameter, we have to remember it in a local variable and use it in another `every` block (actually, that can be fixed by adding a special "package" `struct`, which would contain both current object pointer and passed parameter).

**UPD:** `Container` is now used for storaging only. `draw` and `update` are more global now, and objects themselves react to these. `e_DELETE` event still emitted to each object in a loop, though.