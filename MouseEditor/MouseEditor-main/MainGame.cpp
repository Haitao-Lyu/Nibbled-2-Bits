/*
___  ___                        _
|  \/  |                       | |
| .  . | __ _ _ __  _   _  __ _| |
| |\/| |/ _` | '_ \| | | |/ _` | |
| |  | | (_| | | | | |_| | (_| | |
\_|  |_/\__,_|_| |_|\__,_|\__,_|_|

Use UI buttons to navigate between categories and scroll through items.
Click the plus and minus buttons under an item in the UI to specify how many of that object a player is allowed to place. -1 represents unlimited.
Drag and drop from the UI panel on the left into the game area on the right.
Drag things from the game area out of the game area to remove them.
Place something over another object in the game area to replace it.
Right-click an item to rotate it.

The number above an item is a miscellaneous value that will be saved; it can be used for various things.
Use the up and down keys to change the miscellaneous value of the last selected item.
For example, define how much an object rotates and in which direction every time the mouse goes through.
Use it as an ID to pair objects (e.g., a landing pad and a spring; give them the same number to pair them up in the game).
Define how many times a bridge can be walked on before it breaks.

Mouse holes are special items that cannot be removed. The entrance is marked with an E, and the exit is marked with an X.
Place them along the walls; they will snap to the closest valid location.

To save, press 'S', and a text box will appear. Type the level name without an extension and press enter to save. Press exit to not save.
To load, press 'L'; it is the same as saving.
*/

#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "Panel.h"
#include "PanelItem.h"
#include "ReadCSV.h"
#include "EditorManager.h"
#include "GameArea.h"

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

EditorManager* editorManager;

std::vector<ObjectCSV> objects;
std::map<std::string, int> idMap;
std::vector<std::string> idToString;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE, AxisRotation::ANTICLOCKWISE_ZERO_RIGHT, CoordSys::XRIGHT_YUP);
	Play::LoadBackground("Data\\Backgrounds\\Background.png");

	Play::CentreAllSpriteOrigins();

	objects = ReadObjectsCSV();

	editorManager = new EditorManager(objects);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	editorManager->Update();
	editorManager->Draw();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	delete editorManager;
	Play::DestroyManager();
	return PLAY_OK;
}

