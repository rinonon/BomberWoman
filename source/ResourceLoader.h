#pragma once

class ResourceLoader {
public:
	static ResourceLoader *getInstance();

	int getHdImg(int kind) const;
	int getHdPlayer1(int kind) const;
	int getHdPlayer2(int kind) const;
	int getHdFont(int kind) const;
	int getHdFloor() const;
	int load();

	static void create();
	static void destroy();

private:
	// コンストラクタ・コピーコンストラクタで生成やコピーを禁止
	ResourceLoader();
	ResourceLoader(ResourceLoader&);
	~ResourceLoader();

	static ResourceLoader* mInstance;

	int hdImg[12];
	int hdFont[96];
	int hdPlayer1[12];
	int hdPlayer2[12];
	int mHdFloor;
};