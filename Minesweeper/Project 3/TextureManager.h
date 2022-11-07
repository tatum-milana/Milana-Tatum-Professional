#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	//static = one and only one of these in memory, ever!
	static unordered_map<string, sf::Texture> textures;

	static void LoadTexture(string texName);


public:
	
	static sf::Texture& GetTexture(string texName);
	static void Clear();
	
};

