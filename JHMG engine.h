#ifndef JHMG_ENGINE_H
#define JHMG_ENGINE_H
#include "easyx.h"
#include<map>
#include<string>
#include<iostream>
#include<stdexcept>
#include<cmath>
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

/*
   �Զ����ࣺjhString�࣬jhFraction�࣬jhVector2�࣬jhList�࣬jhMatrix�࣬jhObject2D�����ռ�{transform��,circle��,rectangle��,triangle��,diamond��,trapezium��}
*/
#define PI 3.14
// �������
class jhString;
class jhFraction;
class jhVector2;
template<class T> class jhList;
class jhMatrix;
namespace jhObject2D
{
	class transform;
	class circle;
	class rectangle;
	class triangle;
	class diamond;
	class trapezium;
};

//��Ϸ������
class gameObject;
class gameUI;
class gameUIText;
class gameSound;
class gameInput;
class gameScene;
template<class T> class MouseAction;
class gameInputBox;
class gameMessageBox;
class Game;

//jhString��:�ַ�������
class jhString
{
public:
	//��Ԫ��
	friend ostream& operator<<(ostream& cout, const jhString& str);
	friend istream& operator>>(istream& cin, const jhString& str);
	//���캯��
	jhString();
	jhString(const string& str);
	jhString(const char* str);
	jhString(const jhString& str);
	//���������
	jhString operator+(const jhString& str);
	jhString operator+(const string& str);
	void operator=(const jhString& str);
	void operator=(const string& str);
	void operator+=(const jhString& str);
	void operator+=(const string& str);
	bool operator==(const jhString& str);
	bool operator<(const jhString& str)const;
	bool operator>(const jhString& str)const;
	//�ַ���ת��Ϊ��������(�������)
	int to_int();
	//ת��Ϊchar*
	char* to_char();
	//�ַ���ת��Ϊ����������(�������)
	float to_float();
	//�����ַ�����������0��ʼ
	int indexOf(const string& str);
	//�����ַ�����������0��ʼ
	int indexOf(const jhString& str);
	//ת��Ϊstd::string
	string to_stdString();
	//�ַ�����ȡ������ʼλ�ý�ȡ���յ�λ�ã���0��ʼ
	string substr(int begin, int end);
	//�ַ�����ȡ,������ַ���ȡ���ұ��ַ�(�������߽�)�����Ҳ�����ߣ����ؿգ����ҵ���ߣ����Ҳ����ұߣ�������ߵ�ĩβ
	string substr(const string& leftStr, const string& rightStr);
private:
	string str;
};
//jhFraction��:s/m������
class jhFraction
{
public:
	//��Ԫ��
	friend ostream& operator<<(ostream& cout, const jhFraction& num);
	friend istream& operator>>(istream& cin, jhFraction& num);
	//���캯��
	jhFraction();
	//�������캯��
	jhFraction(const jhFraction& num);
	//���캯��
	jhFraction(int num);
	jhFraction(double num);
	jhFraction(int s, int m);
	//����
	void simplify();
	//��ӡ
	void print();
	//ת��Ϊ������
	float to_float();
	//�ӷ����������
	jhFraction operator+(const jhFraction& num);
	jhFraction operator+(float num);
	//�ӵ������������
	jhFraction& operator+=(float num);
	jhFraction& operator+=(const jhFraction& num);
	//�������������
	jhFraction operator-(const jhFraction& num);
	jhFraction operator-(float num);
	//���������������
	jhFraction& operator-=(const jhFraction& num);
	jhFraction& operator-=(float num);
	//�˷����������
	jhFraction operator*(const jhFraction& num);
	jhFraction operator*(float num);
	//�˵������������
	jhFraction operator*=(float num);
	//�������������
	jhFraction operator=(const jhFraction& num);
	//�������������
	jhFraction operator/(const jhFraction& num);
	jhFraction operator/(float num);
	//���������������
	jhFraction operator/=(float num);
	//�Ƚ����������
	bool operator>(const jhFraction& num);
	bool operator>(float num);
	bool operator>=(const jhFraction& num);
	bool operator>=(float num);
	bool operator<(const jhFraction& num);
	bool operator<(float num);
	bool operator<=(const jhFraction& num);
	bool operator<=(float num);
	bool operator==(const jhFraction& num);
	bool operator==(float num);
private:
	int s, m;/* ��s/m�������ͣ�*/
};
//jhVector2�ࣺ��ά����������
class jhVector2
{
public:
	//��Ԫ��
	float x, y;
	//Ĭ�Ϲ��캯��
	jhVector2();
	//���캯��
	jhVector2(float x, float y);
	//�������캯��
	jhVector2(const jhVector2& v2);
	//��ֵ���������
	jhVector2& operator=(const jhVector2& v2);
	//�ӷ����������
	jhVector2 operator+(const jhVector2& v2);
	//�ӵ������������
	jhVector2& operator+=(const jhVector2& v2);
	//�������������
	jhVector2 operator-(const jhVector2& v2);
	//���������������
	jhVector2& operator-=(const jhVector2& v2);
	//�˷����������
	jhVector2 operator*(float i);
	//�������������
	jhVector2 operator/(float i);
	//�ж��Ƿ����
	bool operator==(const jhVector2& v2);
	//���������
	double destance(const jhVector2& objective);
	//���������
	double cross_product(const jhVector2& objective);
	//���������
	double dot_product(const jhVector2& objective);
	//��ת
	void rotate(const jhVector2& center, float angle);
};
//jhList:����ģ����(��������)
template<class T>
class jhList
{
public:
	struct node
	{
		node* p_back = NULL;
		node* p_next = NULL;
		T value;
	};
	//����ͷ
	node* p_first;
	//�ں�����ӽڵ�
	void addList(T value);
	//ɾ���ڵ�
	void deleteList(node* list);
	//Ĭ�Ϲ��캯��
	jhList();
	//��������
	~jhList();
};
//jhMatrix�࣬������
class jhMatrix
{
private:

