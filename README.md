# Haven Chart Editor

Haven is a tool for creating charts for Sound Voltex-like games.

Most of the contents of this readme are subject to change during
the development of Haven and its sister projects.
If you have any questions about details or terms, either open and
issue for discussion or create a pull request with the desired changes
and a comment detailing the reasoning.

MOST OF THIS WILL GET THROWN IN A WIKI LATER, DON'T WORRY.

## Terminology

The preffered terms for things are likely to change by community preference,
but as of now these are how different parts of the editor or gameplay should be described.

- Length: the length of the highway as a percentage of its total length.
This value is bounded to [0, 1]. It doesn't change the actual length,
but only the visible portion.
The effect is similar to a toggle, but all playables are hidden past the length cutoff instead.
Scroll speed is the same as if the highway length were unchanged.

- Offset: The translation along the X axis of the highway at the critical line.
This is how "side zoom" is implemented, and is nothing more than a simple translation.
One unit of offset likely to equal half a highway width, such that an
offset of 1 places the center of the highway where the right edge used to be.

- Pitch: The angle of the highway around the X axis at the critical line.
This is how "top zoom" is implemented, and this term should be preferred.
One unit of pitch equates 10 degrees of rotation and is unbounded,
such that a value of +/-36 is a full rotation back to its origin.
The highway is free to rotate endlessly in each direction.
See SDVX III's April fools day chart for an example of that in action.

- Roll: The angle of the highway around the Z axis.
This is the kind of rotation that lasers apply during gameplay.
The charter can also control the base amount of roll applied to the highway,
where one unit of roll is 360 degrees of rotation and is unbounded.
See SDVX III's April fools day chart for an example of that in action.
This control is aptly called the "base roll" of the highway.

- Roll Intensity: how strong the laser roll is applied.
There are 4 values, usually called *zero*, *normal*, *bigger*, and *biggest*.
*Normal* is the default value and there's likely no need for more than these.

- Roll Keep: when roll keep is enabled, the applied laser roll goes 
through a max function rather than being used raw.
This applies differently depending on which way the roll is first applied.
The sign of the roll is also kept, a negative roll while keep is enabled will never become positive, even if the magnitude of the roll is greater.

- Spin: When the highway performs a complete 360 roll animation, usually in response
to a slam being played. The duration can be changed by the charter.
Spins have a unique animation path and can control other aspects of a chart, such as 
the background, in ways which simply changing the base roll cannot accomplish.

- Stop: This is when the playable objects on the highway *stop* scrolling towards the player.
The time that a stop occupies is compressed and invisible on the highway.
It's best practice to not have any significant gameplay changes during a stop,
as a player cannot perceive timing during them.

- Swing: Similar to a spin, except the highway rocks (read: rolls) back and forth starting
at around 80 degrees and coming to a halt slightly after a full swing.
The duration can be changed by the charter.
The intensity of a swing should likely be configurable by the charter.

- Toggle: The highway fades in or out of view, but all playables
can still be seen by the player.

- Zoom: The distance of the critical line from the camera.
This is how "bottom zoom" is implemented, and this term should be preferred.
Due to 3D perspective, zooming should have an exponential effect on the
distance from the camera in a form similar to the following:

```
when ZOOM < 0 // zooming out
   ADDED_DIST = X ^ -ZOOM - 1
else
   ADDED_DIST = BASE_DIST * (X ^ -(ZOOM ^ Y) - 1)
```

where ADDED_DIST is how far to translate, in the appropriate direction, 
from the base distance (BASE_DIST) when ZOOM is 0 and X and Y are 
arbitrary values to make things look pretty.
Basically when zooming AWAY from the camera the change in distance gets exponentially greater and
when zooming towards the camera that same change in distance (now in the other direction) gets exponentially smaller, and now also in terms of the base distance from the camera at a zoom value of 0 to more easily avoid clipping the near plane.
X affects the total "power" of a zoom unit and Y additionally tweaks 
zooming towards the camera as becoming exponentially close to the camera 
yields negligible results for even small values.
The direction of a zoom is always the vector from the center of the 
camera to the critical line so that the critical line may always be 
placed at the same Y position on the players screen despite any zooming.

## Misc. Details

- Zoom, pitch, offset and base roll are all controlled as a linear sequence of control points
whose values are interpolated smoothly. This is linear by default, but other interpolation
methods may be supported in the future (for example, it's not uncommon to see a zoom applied
too a strong sound in the song, where the highway bounces either away from or towards the camera.
An elastic ease would do wonders here.)
