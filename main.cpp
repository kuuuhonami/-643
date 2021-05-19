#include<Dxlib.h>
#include"GameBox.h"
#include<cmath>

//bool IsHit(const Rect& rcA, const Rect& rcB)
//{
//	//1まずX方向を調べる
//	// 1-1中心と中心のX座標の差分の絶対値をとる
//	// 1-2それぞれの幅を足したものと1-1を比較する
//	// 1-3幅を足したもの1-2より差分1-1がでかいならfalseを返す
//
//	/*if (fabsf(rcA.center.x - rcB.center.x) > rcA.w + rcB.w)
//	{
//		return false;
//	}
//
//	if (fabsf(rcA.center.y - rcB.center.y) > rcA.h + rcB.h)
//	{
//		return false;
//	}*/
//
//	return true;
//}

bool IsHit(const Circle& cA,const Circle& cB)
{

	auto diffX = cA.center.x - cB.center.x;
	auto diffY = cA.center.y - cB.center.y;
	auto totalRadius = cA.radius + cB.radius;
	return diffX * diffX + diffY * diffY <= totalRadius * totalRadius;
}

int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int)
{
	
	SetMainWindowText(_T("円の当たり判定"));
	ChangeWindowMode(true);
	SetWindowText(L"2016203_穂波風空");
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	Circle cA = { {100,100},50 };
	Circle cB = { {400,300},50 };

	char keystate[256];

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		GetHitKeyStateAll(keystate);
		constexpr float speed = 4.0f;
		if (keystate[KEY_INPUT_RIGHT])
		{
			cA.center.x += speed;
		}

		if (keystate[KEY_INPUT_LEFT])
		{
			cA.center.x -= speed;
		}

		if (keystate[KEY_INPUT_UP])
		{
			cA.center.y -= speed;
		}

		if (keystate[KEY_INPUT_DOWN])
		{
			cA.center.y += speed;
		}

		UINT32 color = 0xffffff;

		//もし当たってたら色を変更する
		if (IsHit(cA, cB))
		{
			color = 0xfffff;
			auto diffV = cA.center - cB.center;
			auto d = (cA.radius + cB.radius) - diffV.Magnitube();
			cA.center+= diffV.Normalized() * d;

		}

		//短形A  
		DrawCircleAA(cA.center.x, cA.center.y,cA.radius,32, color);

		//短形B  
		DrawCircleAA(cB.center.x, cB.center.y,cB.radius, 32, color);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
	//プログラムの終了
}