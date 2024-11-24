  ___________________________________________ ________   
  \__    ___/\_   _____/\__    ___/\______   \\_____  \  
    |    |    |    __)_   |    |    |       _/ /   |   \ 
    |    |    |        \  |    |    |    |   \/    |    \
    |____|   /_______  /  |____|    |____|_  /\_______  /
                     \/                    \/         \/ 
------------------------------------------------------------

Tetro 1.0 by Bernard Walker
November 24th, 2024

Please see attribution.txt for music, sound, and graphic
credits.  

Tetro was written as a hobby project in-between matches of
Dead by Daylight, and when I had nothing better to do. 

It is released free of charge, under the GPL 3.0 license. 


------------------------------------------------------------
Requirements
------------------------------------------------------------

Tetro has been built with Allegro 4.3.2.1, using GCC/DJGPP.
Tetro requires an IBM compatible 386 or better with 4 megs 
of RAM, a VGA graphics card, a math co-processor, and a hard
disk drive. A Sound Blaster 16 or 100% compatible sound card
is recommended.

Tetro has been tested on an AMD 386DX40, though it should 
run on lower clocked machines without issue.


------------------------------------------------------------
Randomization
------------------------------------------------------------

Tetro supports two styles of randomization during play. The
first is the standard 7-Bag randomization seen in typical
Tetris implimentations such as NES Tetris or GameBoy Tetris.
The second is the randomization method seen in Tetris: The
Grand Master (1).  Neither is superior to another, and simply
a matter of preference.


------------------------------------------------------------
Special Thanks / Dedications
------------------------------------------------------------

A special thanks to my partner Jo, who demanded that I add
TGM style bag randomization.  In memory of Smokey and Lucy;
two cats who kept us sane over the years.

------------------------------------------------------------
Frequently Asked Questions
------------------------------------------------------------

If you require technical assistance in running Tetro, please
visit Tetro's GitHub repository:

https://github.com/ArtificialRaccoon/Tetro


------------------------------------------------------------
Why does Tetro require a math co-processor?

I had built Allegro requiring a floating point processor. I 
was simply too lazy to rebuild Allegro.  My apologies.


------------------------------------------------------------
Tetro crashes when I use a Sound Blaster 1.0

There is a bug with my build of Allegro.  While it should 
support the Sound Blaster 1.0, it instead crashes. The 
workaround for this issue is to disable the soundcard using
the Allegro setup.exe bundled with Tetro.


------------------------------------------------------------
Why is it called Tetro, and not Tetris?

Tetris is trademark of the Tetris Corporation.  While many
hundreds of Tetris clones exist, I chose not to risk getting
a sternly worded email over a hobby project.  Unlikey yes,
but stranger things have happened.