	float** matrix;
	int row, column;
	void init(int row, int column)
	{
		this->row = row;
		this->column = column;
		this->matrix = new float* [row];
		for (int i = 0; i < this->row; i++)
		{
			this->matrix[i] = new float[this->column];
		}
	}
public:

	// Ĭ�Ϲ��캯��
	jhMatrix(int row, int column);
	//����һ��������
	jhMatrix(const jhMatrix& other);
	// jhVector2���캯��
	jhMatrix(const jhVector2& v2);
	// ��ά����ת����һάָ�빹��
	jhMatrix(float* other, int row, int column);
	// ��������
	~jhMatrix();
	// ���þ���ֵ
	void setValue(int row, int column, float value);
	//��ӡ����
	void print(bool isFraction = false);
	// ȡת�þ���
	jhMatrix getTransposeMatrix();
	// ȡ�����
	jhMatrix getInverseMatrix();
	//ȡ����ʽ
	float getDeterminant();
	// ������
	void swapRows(int row1, int row2);
	// ��ĳ������Ԫ�س���һ����
	void divideRow(int row, float divisor);
	// ��һ�мӵ���һ�еı���
	void addToRow(int sourceRow, int destRow, float multiple);
	// ��������
	jhMatrix operator+(const jhMatrix& other);
	jhMatrix operator-(const jhMatrix& other);
	jhMatrix operator*(const jhMatrix& other);
	jhMatrix operator*(float num);
	void operator=(const jhMatrix& other);
	bool operator==(const jhMatrix& other);
};

namespace jhObject2D
{
	// ������
	class transform;
	class circle;
	class rectangle;
	class triangle;
	class diamond;
	//���ʵ��
	// �������
	class transform
	{
	public:

		//��Ԫ��
		friend class circle;
		friend class rectangle;
		friend class triangle;
		friend class diamond;
		// Ĭ�Ϲ��캯��
		transform();
		//�������캯��
		transform(const transform& other);
		// ���캯��
		transform(jhVector2 position);
		//�ƶ�
		virtual void move(jhVector2 dest) = 0;
		//��ȡ��ǰλ��
		virtual jhVector2 getPosition();
		// �������
		virtual float getAreaSize() = 0;
		// �������
		float getDistance(const transform& other);
		//��ȡ���Ͻ�����
		virtual jhVector2 getLeftTopPosition() = 0;
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const triangle& other) = 0;
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const rectangle& other) = 0;
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const diamond& other) = 0;
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const circle& other) = 0;
	private:
		// λ��(ͼ���������꣬�����Բ��������)
		jhVector2 position;
	};

	// Բ��
	class circle :public transform
	{
	public:

		// Ĭ�Ϲ��캯��
		circle(float radius, jhVector2 position = jhVector2(0, 0));
		// �������캯��
		circle(const circle& other);
		// �뾶
		float radius;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(jhVector2 dest);
		//��ȡ���Ͻ�����
		virtual jhVector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const circle& other);
	};

	// ����
	class rectangle : public transform
	{
	public:

		// Ĭ�Ϲ��캯��
		rectangle(float width, float height, jhVector2 position = jhVector2(0, 0));
		// �������캯��
		rectangle(const rectangle& other);
		// ��Ⱥ͸߶�
		float width;
		// �߶�
		float height;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(jhVector2 dest);
		// ��ȡ���Ͻ�����
		virtual jhVector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const circle& other);
	};
	// ������
	class triangle :public transform
	{
	public:

		// ������ͨ������
		triangle(jhVector2 pointA, jhVector2 pointB, jhVector2 pointC);
		// ����ȱ�������
		triangle(jhVector2 center, float coLength);
		// �������캯��
		triangle(const triangle& other);
		// �ƶ�
		virtual void move(jhVector2 dest);
		// ��������
		jhVector2 pointA, pointB, pointC;
		// ��ȡ��A������
		jhVector2 getPositionA();
		// ��ȡ��B������
		jhVector2 getPositionB();
		// ��ȡ��C������
		jhVector2 getPositionC();
		//��ȡ���Ͻ�����
		virtual jhVector2 getLeftTopPosition();
		// ��ȡ���
		virtual float getAreaSize();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const circle& other);
	};

	// ����
	class diamond :public transform
	{
	public:

		// �ԶԽ��߳��ȹ�������
		diamond(float lengthX, float lengthY, jhVector2 position = jhVector2(0, 0));
		//�������캯��
		diamond(const diamond& other);
		// �Խ��߳���
		float lengthX, lengthY;
		// ��ȡ���
		virtual float getAreaSize();
		// �ƶ�
		virtual void move(jhVector2 dest);
		//��ȡ���Ͻ�����
		virtual jhVector2 getLeftTopPosition();
		// �ж��Ƿ�����������
		virtual bool isTriggerEnter(const triangle& other);
		// �ж��Ƿ��ھ�����
		virtual bool isTriggerEnter(const rectangle& other);
		// �ж��Ƿ���������
		virtual bool isTriggerEnter(const diamond& other);
		// �ж��Ƿ���Բ����
		virtual bool isTriggerEnter(const circle& other);
	};

};



