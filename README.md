# Magician
This project is a port of the [$1 Unistroke Recognizer](http://faculty.washington.edu/wobbrock/pubs/uist-07.01.pdf) to Unreal Engine (C++).
## Training
Enter the **TrainMode [value]** in the console (~).
* 1 - ON
* 0 - OFF
*ex., TrainMode 1* to enable train mode.* 
## Details
The generated objects and gesture names are entered into the Magician Pawn (Blueprint). 
## Structure
### Gesture Recognizer
* UnistrokeRecognizer
* UnistrokeRectangle
* UnistrokeResult
* UnistrokeTemplate
* UnistrokePoint
### Template Vault
* UnistrokeDataTable
### Demo
* PaintWidget
* TrainWidget
* MagicianPlayerController
* MagicianPawn
* MagicianGameModeBase