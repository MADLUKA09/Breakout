This is a project made for a job application at a game development company.
It is a simple Breakout clone with three levels.
It is made entirely in C++, with premake being used for build scripting.

SDL2 is used to simplify rendering, along with SDL2_Mixer for audio and SDL2_ttf for text on screen.
tinyxml2 is used for reading level files.

Everything else was made by me.

The controls:
-left and right directional arrows for moving the pad
-space for launching the ball

Additional controls:
-"L" buys a life for points, points can go negative
-"U" instant level up
-"R" resets the ball to the pad, made in case of bugs

There is a bug which allows the ball to sometimes clip through a wall.
The physics is severely unoptimized, but it mostly does the job.

The batch file generates the solution and the project, copies necessary libraries and assets to the build folder.

Thank you for viewing my project.