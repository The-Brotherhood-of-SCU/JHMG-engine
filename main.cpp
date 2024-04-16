#include "JHMG engine.h"

//����ȫ����Ϸ����
Game* mainGame;

//��������
void loop();
void trigger(gameObject* other);
void onClick(int messageType, jhVector2 position);

int main(int argc, char* argv[])
{
	//������Ϸ����
	mainGame = new Game;
	//���ô��ڴ�С�ͱ���
	mainGame->setWindowSize(jhVector2(800, 600));
	mainGame->setWindowTitle("Game demo");
	//������Ϸ֡��
	mainGame->setTargetFrame(165);
	//������Ϸ����
	gameScene* scene = new gameScene;
	//����UI����
	gameUI* xiaoxin = new gameUI(jhVector2(0, 0), jhVector2(50, 50), ".\\xiaoxin.png", true);
	//���UI���󵽳�����
	scene->addGameUI("xiaoxin", xiaoxin);
	//�����ı�UI
	gameUIText* text = new gameUIText(jhString("fps"), jhVector2(100, 100), true);
	//����ı�UI��������
	scene->addGameUIText("text", text);
	//������Ϸ����
	gameObject* player = new gameObject(new jhObject2D::circle(25, jhVector2(170, 70)), ".\\pkq.png", 50, 50, true);
	//����Ϸ������ײ�¼�(������ײ����)
	player->setOnCollision(trigger);
	//����Ϸ����ѭ���¼�(ÿ֡����һ��)
	player->setGameLoopFunc(loop);
	//�����Ϸ���󵽳�����
	scene->addGameObject("player", player);
	//������Ϸ����
	gameObject* pikaqiu = new gameObject(new jhObject2D::circle(25, jhVector2(270, 70)), ".\\pkq.png", 50, 50, true);
	//����Ϸ�������¼�(�������)
	pikaqiu->mouseAction->setClickFunc(onClick);
	//�����Ϸ���󵽳�����
	scene->addGameObject("pikaqiu", pikaqiu);
	//��ӳ�������Ϸ��
	mainGame->setScene(scene);
	//��ʼ�����ڿ�ʼ��Ϸ
	mainGame->initWindow();
}

void loop()
{
	//��ȡ��Ϸ����
	auto scene = mainGame->getScene();
	//��ȡ��Ϸ����
	auto player = scene->getGameObject("player");
	//��ȡUI�ı�����
	auto text = scene->getGameUIText("text");
	//ƴ����ʾfps
	text->text = "fps:" + to_string(int(1000 / mainGame->deltaTime));
	//��ȡ��������
	auto key = mainGame->Input.getKey();
	//�жϼ�������
	if (key == KeyMessage::a)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		//x = deltaX + X0 = V*t + X0
		currentPosition += jhVector2(-250, 0) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::d)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(250, 0) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::w)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0, -250) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::s)
	{
		jhVector2 currentPosition = player->transform.circle->getPosition();
		currentPosition += jhVector2(0, 250) * ((float)mainGame->deltaTime / 1000);
		player->transform.circle->move(currentPosition);
	}
	if (key == KeyMessage::space)
	{
		//ɾ������
		cout << "delete pikaqiu" << endl;
		scene->removeGameObject("pikaqiu");
	}
	if (key == KeyMessage::esc)
	{
		//�˳���Ϸ
		exit(0);
	}
}

void trigger(gameObject* other)
{
	//��ײ�������
	cout << mainGame->getScene()->getName(other) << endl;
}

void onClick(int messageType, jhVector2 position)
{
	//������
	if (messageType == MouseMessage::leftDown)
		cout << "�������" << endl;
	if (messageType == MouseMessage::leftUp)
		cout << "����ſ�" << endl;
	if (messageType == MouseMessage::rightDown)
		cout << "�Ҽ�����" << endl;
	if (messageType == MouseMessage::rightUp)
		cout << "�Ҽ��ſ�" << endl;
}