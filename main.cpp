//[C++ SFML 구글 공룡게임 만들기]
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
	//SFML 윈도우을 열어주고, title을 정해줍니다.
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Dinosaur Game. By BlockDMask");
	window.setFramerateLimit(60);	//프레임 정해주기

	//dino
	Texture t1;
	Texture t2;
	t1.loadFromFile("images/dino1.png");	//실제 그림을 받아 옵니다.
	t2.loadFromFile("images/dino2.png");

	//스프라이트로 만들어줌
	Sprite dinoArr[2];
	dinoArr[0] = Sprite(t1);
	dinoArr[1] = Sprite(t2);

	static const int DINO_Y_BOTTOM = HEIGHT - t1.getSize().y;	//공룡 바닥위치
	
	Position dinoPos;
	dinoPos.x = 50;
	dinoPos.y = DINO_Y_BOTTOM;

	//프레임에 따라 왼발 오른발 해주기 위한 변수 네개
	int index			= 0;	//왼발 오른발 인덱스
	float frame			= 0.f;
	float frameSpeed	= 0.4f;
	const int changeCount = 5;	//몇 프레임에 체인지 할지

	const int gravity = 5;	//중력. 점프할때 사용
	bool isJumping = false;	//점프 중인지
	bool isBottom = true;	//바닥에 발이 닿았는지

	//tree
	Texture t3;
	t3.loadFromFile("images/tree.png");
	Sprite tree(t3);

	static const int TREE_Y_BOTTOM = HEIGHT - t3.getSize().y;	//나무 바닥
	Position treePos;
	treePos.x = WIDTH - 20;
	treePos.y = TREE_Y_BOTTOM;

	const int treeSpeed = 4;	//나무 스피드

	while (window.isOpen())		//윈도우가 열렸으면
	{
		Event e;
		while (window.pollEvent(e))	//윈도우 이벤트를 받는데
		{
			if (e.type == Event::Closed)	//닫기면 윈도우 닫음
			{
				window.close();
			}
		}
		//logic.

		//dino jump.
		if (Keyboard::isKeyPressed(Keyboard::Space)) //스페이스 입력 감지
		{
			if (isBottom && !isJumping)	//바닥이고, 점프중이 아닐때 점프 가능
			{
				//make jumping stage;
				isJumping = true;
				isBottom = false;
			}
		}

		//dino jump(up and down)
		if (isJumping)	
		{
			dinoPos.y -= gravity; //점프중일때는 y에서 중력을 뺴줌 그럼 올라감
		}
		else
		{
			dinoPos.y += gravity;
		}

		//dino jump limit, dino bottom limit.
		if (dinoPos.y >= DINO_Y_BOTTOM)	//바닥에서 지하로 가지 않도록 설정
		{
			dinoPos.y = DINO_Y_BOTTOM;
			isBottom = true;
		}
		if (dinoPos.y <= DINO_Y_BOTTOM - 100)	//점프해서 우주로 가지 않도록 설정
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
