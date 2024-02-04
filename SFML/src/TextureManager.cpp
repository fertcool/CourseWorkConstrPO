#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
    /*for (auto& item : tex_map)
    {
        delete item.second;
    }*/
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
TexturePtr TextureManager::get(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//если уже есть 
    {
        return tex_map[path];
    }
    return TexturePtr(nullptr);
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
TexturePtr TextureManager::LoadTexture(std::string path)
{
    TexturePtr texture = make_TexturePtr();
    if (!texture->loadFromFile(path))
    {
        std::cout << "Texture didn't load!";
        return TexturePtr(nullptr);
    }
    return texture;
}