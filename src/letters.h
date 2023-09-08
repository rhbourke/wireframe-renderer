#ifndef LETTERS_H
#define LETTERS_H


#include <vector>

struct point {
	float x, y, z;
};

/*A piece is a set of consecutive points that should have edges drawn to connect them all into a figure.
Many letters have only one piece, but some require multiple. For example, the letter O has an inner ring and outer ring of connected points.
To same time writing out all of the connected points in a letter, we just store the starting and ending point in each piece and make the edges later.*/
struct piece {
	int first, last;
};

struct letter {
	char name;
	std::vector<point> points;
	std::vector<piece> pieces;
	letter(char name, std::vector<point> points, std::vector<piece> pieces) : name(name), points(points), pieces(pieces) {}
};


const std::vector<letter> alphabet = {
	{
		' ',
		{
		},
		{
		},
	},{
		'A',
		{
			{0, 100, 1},
			{40, 0, 1},
			{60, 0, 1},
			{100, 100, 1},
			{80, 100, 1},
			{60, 50, 1},
			{40, 50, 1},
			{20, 100, 1},

			{40, 40, 1},
			{45, 20, 1},
			{55, 20, 1},
			{60, 40, 1},
		},
		{
			{0,7},
			{8, 11},
		}

	}, {
		'B',
		{
			{0, 0, 1},
			{0, 100, 1},
			{90, 100, 1},
			{100, 90, 1},
			{100, 60, 1},
			{90, 50, 1},
			{80, 50, 1},
			{85, 50, 1},
			{95, 40, 1},
			{95, 10, 1},
			{85, 0, 1},

			{15,15,1},
			{15,35,1},
			{70,35,1},
			{80,30,1},
			{80,20,1},
			{70,15,1},

			{15,65,1},
			{15,85,1},
			{75,85,1},
			{85,80,1},
			{85,70,1},
			{75,65,1},
		},
		{
			{0,10},

			{11, 16},

			{17, 22},
		}
	},{
		'C',
		{
			{0,20,1},
			{0, 80, 1},
			{20, 100, 1},
			{100, 100, 1},
			{100, 90, 1},
			{30, 90, 1},
			{20, 70, 1},
			{20, 30, 1},
			{30, 10, 1},
			{100, 10, 1},
			{100, 0, 1},
			{20, 0, 1},
		},
		{
			{0, 11}
		}
	},{
		'D',
		{
			{0, 0, 1},
			{0, 100, 1},
			{80, 100 ,1},
			{100, 80, 1},
			{100, 20, 1},
			{80, 0, 1},

			{20, 20, 1},
			{20, 80, 1},
			{70, 80 ,1},
			{85, 60 ,1},
			{85, 40, 1},
			{70, 20, 1},
		},{
			{0, 5},
			{6, 11}
		}
	}, {
		'E',
		{
			{0, 0, 1},
			{0, 100, 1},
			{100, 100, 1},
			{100, 85, 1},
			{15, 85, 1},
			{15, 55, 1},
			{70, 55, 1},
			{70, 45, 1},
			{15, 45, 1},
			{15, 15, 1},
			{100, 15, 1},
			{100, 0, 1},
		},{
			{0, 11}
		}
	}, {
		'F',
		{
			{0,0,1},
			{0, 100, 1},
			{15, 100, 1},
			{15, 55, 1},
			{70, 55, 1},
			{70, 45, 1},
			{15, 45, 1},
			{15, 15, 1},
			{90, 15, 1},
			{90, 0, 1},
		},{
			{0, 9}
		}
	}, {
		'G',
		{
			{0,20,1},
			{0, 80, 1},
			{20, 100, 1},
			{80, 100, 1},
			{100, 80, 1},
			{100, 70, 1},
			{70, 50, 1},
			{60, 60, 1},
			{80, 80, 1},
			{80, 90, 1},
			{30, 90, 1},
			{20, 70, 1},
			{20, 30, 1},
			{30, 10, 1},
			{90, 10, 1},
			{90, 0, 1},
			{20, 0, 1},
		},{
			{0, 16}
		}
	}, {
		'H',
		{
			{0, 0, 1},
			{0, 100, 1},
			{33, 100, 1},
			{33, 55, 1},
			{66, 55, 1},
			{66, 100, 1},
			{100, 100, 1},
			{100, 0, 1},
			{66, 0, 1},
			{66, 45, 1},
			{33, 45, 1},
			{33, 0, 1},
		},{
			{0, 11}
		}
	}, {
		'I',
		{
			{0, 0, 1},
			{0, 20, 1},
			{33, 20, 1},
			{33, 80, 1},
			{0, 80, 1},
			{0, 100, 1},
			{100, 100, 1},
			{100, 80, 1},
			{66, 80, 1},
			{66, 20, 1},
			{100, 20, 1},
			{100, 0, 1},
		}, {
			{0, 11}
		}

	}, {
		'J',
		{
			{0, 0, 1},
			{0, 20, 1},
			{33, 20, 1},
			{33, 80, 1},
			{20, 80, 1},
			{10, 70, 1},
			{0, 80, 1},
			{10, 100, 1},
			{50, 100, 1},
			{66, 80, 1},
			{66, 20, 1},
			{100, 20, 1},
			{100, 0, 1},
		}, {
			{0, 12}
		}
	}, {
		'K',
		{
			{0, 0, 1},
			{0, 100, 1},
			{33, 100, 1},
			{33, 50, 1},
			{70, 100, 1},
			{90, 85, 1},
			{50, 40, 1},
			{75, 15, 1},
			{60, 0, 1},
			{33, 30, 1},
			{33, 0, 1},
		}, {
			{0, 10}
		}
	}, {
		'L',
		{
			{10, 0, 1},
			{10, 100, 1},
			{90, 100, 1},
			{90, 80, 1},
			{30, 80, 1},
			{30, 0, 1},
		}, {
			{0, 5}
		}

	}, {
		'M',
		{
			{0, 100, 1},
			{25, 0, 1},
			{50, 25, 1},
			{75, 0, 1},
			{100, 100, 1},
			{85, 100, 1},
			{70, 35, 1},
			{50, 50, 1},
			{30, 35, 1},
			{15, 100, 1},
		}, {
			{0, 9}
		}

	}, {
		'N',
		{
			{0, 0, 1},
			{0, 100, 1},
			{20, 100, 1},
			{20, 25, 1},
			{80, 100, 1},
			{100, 100, 1},
			{100, 0, 1},
			{80, 0, 1},
			{80, 75, 1},
			{20, 0, 1},
		}, {
			{0, 9}
		}
	}, {
		 'O',
		{
			{0,20,1},
			{0, 80, 1},
			{20, 100, 1},
			{80, 100, 1},
			{100, 80, 1},
			{100, 20, 1},
			{80, 0, 1},
			{20, 0, 1},

			{25,25,1},
			{25, 75, 1},
			{75, 75, 1},
			{75, 25, 1},
		}, {
			{0, 7},
			{8, 11}
		}
	}, {
		 'P',
		{
			{0, 0, 1},
			{0, 100, 1},
			{20, 100, 1},
			{20, 50, 1},
			{80, 50, 1},
			{85, 50, 1},
			{95, 40, 1},
			{95, 10, 1},
			{85, 0, 1},

			{15,15,1},
			{15,35,1},
			{70,35,1},
			{80,30,1},
			{80,20,1},
			{70,15,1},
		}, {
			{0, 8},
			{9,14}
		}
	}, {
		'Q',
		{
			{0,20,1},
			{0, 80, 1},
			{20, 100, 1},
			{80, 100, 1},
			{85, 95, 1},
			{90, 100, 1},
			{100, 95, 1},
			{90, 90, 1},
			{100, 80, 1},
			{100, 20, 1},
			{80, 0, 1},
			{20, 0, 1},

			{25,25,1},
			{25, 75, 1},
			{75, 75, 1},
			{75, 25, 1},
		}, {
			{0, 11},
			{12, 15}
		}
	}, {
		 'R',
		{
			{0, 0, 1},
			{0, 100, 1},
			{20, 100, 1},
			{20, 50, 1},
			{45, 50, 1},
			{80, 100, 1},
			{95, 90, 1},
			{70, 50, 1},
			{85, 50, 1},
			{95, 40, 1},
			{95, 10, 1},
			{85, 0, 1},

			{15,15,1},
			{15,35,1},
			{70,35,1},
			{80,30,1},
			{80,20,1},
			{70,15,1},
		}, {
			{0, 11},
			{12,17}
		}
	}, {
		'S',
		{
			{100, 0, 1},
			{15, 0, 1},
			{0, 15, 1},
			{0, 45, 1},
			{15, 55, 1},
			{70, 55, 1},
			{80, 65, 1},
			{80, 85, 1},
			{0, 85, 1},
			{0, 100, 1},
			{85, 100, 1},
			{100, 90, 1},
			{100, 60, 1},
			{85, 45, 1},
			{15, 45, 1},
			{15, 25, 1},
			{25, 15, 1},
			{100,15, 1}
		}, {
			{0, 17}
		}
	}, {
		'T',
		{
			{5, 0, 1},
			{5, 25, 1},
			{35, 25, 1},
			{35, 100, 1},
			{65, 100, 1},
			{65, 25, 1},
			{95, 25, 1},
			{95, 0, 1},

		}, {
			{0, 7}
		}

	}, {
		'U',
		{
			{0, 0, 1},
			{0, 80, 1},
			{20, 100, 1},
			{80, 100, 1},
			{100, 80, 1},
			{100, 0, 1},
			{80, 0, 1},
			{80, 70, 1},
			{70, 80, 1},
			{30, 80, 1},
			{20, 70, 1},
			{20, 0, 1},
		}, {
			{0, 11}
		}
	}, {
		'V',
		{
			{0, 0, 1},
			{40, 100, 1},
			{60, 100, 1},
			{100, 0, 1},
			{80, 0, 1},
			{50, 80, 1},
			{20, 0, 1},
		}, {
			{0, 6}
		}
	}, {
		'W',
		{
			{0, 0, 1},
			{25, 100, 1},
			{50, 75, 1},
			{75, 100, 1},
			{100, 0, 1},
			{85, 0, 1},
			{70, 65, 1},
			{50, 50, 1},
			{30, 65, 1},
			{15, 0, 1},
		}, {
			{0, 9}
		}
	}, {
		'X',
		{
			{0, 0, 1},
			{40, 50, 1},
			{0, 100, 1},
			{20, 100, 1},
			{50, 60, 1},
			{80, 100, 1},
			{100, 100, 1},
			{60, 50, 1},
			{100, 0, 1},
			{80, 0, 1},
			{50, 40, 1},
			{20, 0, 1},
		}, {
			{0, 11}
		}
	}, {
		'Y',
		{
			{0, 0, 1},
			{40, 40, 1},
			{40, 100, 1},
			{60, 100, 1},
			{60, 40, 1},
			{100, 0, 1},
			{80, 0, 1},
			{50, 30, 1},
			{20, 0, 1},
		}, {
			{0, 8}
		}
	}, {
		'Z',
		{
			{0, 0, 1},
			{0, 20, 1},
			{70, 20, 1},
			{00, 100, 1},
			{100, 100, 1},
			{100, 80, 1},
			{30, 80, 1},
			{100, 0, 1},
		}, {
			{0, 7}
		}
	}

};
	
#endif

	