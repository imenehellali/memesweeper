#pragma once

#include <assert.h>
#include<random>
#include "RectI.h"
#include"Graphics.h"
#include"Mouse.h"
class MineField
{
public:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	private:

	public:
		Tile() = default;
		void DrawTile(Graphics& gfx, Vei2& pos);
	public:
		State state = State::Hidden;
		bool hasMine = false;
	};
public:
	MineField(int nMines);
	void Update();
	void DrawMineField(Graphics& gfx);
	RectI GetRect();
	void Reveal(Mouse& mouse);
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[width * height];

};