#include "../../Main/include/Headers.h"

int main(int argc, char *argv[]) {
	HO::GameEngine engine;
	if (engine.Initialize()) {
		engine.RunLoop();
	}
	engine.Quit();
	return 0;
}