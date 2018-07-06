-- Wizznic! --
 - An implementation of the arcade classic Puzznic,
   for Gp2X Wiz, Linux and Windows.

-- Index --
1.0 Wizznic Info and License
1.1 Objective
1.2 Controls and Keys
1.3 How do I clear the highscore?

2.0 User created content
2.1 How to make new levels
2.2 How to submit my level for inclusion into the official game ?
2.3 How to make new themes
2.4 Sound files needed!

3.0 Contributors and Credits

4.0 Frequently Asked Questions (FAQ)

------------------------------------

1.0 SDL-Ball Info
Author: Jimmy Christensen
Project page: https://sourceforge.net/projects/wizznic/
Web site: Please help this project out by making a website.

License:
Code, Graphics, Levels are GPLv3
See data/media-licenses.txt for soundfiles (GPLv3)

Wizznic is my hobby project, I'm using it to learn C and SDL,
don't flame me for my ugly code, if you don't like it, dont
read it.. :)

------------------------------------

1.1 Objective
As the original game, your mission is to clear the level of
bricks, this is done by moving the bricks about, when two or
more bricks of the same kind are next to eachoter, or on top
of eachother, they will disappear and points will be given.
The level has to be cleared before the time runs out, or you
will loose a life. If you realize that you made a mistake, or
ran out of time, quickly press "Menu" and "Retry" each life
gives you 4 retries. So it's better to retry than to loose a life.

------------------------------------

1.2 Controls and keys
On the Wiz:
D-Pad - Navigate menus, move cursor about.
X     - Select item in menu, select brick.
B     - Can also be used to select brick.
MENU  - Pauses the game and displays the menu.
Vol   - Adjust volume, the setting is saved.

On the Pc:
Arrows - Navigate menus, move cursor.
X      - Select item in menu, select brick.
B      - Can also be used to select brick.
Return - Pauses the game and displays the menu.
There's no way to adjust volume in the PC version, use your OS's settings.

------------------------------------
1.3 How do I clear the highscore?
Simply delete user.ini in the wizznic directory. (this also resets volume)

------------------------------------

2.0 User created content
I'm only one guy, and frankly, I tend to lose interest in projects when they are in a
fairly playable state... That does not mean that I won't come back to them and make more
content, but for the project to succeed, I really need some help creating content.
If you create a nice level (or many), some themes/background-images or sound effects, please
do write to me, I'd love to include them in the game (I reserve the right to discard content,
obviously)

2.1 How to make new levels
Levels are by far the most important aspect of this game, and everyone can do it!

Start a new game, press Menu, select "User Levels", and select "Create".
Use A and B to select brick-type (you can see the brick in the left cornor).
Move the cursor around with the DPAD, press X to place a brick. Press Y to delete a brick.
When you are done with your level, press SELECT to save it. Then press MENU to exit.
Now your level is in the list of user-levels, select it and press Y to play.

If you made a good level, you should tweak it's settings, (time, author name, and (optional) theme).
Ofcause you can just leave the name at "Unknown" if you don't want to tell the world who made that awesome
level. - To tweak the settings, open your level, it is in the wizznic/data/userlevels/ directory, open it
with a simple text-editor like Kate/Nano/Vi (Unix/Mac) or "Wordpad MFC"/Notepad++ (Windows).

The lines in the level-file must be less than 32 characters, they are as follows:
Author
Time in seconds
path/name to background image (inside wizznic/data/themes/)
path/name to theme (inside wizznic/data/themes)
The next 11 lines are the level data.

Okay, so you made a level! Great! Now the final step is to submit your level for inclusion in future
releases of the game, please do this, as it will help make the game more enjoyable for everyone!

------------------------------------
2.2 How to submit a level for inclusion in future releases
It's really easy, as you know, your level is placed in wizznic/data/userlevels/ and is called something like "userlevel0.wzp"
Simply go to this address:
https://sourceforge.net/tracker/?func=add&group_id=286702&atid=1216626

And attach your level-file to the tracker-item.

Thank you! :)

------------------------------------
2.3 How to make new themes
A theme consists of two parts: Background-images, and Tiles/Animations.
Levelfiles can request a background-image from theme Zebra, and use the Tiles/Animations from theme Giraffe.

Background-Images:
Background images are the simplest part of a theme, just create a 320x240 image, with your graphics, use an
existing board as a template, or use the template.png from the srcgfx folder.
You're done, now all you need is to submit your awesome background, and hope somebody will use it (I will!)
oh, you want to create some bricks that match it? Read on..

Tiles/Animations:
Main file: themename.png
There are two required files nessicary to make a functioning brick-set, that's the "themename.png" and
"themename-expl0.png" files.
"themename" is the name of your theme.. For instance "wood.png", copy a file from one
of the existing themes, and use that as a template, the first (cyan) and last brick(some other color) are reserved
don't touch them.
The rest of the bricks are self-explanatory.

Explosion file: themename-expl0.png
This is the explosion/destruct animation for the first brick (if this is the only file, then it will be used
for all bricks when they are destroyed), there are 16 frames in the file, after frame 8, the brick will no
longer be rendered. (the last 8 frames are rendered too), so if you want to make something that "covers" the brick,
use the first 8 frames for that.

Extra-Walls File: themename-walls.png
If you called your main theme file giraffe.png then your wall file have to be called giraffe-walls.png
You don't have to create this file, but if you do, it's simly some more wall-pieces.

2.4 Sound files needed!
I'm really awful at sound-work (worse than at coding or doing gfx, wow!!:P) so please, if you have the skills
and want to help me out, please have a look at the files in data/snd/ many of them are just a template "click" sound
and could be much better... If you make a sound-theme, I'm pretty sure it will be better than what I've got, and
I'll be happy to use your theme as the default sound-theme :)

------------------------------------

4.0 Contributors and Credits
As for now, I borrowed a couple of lines of code from the OpenJazz Wiz port (and imitated their control concept).
Other than that, I'm thanking Jesper Kollerup in advance for his future work on themes :)

------------------------------------

5.0 Frequently Asked Questions
Nobody asked any questions yet.
