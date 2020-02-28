#pragma once

//Ÿ�ϻ�����
#define TILESIZE 52

//ũ��
#define TILEX 52
#define TILEY 52

//Ÿ�� �� ������
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//����
enum TERRAIN
{
	//�ƹ��͵�����		��
	TERRAIN_NONE, TERRAIN_GROUND , TERRAIN_DOOR
};

//������Ʈ
enum OBJECT
{
	OBJ_NONE, OBJ_NOMALWALL, OBJ_SKULLWALL, OBJ_WHITEWALL, OBJ_IRONWALL, OBJ_GOLDWALL
};

//������ ����
enum POS
{

};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;			//����
	OBJECT obj;					//������Ʈ
	RECT rc;					//��Ʈ
	int terrainFrameX;			//���� �����ӹ�ȣ
	int terrainFrameY;			
	int objFrameX;				//������Ʈ �����ӹ�ȣ
	int objFrameY;
	int x, y;					//Ÿ�� ������ǥ
	int strength;				//Ÿ���� ����
};

//����Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;				//����Ÿ�� ��Ʈ
	int terrainFrameX;			//����Ÿ�� ������ ��ȣ
	int terrainFrameY;			
};

//����Ÿ��(���� Ŭ���� Ÿ�� ���� �����)
struct tagCurrentTile
{
	int x;
	int y;
};