//��������� ��������� �������
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include "stdafx.h"
#include <unordered_map> 
typedef std::shared_ptr<Texture> TexturePtr;
#define make_TexturePtr std::make_shared<Texture> 

class TextureManager
{
	std::unordered_map<std::string, TexturePtr> tex_map; // ���-������� � ��������� � ����������� �� ��������
	TexturePtr LoadTexture(std::string path);//�������� ��������
public:
	TextureManager();
	~TextureManager();
	void add(std::string path); //�-� ���������� 
	TexturePtr get(std::string path); //�-� ���������
	void remove(std::string name); //�-� ��������

};
#endif