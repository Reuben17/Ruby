#if 0
#include "../src/Ruby.h"

using namespace Ruby;
using namespace Graphics;

class Game : public Rubyy
{
private:
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* sprite;
	Shader* shader;
public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->GetWidth() / 32.0f, window->GetHeight() / 18.0f);
#ifdef RUBY_EMSCRIPTEN
		shader = new Shader("res/shaders/basic.es3.vert", "res/shaders/basic.es3.frag");
#else
		shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
#endif
		layer = new Layer(new BatchRenderer2d(), shader, Maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

#ifdef RUBY_EMSCRIPTEN
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("res/test.png"));
#else
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("test.jpg"));
#endif
		layer->add(sprite);

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer->add(fps);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}

	void update() override
	{
		float speed = 0.5f;
		if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;

		//double x, y;
		//window->getMousePosition(x, y);
		//shader->setUniform2f("light_pos", Maths::vec2((float)(x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window->GetHeight())));
	}

	void render() override
	{
		layer->render();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}
#endif
