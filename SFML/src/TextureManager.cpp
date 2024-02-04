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
//�-� ���������� �������� � ��������
void TextureManager::add(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//���� ��� ���� 
    {
        return;
    }
    tex_map[path] = LoadTexture(path);
}
//�-� ��������� ��������
TexturePtr TextureManager::get(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//���� ��� ���� 
    {
        return tex_map[path];
    }
    return TexturePtr(nullptr);
}
//�-� �������� ��������
void TextureManager::remove(std::string path)
{
    if (tex_map.find(path) != tex_map.end())//���� ��� ���� 
    {
        tex_map.erase(path);
    }
}
//�-� �������� ��������
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