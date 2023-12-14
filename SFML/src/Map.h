//��������� �����
#ifndef MAP_H
#define MAP_H
//��������� ������� � ������ ������
#define Access2(i, j) (i) * (mapH) + j //2�2
#define Access3(i, j, k) (i) * (mapH - 1) * 6 + (j) * 6 + k //3x3

#include "structs.h"
#include "TObject.h"
#include "TextureManager.h"

class Map
{
    int mapW, mapH;//������� �����
    Texture* texfield;//�������� �����

    //������� 
    TCell* vertexes;//2�2 ������ ������
    TCell* normals;//2x2  ������ ��������
    GLuint* indexes;//3x3 ������ ��������
    TUV* UV;//2x2 ������ ������ ��� �������

    TObject** objects;//������ ���������� �� �������
    int numObj;//���������� ��������

    void CalcNormals(TCell a, TCell b, TCell c, TCell* n);//�-� ���������� ��������
    void MapCreateHill(int posX, int posY, int rad, int height);// �-� �������� ������

public:

    Map(int imapW, int imapH, TextureManager& TexM);
    ~Map();
    float MapGetHeight(float x, float y);//�������� ������ �� ����������� x � y
    bool IsCoordInMap(float x, float y);//�������� ������������� ��������� x � y
    void MapShow(Window& window);//��������� �����

    static inline int jopa{};
    

};


#endif