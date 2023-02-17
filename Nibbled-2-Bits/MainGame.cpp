#define PLAY_IMPLEMENTATION
#include "MainGame.h"
#include "GameTool/Timer.h"

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	int bk_id = Play::LoadBackground("Data\\Sprites\\Mouse Bundle\\background\\non-repeating-with-glows\\yellow.png");
	Play::CentreAllSpriteOrigins();

}


// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	Timer::UpdateDeltaTime(elapsedTime);

	Play::SetDrawingBlendMode( Play::BLEND_NORMAL );
	Play::PresentDrawingBuffer();

	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

