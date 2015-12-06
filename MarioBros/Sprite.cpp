#include "Sprite.h"
#include "Graphic.h"
#include "Animation.h"
Sprite::Sprite(){};
Sprite::Sprite(Graphic* g, char* path)
{
	spriteHandler = g->spriteDX;
	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(path, &imageInfo);
	width = imageInfo.Width;
	height = imageInfo.Height;
	D3DXGetImageInfoFromFile(path, &imageInfo);
	D3DXCreateTextureFromFileEx(g->device,
		path,
		imageInfo.Width,
		imageInfo.Height,
		1,						//Mipmap level
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255),
		&imageInfo,
		NULL,
		&image);
}
void Sprite::Draw(int x, int y, float xScaleRatio, float yScaleRatio, D3DXVECTOR2 vRotatteCenter, float angle, D3DCOLOR color, RECT rSrc, float deep)
{
	D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform, NULL, 0, &D3DXVECTOR2(xScaleRatio, yScaleRatio), &vRotatteCenter, angle, &D3DXVECTOR2((float)x, (float)y));
	spriteHandler->SetTransform(&mTransform);
	spriteHandler->Draw(image, &rSrc, NULL, &D3DXVECTOR3(0, 0, deep), color);

}
void Sprite::Draw(int x, int y,int vpx,int vpy, float xScaleRatio, float yScaleRatio, RECT rSrc, float deep)
{
	D3DXVECTOR3 position((float)x, (float)y, 0);

	//
	// WORLD TO VIEWPORT TRANSFORM USING MATRIX
	//

	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -vpx;
	mt._42 = vpy;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);

	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);

	//spriteHandler->Draw(image, NULL, &center, &p, D3DCOLOR_XRGB(255, 255, 255));
	/*D3DXMATRIX mTransform;
	D3DXMatrixTransformation2D(&mTransform, NULL, 0, &D3DXVECTOR2(xScaleRatio, yScaleRatio), &D3DXVECTOR2(0, 0), 0, &D3DXVECTOR2((float)x, (float)y));
	spriteHandler->SetTransform(&mTransform);*/
	//D3DXMATRIX mt1;
	//D3DXMatrixScaling(&mt1, xScaleRatio, yScaleRatio, 1);
	//spriteHandler->SetTransform(&mt1);


	//spriteHandler->Draw(image, &rSrc,NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->Draw(image, &rSrc, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}