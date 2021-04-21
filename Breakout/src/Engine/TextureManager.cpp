#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager(SDL_Renderer* renderer) : gmRenderer (renderer)
{

}

TextureManager::~TextureManager() {
	m_TextureMap.clear();
}

void TextureManager::loadTexture(const std::string& name, const std::string& path) {
	SDL_Texture** newTexture = new SDL_Texture*;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());

	if (surface == NULL)
		SDL_Log("Failed to load image!");
	else {
		*newTexture = SDL_CreateTextureFromSurface(gmRenderer, surface);
		if (*newTexture == NULL)
			SDL_Log("Failed to create texture from surface!");
	}

	auto newEntry = std::make_pair(name, *newTexture);
	m_TextureMap.insert(newEntry);

	SDL_FreeSurface(surface);
}

SDL_Texture* TextureManager::getTexture(const std::string& name) {
	SDL_Texture* tex = m_TextureMap[name];
	if (!tex) {
		std::cout << "Texture with name '" << name << "' does not exist!" << std::endl;
		return NULL;
	}
	return tex;
}