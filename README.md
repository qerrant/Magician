# Magician
This project is a port of the [$1 Unistroke Recognizer](http://faculty.washington.edu/wobbrock/pubs/uist-07.01.pdf) to Unreal Engine (C++). There are only 6 templates (star, triangle, circle, v, x, pigtail), but you can add your own both by exporting CSV tables and in training mode. The project used UE4 v4.26.
![Alt Text](https://github.com/qerrant/Magician/blob/9969d49e6a5ff90d460a10ddd4dc7133ea45ebb0/demo.gif)
## Training
Enter the **TrainMode [value]** in the console (~).
* 1 - ON
* 0 - OFF

 *ex., TrainMode 1 to enable train mode.* 
## Details
The generated objects and gesture names are entered into the Magician Pawn (Blueprint). 
## Structure
#### Gesture Recognizer
* UnistrokeRecognizer - general
* UnistrokeRectangle - struct for boundgin box
* UnistrokeResult - struct of result (name, score, time)
* UnistrokeTemplate - create template from unistroke points
* UnistrokePoint - main struct with main algorithms
#### Template Vault
* UnistrokeDataTable - struct of Data Table
#### Demo
* PaintWidget - Widget for painting points
* TrainWidget - Add points as a template to Data Table
* MagicianPlayerController - Player Controller
* MagicianPawn - Pawn
* MagicianGameModeBase - Game Mode
