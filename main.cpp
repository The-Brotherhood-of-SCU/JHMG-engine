#include "JHMG engine.h"

//����ȫ����Ϸ����
Game* mainGame;

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
	gameUI* xiaoxin = new gameUI(jhVector2(0,0),jhVector2(50,50),".\\xiaoxin.png",true);
	//���UI������Ϸ��
	mainGame->addGameUI("xiaoxin",xiaoxin);
	//�����ı�UI
	gameUIText* text = new gameUIText(jhString("fps"), jhVector2(100, 100), true);
	//����ı�UI����Ϸ��
	mainGame->addGameUIText("text", text);
	//������Ϸ����
	gameObject* player = new gameObject(new jhObject2D::circle(25,jhVector2(170,70)),".\\pkq.png",50,50,true);
	gameObject* pikaqiu = new gameObject(new jhObject2D::circle(25, jhVector2(270, 70)), ".\\pkq.png", 50, 50, true);
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
	//��ȡ��Ϸ����
	auto player = mainGame->getGameObject("player");
	//��ȡUI�ı�����
	auto text = mainGame->getGameUIText("text");
	//ƴ����ʾfps
	text->text = "fps:"+to_string(int(1000 / mainGame->deltaTime));
	//��ȡ��������
	auto key = mainGame->Input.getKey();
	//�жϼ�������
	if (key == KeyMessage::a)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		//x = deltaX + X0 = V*t + X0
		currentPosition += jhVector2(-150,0)* ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(150,0)* ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,-150)* ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0,150)*((float)mainGame->deltaTime/1000);
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