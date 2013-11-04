
#include "stdafx.h"
#include "ShapeGameManager.h"

int main(int argc, char* argv[])
{
	// get things going
	//  optional parameters:
	//		int windowWidth			default: 1024
	//		int windowHeight		default: 768
	//		std::string windowName	default: "Angel Engine"
	//		bool antiAliasing		default: false
	//		bool fullScreen			default: false
	//		bool resizable			default: false
	theWorld.Initialize(1024, 768, "Shape's Adventure", false);
	//theWorld.SetupPhysics();

  theWorld.SetBackgroundColor(Color::FromInts(0, 191, 255));

  //adds the default grid so you can more easily place Actors
	//theWorld.Add(new GridActor(), -1);

	//YOUR GAME SETUP CODE HERE
  theWorld.SetGameManager(new ShapeGameManager());

	// do all your setup first, because this function won't return until you're exiting
	theWorld.StartGame();

	// any cleanup can go here
	theWorld.Destroy();

	return 0;

}
