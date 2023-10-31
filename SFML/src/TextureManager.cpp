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

void TextureManager::add(std::string path)
{
    if (tex_map.find(path) != tex_map.end())
    {
        return;
    }
    tex_map[path] = LoadTexture(path);
}
Texture* TextureManager::get(std::string path)
{
    if (tex_map.find(path) != tex_map.end())
    {
        return tex_map[path];
    }
    return nullptr;
}
void TextureManager::remove(std::string path)
{
    if (tex_map.find(path) != tex_map.end())
    {
        tex_map.erase(path);
    }
}
Texture* TextureManager::LoadTexture(std::string path)
{
    Texture* texture= new Texture;
    if (!texture->loadFromFile(path))
    {
        std::cout << "Texture didn't load!";
        delete texture;
        return nullptr;
    }
    return texture;
}