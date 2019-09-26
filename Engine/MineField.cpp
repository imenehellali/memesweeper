#include "MineField.h"
#include"SpriteCodex.h"

MineField::MineField(int nMines)
{
	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<int> xDist(0,width-1);
	std::uniform_int_distribution<int> yDist(0,height-1);
	assert(nMines > 0 && nMines < width * height);
	Vei2 origin(100, 100);
	for (int i = 0; i < nMines; i++) 
	{
		const int pos = yDist(rng) * width + xDist(rng);
		Vei2 tileDisplacement = origin + Vei2(xDist(rng), yDist(rng));
		field[pos].hasMine = true;
	}
}

void MineField::Update()
{

}

void MineField::DrawMineField(Graphics& gfx)
{
	Vei2 origin(250,200);
	//Draw Rctangle
	gfx.DrawRect(GetRect(), SpriteCodex::baseColor);
	//Draw Grid
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Vei2 tileDisplacement = origin + Vei2(x, y)*SpriteCodex::tileSize;
			const int pos = y * width + x;
			Vei2 posVec(x, y);
			field[pos].adjacentMinesNum = AdjacentMines(posVec);
			field[pos].DrawTile(gfx,tileDisplacement);
		}
	}
}

RectI MineField::GetRect()
{
	return RectI(Vei2(250,200), width*SpriteCodex::tileSize, height*SpriteCodex::tileSize);
}

void MineField::Reveal(Mouse& mouse)
{
	int x=mouse.GetPosX();
	int y = mouse.GetPosY();
	Vei2 pos(x, y);
	pos -= Vei2(250, 200);
	pos /= SpriteCodex::tileSize;
	if (mouse.LeftIsPressed()&& field[pos.y*width +pos.x].state!=Tile::State::Flagged)
	{
		field[pos.y * width + pos.x].state = Tile::State::Revealed;
	}
	if (mouse.RightIsPressed() && field[pos.y * width + pos.x].state != Tile::State::Flagged)
	{
		field[pos.y * width + pos.x].state = Tile::State::Flagged;
	}
}


void MineField::Tile::DrawTile(Graphics& gfx,Vei2& pos)
{
	switch (state)
	{
	case(Tile::State::Flagged):
	{
		SpriteCodex::DrawTileButton(pos, gfx);
		SpriteCodex::DrawTileFlag(pos, gfx);
	}break;
	case(Tile::State::Revealed):
	{
		if (!hasMine) {
			SpriteCodex::DrawTileNUmber(pos, adjacentMinesNum, gfx);
		}
		else if(hasMine) {
			SpriteCodex::DrawTileBomb(pos, gfx);
		}

	}break;
	case(Tile::State::Hidden):
	{
		SpriteCodex::DrawTileButton(pos, gfx);
	}
	break;
	}
}

int MineField::AdjacentMines(Vei2& pos)
{
	int count = -1;
	const int xStart = std::max(0, pos.x - 1);
	const int yStart = std::max(0, pos.y - 1);
	const int xEnd = std::min(width - 1, pos.x + 1);
	const int yEnd = std::min(height - 1, pos.y + 1);

	for (int y = yStart; y < yEnd; y++) {
		for (int x = xStart; x < xEnd; x++) {
			if (field[pos.y * width + pos.x].hasMine)
				++count;
		}
	}
	return count;
}

