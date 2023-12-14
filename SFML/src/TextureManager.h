//заголовок менеджера текстур
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "stdafx.h"
#include <unordered_map> 

class TextureManager
{
	std::unordered_map<std::string, Texture*> tex_map; // хеш-таблица с именемами и указателями на текстуры
	Texture* LoadTexture(std::string path);//загрузка текстуры
public:
	TextureManager();
	~TextureManager();
	void add(std::string path); //ф-я добавления 
	Texture* get(std::string path); //ф-я получения
	void remove(std::string name); //ф-я удаления

};
#endif