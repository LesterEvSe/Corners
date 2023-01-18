
# SFML Game Corners
  
  A program for _Linux_ that uses the _SFML_ graphical library. This is a checker game called **Corners** designed to entertain two players on the same device. The rules of the game are shown on the main application screen. Read only paragraph **Easy way to build and run**, if you could not build, then read all the way to the end, starting with paragraph **Requirements**
  
##  Easy way to build and run

###  This path via .sh files.
  - First of all, run the console from the "bash-scripts" directory
  - In order for the .sh files to run, they need to be allowed to run with the ***chmod +x build.sh game.sh*** command.
  - Next, install the necessary programs and build the project, using the ***bash build.sh*** command.
  - Lastly, you can run the game with the ***bash game.sh*** command.

##  Requirements
  
  The main thing you need to run is to have SFML version 2.5.1 or higher installed on your computer. You can install it with the command
  ***sudo apt-get install libsfml-dev*** or see the installation guide, on the official website https://www.sfml-dev.org/index.php
  
##  Build

  - To build a project, you need to make a "build" directory in the project folder with the command ***mkdir build***.
  - Then move into it with the command ***cd build***.
  - Next, you need to run ***cmake ..*** command inside "build" directory.
  - Finally, use the ***make*** command to compile, link the project, and create an executable.
  
##  Run
  
  If project was build successfully, you can run it, using ***./Corners*** command. To close the game, just click on the cross in the upper right corner.
