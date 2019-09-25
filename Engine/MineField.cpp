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
		if(field[pos].hasMine)
			field[pos].SpawnMine(tileDisplacement);
	}
}

void MineField::Update()
{
}

void MineField::DrawMineField(Graphics& gfx)
{
	Vei2 origin(100, 200);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Vei2 tileDisplacement = origin + Vei2(x, y)*SpriteCodex::tileSize;
			field[y * width + x].DrawTile(gfx,tileDisplacement);
		}
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
			SpriteCodex::DrawTile0(pos, gfx);
		}
		else {
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

MineField::Tile::Tile(const Vei2 size_in)
{
}

void MineField::Tile::SpawnMine(const Vei2 pos)
{
	assert(!hasMine);
	hasMine = true;
	
}
