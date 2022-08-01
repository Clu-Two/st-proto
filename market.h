#pragma once
struct market
{
	const char* name = { "N/A" };
	const char* id = { "N/A" };
	int weight = 0;
	int price = 0;
	int quantity = 0;
	int row_total = 0;
	int load_total = 0;
	int increment = 0;

	int marketRowStaging(int row_total, int increment)
	{
		row_total += increment;
		return row_total;
	}

	enum details : int
	{
		NAME,
		ID,
		WEIGHT,
		PRICE,
		QUANTITY
	};

	enum names : int
	{
		STEEL,
		RADON,
		GRAPHENE,
		FCELLS,
		KRYPTONITE
	};

	market(const char* n, const char* i, int w, int p, int q)
	{
		name = n;
		id = i;
		weight = w;
		price = p;
		quantity = q;
	}

};
