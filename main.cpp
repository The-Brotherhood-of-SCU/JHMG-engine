#include "JHMG engine.h"

//������Ϸȫ�ֱ���
Game* mainGame = NULL;
gameUI* xiaoxin = NULL;
gameObject* pikaqiu = NULL;
gameObject* player = NULL;
//��������
void loop();
void trigle(gameObject* other);

int main(int argc, char* argv[])
{
	//������Ϸ����
	mainGame = new Game;
	//���ô��ڴ�С�ͱ���
	mainGame->setWindowSize(jhVector2(800,600));
	mainGame->setWindowTitle("Game");
	//������Ϸ֡��
	mainGame->setTargetFrame(60);
	//������Ϸѭ������(ÿ֡����һ��)
	mainGame->setGameLoopFunc(loop);

	//����UI����
	xiaoxin = new gameUI(jhVector2(0,0),jhVector2(50,50),".\\xiaoxin.png",true);
	//���UI������Ϸ��
	mainGame->addGameUI("xiaoxin",xiaoxin);
	//�����ı�UI
	gameUIText* text = new gameUIText(jhString("my game"), jhVector2(100, 100), true);
	//����ı�UI����Ϸ��
	mainGame->addGameUIText("text", text);
	//������Ϸ����
	player = new gameObject(new jhObject2D::circle(20,jhVector2(170,70)),".\\pkq.png",40,40,true);
	pikaqiu = new gameObject(new jhObject2D::circle(20, jhVector2(270, 70)), ".\\pkq.png", 40, 40, true);
	//����Ϸ������ײ�¼�
	player->setOnCollision(trigle);
	//�����Ϸ������Ϸ��
	mainGame->addGameObject("player",player);
	mainGame->addGameObject("pikaqiu", pikaqiu);

	//��ʼ�����ڿ�ʼ��Ϸ
	mainGame->initWindow();
}

void loop()
{
	//��ȡ��������
	auto key = mainGame->Input.getKey();
	//�жϼ�������
	if (key == KeyMessage::a)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(-50,0);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(50,0);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,-50);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,50);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::space)
	{
		//ɾ������
		cout << "delete pikaqiu" << endl;
		mainGame->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//�˳���Ϸ
		exit(0);
	}
}

void trigle(gameObject* other)
{
	//��ײ�������
	cout<<mainGame->getName(other)<<endl;
}