//��Ϸ������
class gameObject
{
	friend class Game;
	friend class gameScene;
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
	//����¼�
	MouseAction<gameObject*>* mouseAction;
	//��Ϸ���������
	bool visible;
	//���캯��
	gameObject(jhObject2D::circle* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::rectangle* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::diamond* transform, LPCTSTR file, int width, int height, bool visible = true);
	gameObject(jhObject2D::triangle* transform, LPCTSTR file, int width, int height, bool visible = true);
	//������ײ�ص�����
	gameObject* setOnCollision(void (*onCollision)(gameObject* gameObject));
	//������Ϸѭ���ص�����
	gameObject* setGameLoopFunc(void(*gameLoopFunc)(gameObject* gameObject));
	// �޸���Ϸ������ͼ
	gameObject* changeImage(LPCTSTR file,jhVector2 size);
	//��ǩ
	jhString tag="gameObject";


private:
	//��Ϸ�����ͼƬ
	IMAGE* image;
	//��ײ�ص�����
	void (*onCollision)(gameObject* gameObject) = NULL;
	//��Ϸѭ���ص�����
	void(*gameLoopFunc)(gameObject* gameObject) = NULL;
	//�����ô���
	int refCount = 0;
};

//��Ϸ������
class gameUI
{
	friend class Game;
	friend class gameScene;
private:
	//ͼƬ
	IMAGE* image;
	//�����ô���
	int refCount = 0;
	//ѭ������
	void (*gameLoopFunc)(gameUI* self) = NULL;
public:
	//λ��
	jhVector2 position;
	//��С
	jhVector2 size;
	//����¼�
	MouseAction<gameUI*>* mouseAction;
	//������
	bool visible;
	//����ѭ������
	gameUI* setGameLoopFunc(void (*gameLoopFunc)(gameUI* self));
	//���캯��
	gameUI(jhVector2 position, jhVector2 size, jhString image, bool visible = true);
	//�޸���Ϸ������ͼ
	gameUI* changeImage(LPCTSTR file, jhVector2 size);
	//��ǩ
	jhString tag = "gameUI";
};

//��Ϸ����������
class gameUIText
{
	friend class Game;
	friend class gameScene;
public:
	// ����
	jhString text;
	// ��ɫ
	COLORREF color;
	// �����С
	jhVector2 size;
	// λ��
	jhVector2 position;
	// ������
	bool visible;
	// ���캯��
	gameUIText(jhString text, jhVector2 position, COLORREF color = WHITE, jhVector2 size = jhVector2(0, 15), bool visible = true);
private:
	//�����ô���
	int refCount = 0;
	//��ǩ
	jhString tag = "gameUIText";
};


//��Ϸ��Ч��
class gameSound
{
	friend class Game;
private:
	//��Ч
	jhString music_file;
public:
	//���������ļ�
	void setSound(jhString music_file);
	//������Ч
	void play(bool repeat=false);
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
	a = 65,
	b = 66,
	c = 67,
	d = 68,
	e = 69,
	f = 70,
	g = 71,
	h = 72,
	i = 73,
	j = 74,
	k = 75,
	l = 76,
	m = 77,
	n = 78,
	o = 79,
	p = 80,
	q = 81,
	r = 82,
	s = 83,
	t = 84,
	u = 85,
	v = 86,
	w = 87,
	x = 88,
	y = 89,
	z = 90,
	enter = 13,
	space = 32,
	esc = 27,
};

