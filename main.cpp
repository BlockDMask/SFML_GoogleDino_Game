//[C++ SFML ���� ������� �����]
//by. BlockDMask.

#include<SFML/Graphics.hpp>
using namespace sf;
#define WIDTH 600
#define HEIGHT 300
struct Position
{
	int x;
	int y;
};

int main(void)
{
	//SFML �������� �����ְ�, title�� �����ݴϴ�.
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Dinosaur Game. By BlockDMask");
	window.setFramerateLimit(60);	//������ �����ֱ�

	//dino
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/dino1.png");	//���� �׸��� �޾� �ɴϴ�.
	t2.loadFromFile("images/dino2.png");

	//��������Ʈ�� �������
	Sprite dinoArr[2];
	dinoArr[0] = Sprite(t1);
	dinoArr[1] = Sprite(t2);

	static const int DINO_Y_BOTTOM = HEIGHT - t1.getSize().y;	//���� �ٴ���ġ
	
	Position dinoPos;
	dinoPos.x = 50;
	dinoPos.y = DINO_Y_BOTTOM;

	//�����ӿ� ���� �޹� ������ ���ֱ� ���� ���� �װ�
	int index			= 0;	//�޹� ������ �ε���
	float frame			= 0.f;
	float frameSpeed	= 0.4f;
	const int changeCount = 5;	//�� �����ӿ� ü���� ����

	const int gravity = 5;	//�߷�. �����Ҷ� ���
	bool isJumping = false;	//���� ������
	bool isBottom = true;	//�ٴڿ� ���� ��Ҵ���

	//tree
	Texture t3;
	t3.loadFromFile("images/tree.png");
	Sprite tree(t3);

	static const int TREE_Y_BOTTOM = HEIGHT - t3.getSize().y;	//���� �ٴ�
	Position treePos;
	treePos.x = WIDTH - 20;
	treePos.y = TREE_Y_BOTTOM;

	const int treeSpeed = 4;	//���� ���ǵ�

	while (window.isOpen())		//�����찡 ��������
	{
		Event e;
		while (window.pollEvent(e))	//������ �̺�Ʈ�� �޴µ�
		{
			if (e.type == Event::Closed)	//�ݱ�� ������ ����
			{
				window.close();
			}
		}
		//logic.

		//dino jump.
		if (Keyboard::isKeyPressed(Keyboard::Space)) //�����̽� �Է� ����
		{
			if (isBottom && !isJumping)	//�ٴ��̰�, �������� �ƴҶ� ���� ����
			{
				//make jumping stage;
				isJumping = true;
				isBottom = false;
			}
		}

		//dino jump(up and down)
		if (isJumping)	
		{
			dinoPos.y -= gravity; //�������϶��� y���� �߷��� ���� �׷� �ö�
		}
		else
		{
			dinoPos.y += gravity;
		}

		//dino jump limit, dino bottom limit.
		if (dinoPos.y >= DINO_Y_BOTTOM)	//�ٴڿ��� ���Ϸ� ���� �ʵ��� ����
		{
			dinoPos.y = DINO_Y_BOTTOM;
			isBottom = true;
		}
		if (dinoPos.y <= DINO_Y_BOTTOM - 100)	//�����ؼ� ���ַ� ���� �ʵ��� ����
		{
			isJumping = false;
		}

		//dino step.
		frame += frameSpeed;
		if (frame > changeCount)
		{
			frame -= changeCount;
			++index;
			if (index >= 2) { index = 0; }
		}

		//tree move.
		if (treePos.x <= 0)
		{
			treePos.x = WIDTH;
		}
		else
		{
			treePos.x -= treeSpeed;
		}

		//tree Position.
		tree.setPosition(treePos.x, treePos.y);

		//dino Position.
		dinoArr[index].setPosition(dinoPos.x, dinoPos.y);

		//draw.
		window.clear(Color::White);
		window.draw(dinoArr[index]);
		window.draw(tree);
		window.display();
	}
	return 0;
}
