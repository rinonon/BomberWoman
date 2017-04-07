#include "ResourceLoader.h"
#include "stdCommon.h"


//staticïœêîÇÕcppÇ…é¿ëÃÇ™ïKóv
ResourceLoader* ResourceLoader::mInstance = 0;

ResourceLoader::ResourceLoader(){
}

ResourceLoader::~ResourceLoader(){
}

void ResourceLoader::create() {
	mInstance = new ResourceLoader();
}

void ResourceLoader::destroy() {
	SAFE_DELETE(mInstance);
}

ResourceLoader* ResourceLoader::getInstance() {
	return mInstance;
}

int ResourceLoader::getHdImg(int kind) const {
	return hdImg[kind];
}

int ResourceLoader::getHdPlayer1(int kind) const {
	return hdPlayer1[kind];
}

int ResourceLoader::getHdPlayer2(int kind) const {
	return hdPlayer2[kind];
}

int ResourceLoader::getHdFont(int kind) const {
	return hdFont[kind];
}

int ResourceLoader::getHdFloor() const {
	return mHdFloor;
}

int ResourceLoader::load() {

	DxLib::LoadDivGraph("data/image/Img.png", 12, 4, 3, 32, 32, hdImg, TRUE);
	DxLib::LoadDivGraph("data/image/Player1.bmp", 12, 3, 4, 32, 32, hdPlayer1, TRUE);
	DxLib::LoadDivGraph("data/image/Player2.bmp", 12, 3, 4, 32, 32, hdPlayer2, TRUE);
	DxLib::LoadDivGraph("data/fontData/font.dds", 96, 16, 6, 8, 16, hdFont, TRUE);
	mHdFloor = DxLib::LoadGraph("data/image/Floor.png", TRUE);

 	return 0;
}