//����������
class gameInput
{
	friend class Game;
private:
	char key;
	void getMessage(const ExMessage& msg);
public:
	//��ȡ��������
	char getKey();
};

enum MouseMessage
{
	leftDown = 513,
	leftUp = 514,
	rightDown = 516,
	rightUp = 517,
};

//��Ϸ������
class gameScene
{
	friend class Game;
private:
	//��Ϸ����
	jhList<gameObject*> gameObjects;
	//��Ϸ����
	jhList<gameUI*> gameUIs;
	//��������
	jhList<gameUIText*> gameUITexts;
	//��Ϸ����map
	map<jhString, gameObject*> gameObjectsMap;
	//��Ϸ����map
	map<jhString, gameUI*> gameUIMap;
	//��Ϸ��������map
	map<jhString, gameUIText*> gameUITextsMap;
	//��Դ��map ����100������UI10����������1
	map<jhString, int> gameTotalMap;
	//ѭ������
	void (*gameLoop)()=NULL;
	//���Ѻ���
	void (*awake)() = NULL;
public:
	//��������
	~gameScene();
	//�����Ϸ����
	void addGameObject(jhString name, gameObject* gameObject);
	//ɾ����Ϸ����
	void removeGameObject(jhString name);
	//��ȡ��Ϸ��������
	jhString getName(gameObject* gameObject);
	jhString getName(gameUI* gameUI);
	jhString getName(gameUIText* gameUIText);
	//�����Ϸ����UI����
	void addGameUI(jhString name, gameUI* gameUI);
	//�����Ϸ��������
	void addGameUIText(jhString name, gameUIText* text);
	//ɾ����Ϸ����
	void removeGameUI(jhString name);
	//ɾ����Ϸ��������
	void removeGameUIText(jhString name);
	//��ȡ��Ϸ����
	gameObject* getGameObject(jhString name);
	//��ȡ��Ϸ����
	gameUI* getGameUI(jhString name);
	//��ȡ��Ϸ�����ı�
	gameUIText* getGameUIText(jhString name);
	//����ѭ������
	void setGameLoopFunc(void (*gameLoop)());
	//���û��Ѻ���
	void setAwakeFunc(void (*awake)());
};

//����¼���
template<class T>
class MouseAction
{
	friend class Game;
	friend class gameObject;
	friend class gameUI;
private:
	//���Ͻ���ʼ�ж�����
	jhVector2 beginPosition;
	//���½ǽ����ж�����
	jhVector2 endPosition;
	//��ȡ������¼�
	void getMouseMessage(const ExMessage& msg);
	//������ָ��
	T self;
	//������ص�����
	void (*onClick)(int mouseMessage, jhVector2 position,T self) = NULL;
public:
	//����������ص�����
	void setClickFunc(void (*onClick)(int mouseMessage, jhVector2 position,T self));
};

//�������
class gameInputBox
{
	friend class Game;
private:
	jhString* inputText;
	jhString title;
	jhString prompt = "";
	jhString defaultText = "";
	int maxInput = 100;
	jhVector2 size = jhVector2(0,0);
public:
	gameInputBox(jhString* inputText, jhString title="notice", jhString prompt="", jhString defaultText="", int max=256, jhVector2 size=jhVector2(0,0));
	void show();
};

//��Ϣ����
class gameMessageBox
{
	friend class Game;
private:
		jhString title = "notice:";
		jhString message = "";
public:
	gameMessageBox(jhString title, jhString message);
	void show();
};

//��Ϸ��
class Game
{
private:
	//��Ϸ���ھ��
	HWND window;
	//��Ϸ���ڴ�С
	jhVector2 windowSize = jhVector2(800, 600);
	//��Ϸ���ڱ���
	jhString windowTitle = "not define";
	//��Ϸ����
	gameScene* Scene = NULL;
	//��Ϸ֡��
	int targetFrame = 60;
	//��Ϸ��Ч
	gameSound Sound;
	//��Ϸѭ��
	void gameLoop();
public:
	//������Ϸ���ڴ�С
	void setWindowSize(jhVector2 windowSize);
	//������Ϸ���ڱ���
	void setWindowTitle(jhString windowTitle);
	//��ʼ������,��ʼ��Ϸ
	void initWindow();
	//������Ϸ����
	void setScene(gameScene* Scene);
	//������Ϸ֡��
	void setTargetFrame(int targetFrame);
	//��Ϸ���
	long deltaTime;
	//��ȡ��Ϸ���ڴ�С
	jhVector2 getWindowSize();
	//��ȡ��Ϸ���ڱ���
	jhString getWindowTitle();
	//��ȡ��Ϸ����
	gameScene* getScene();
	//��������
	gameInput Input;
};


#endif // !JHMG_ENGINE_H