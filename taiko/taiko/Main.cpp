
# include "game.h"
# include "song_data.h"

void Main()
{
	Window::Resize(1080, 720);
	
	auto game = make_shared<Game>();

	while (System::Update()){
		game->update();
		game->draw();
	}
}
