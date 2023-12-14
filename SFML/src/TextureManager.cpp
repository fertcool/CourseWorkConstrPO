#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
    for (auto& item : tex_map)
    {
        delete item.second;
    }
}
//ф-я добавления текстуры в менеджер
void TextureManager::add(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//если уже есть 
    {
        return;
    }
    tex_map[path] = LoadTexture(path);
}
//ф-я получения текстуры
Texture* TextureManager::get(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//если уже есть 
    {
        return tex_map[path];
    }
    return nullptr;
}
//ф-я удаления текстуры
void TextureManager::remove(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//если уже есть 
    {
        tex_map.erase(path);
    }
}
//ф-я загрузки текстуры
Texture* TextureManager::LoadTexture(std::string path)
{
    Texture* texture = new Texture;
    if (!texture->loadFromFile(path))
    {
        std::cout << "Texture didn't load!";
        delete texture;
        return nullptr;
    }
    return texture;
}