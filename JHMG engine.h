#pragma once
#include<easyx.h>
#include "jhClass.h"
#include<map>
using namespace std;

//���ֲ��������
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*	
����ϵ˵����
	����ԭ�����豸�����Ͻǣ�X ������Ϊ����Y ������Ϊ����������λ������
*/

//putImg��չ
inline void putimagePNG(int x, int y, IMAGE* img) {
	DWORD* pwin = GetImageBuffer();//��ȡ���ڻ�����ָ��
	DWORD* pimg = GetImageBuffer(img);//��ȡͼƬ������ָ��
	int win_w = getwidth();
	int win_h = getheight();
	int img_w = img->getwidth();
	int img_h = img->getheight();
	//�ж�x,y�����Ƿ񳬳��˴��ڵķ�Χ
	int real_w = (x + img_w > win_w) ? win_w - x : img_w;//�����ұ߽�ʵ����ͼ�Ŀ��
	int real_h = (y + img_h > win_h) ? win_h - y : img_h;//�����±߽�
	if (x < 0) {//������߽紦��
		pimg += -x;//��ָ�����ƫ��
		real_w -= -x;
		x = 0;
	}
	if (y < 0) {//�����ϱ߽紦��
		pimg += (img_w * -y);//��ָ�����ƫ��
		real_h -= -y;
		y = 0;
	}
	pwin += (win_w * y + x);

	for (int iy = 0; iy < real_h; iy++) {
		for (int ix = 0; ix < real_w; ix++) {
			UCHAR alpha = pimg[ix] >> 24;
			if (alpha > 200)//alpha  0 ��ʾ��ȫ͸��
			{
				pwin[ix] = pimg[ix];
			}
		}
		//������һ��
		pwin += win_w;
		pimg += img_w;
	}
}

class gameObject;
class gameUI;
class gameSound;
class gameInput;
class Game;


//��Ϸ������
class gameObject
{
	friend class Game;
public:
	//��Ϸ����
	union Transform
	{
		jhObject2D::circle* circle;
		jhObject2D::diamond* diamond;
		jhObject2D::rectangle* rectangle;
		jhObject2D::triangle* triangle;
	};
	Transform transform;
	char transformType;

	//��Ϸ���������
	bool visible;
	//���캯��
	gameObject(jhObject2D::circle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::rectangle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::diamond* transform, LPCTSTR file,int width ,int height, bool visible = true);
	gameObject(jhObject2D::triangle* transform, LPCTSTR file,int width ,int height, bool visible = true);
	//������ײ�ص�����
	void setOnCollision(void (*onCollision)(gameObject* gameObject));
	

private:
	//��Ϸ�����ͼƬ
	IMAGE* image;
	//��ײ�ص�����
	void (*onCollision)(gameObject* gameObject) = NULL;
};

//��Ϸ������
class gameUI
{
	friend class Game;
private:
	//ͼƬ
	IMAGE* image;
public:
	//λ��
	jhVector2 position;
	//��С
	jhVector2 size;
	//������
	bool visible;
	//���캯��
	gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible = true);
};

//��Ϸ��Ч��
class gameSound
{
public:
	//��Ч
	jhString music_file;
	//���������ļ�
	void setSound(jhString music_file);
	//������Ч
	void play();
	//ֹͣ��Ч
	void stop();
	//��ͣ��Ч
	void pause();
	//������Ч
	void resume();
	//��������
	void setVolume(int volume);
	//��ȡ����
	int getVolume();
	//���ò���λ��
	void setPosition(int position);
	//��ȡ����λ��
	int getPosition();
	//��ȡ��Ч����
	int getLength();
	//��ȡ��Ч״̬
	int getState();
	//�ر���Ч
	void close();
	//��������
	~gameSound();
};

//������Ϣ��
enum KeyMessage
{
	a =65,
	b =66,
	c =67,
	d =68,
	e =69,
	f =70,
	g =71,
	h =72,
	i =73,
	j =74,
	k =75,
	l =76,
	m =77,
	n =78,
	o =79,
	p =80,
	q =81,
	r =82,
	s =83,
	t =84,
	u =85,
	v =86,
	w =87,
	x =88,
	y =89,
	z =90,
	enter =13,
	space =32,
	esc =27,
};

//����������
class gameInput
{
	friend class Game;
private:
	ExMessage msg;
	char key;
	void getMessage();
public:
	//��ȡ��������
	char getKey();
};

//��Ϸ��
class Game
{
private:
	//��Ϸ���ھ��
	HWND window;
	//��Ϸ���ڴ�С
	jhVector2 windowSize= jhVector2(800, 600);
	//��Ϸ���ڱ���
	jhString windowTitle = "not define";
	//��Ϸ����
	jhList<gameObject*> gameObjects;
	//��Ϸ����
	jhList<gameUI*> gameUIs;
	//��Ϸ֡��
	int targetFrame = 60;
	//��Ϸ���
	long deltaTime;
	//��Ϸѭ���Զ��庯��
	void(*gameLoopFunc)() = NULL;
	//��Ϸ��Ч
	gameSound Sound;
	//��Ϸ����map
	map<jhString,gameObject*> gameObjectsMap;
	//��Ϸ����map
	map<jhString,gameUI*> gameUIMap;
	//��Ϸѭ��
	void gameLoop();
public:
	//������Ϸ���ڴ�С
	void setWindowSize(jhVector2 windowSize);
	//������Ϸ���ڱ���
	void setWindowTitle(jhString windowTitle);
	//����ѭ������
	void setGameLoopFunc(void(*func)());
	//��ʼ������,��ʼ��Ϸ
	void initWindow();
	//������Ϸ֡��
	void setTargetFrame(int targetFrame);
	//��ȡ��Ϸ���ڴ�С
	jhVector2 getWindowSize();
	//��ȡ��Ϸ���ڱ���
	jhString getWindowTitle();
	//�����Ϸ����
	void addGameObject(jhString name,gameObject* gameObject);
	//ɾ����Ϸ����
	void removeGameObject(jhString name);
	//��ȡ��Ϸ����
	gameObject* getGameObject(jhString name);
	//��ȡ��Ϸ��������
	jhString getName(gameObject* gameObject);
	//�����Ϸ����
	void addGameUI(jhString name,gameUI* gameUI);
	//ɾ����Ϸ����
	void removeGameUI(jhString name);
	//��ȡ��Ϸ����
	gameUI* getGameUI(jhString name);
	//��������
	gameInput Input;
};