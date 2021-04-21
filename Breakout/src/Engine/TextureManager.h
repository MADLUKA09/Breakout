#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>

class TextureManager
{
public:
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();

	void loadTexture(const std::string& name, const std::string& path);
	SDL_Texture* getTexture(const std::string& name);

private:
	std::unordered_map<std::string, SDL_Texture*> m_TextureMap;
	SDL_Renderer* gmRenderer;


};

