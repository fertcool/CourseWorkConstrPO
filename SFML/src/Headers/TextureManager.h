//заголовок менеджера текстур
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "stdafx.h"
#include <unordered_map> 
typedef std::shared_ptr<Texture> TexturePtr;
#define make_TexturePtr std::make_shared<Texture> 

class TextureManager
{
	std::unordered_map<std::string, TexturePtr> tex_map; // хеш-таблица с именемами и указателями на текстуры
	TexturePtr LoadTexture(std::string path);//загрузка текстуры
public:
	TextureManager();
	~TextureManager();
	void add(std::string path); //ф-я добавления 
	TexturePtr get(std::string path); //ф-я получения
	void remove(std::string name); //ф-я удаления

};
#endif