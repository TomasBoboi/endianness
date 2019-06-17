#include <stdlib.h>
#include <stdio.h>

#define Type long long

Type reverse_endianness(Type x)
{
	Type y = 0;

	for (int i = 0; i < sizeof(Type); i++)
	{
		y |= x & 255; // 0x00..00FF
		if (i != sizeof(Type) - 1)
		{
			y <<= 8;
			x >>= 8;
		}
	}

	return y;
}

void print_bits(Type x)
{
	char bits[128];
	char k = 8 * sizeof(Type) - 1;

	for (int i = 0; i < sizeof(Type) * 8; i++)
		bits[i] = 0;

	while (x != 0)
	{
		bits[k--] = x % 2;
		x /= 2;
	}

	for (int i = 0; i < 8 * sizeof(Type); i++)
		printf("%c%s", bits[i] + '0', ((i + 1) % 4 == 0) ? " " : "");

	printf("\n");
}

void print_hex(Type x)
{
	char hex[32];
	char k = 2 * sizeof(Type) - 1;

	for (int i = 0; i < sizeof(Type) * 2; i++)
		hex[i] = 0;

	while (x != 0)
	{
		switch (x % 16)
		{
		case 0: case 1: case 2: case 3: case 4:
		case 5: case 6: case 7: case 8: case 9:
			hex[k--] = x % 16 + '0';
			break;
		case 10: case 11: case 12: case 13: case 14: case 15:
			hex[k--] = x % 16 + 'A' - 10;
			break;
		}
		x /= 16;
	}

	for (int i = 0; i < 2 * sizeof(Type); i++)
		printf("   %c ", (hex[i]) ? hex[i] : '0');
	printf("\n");
}

int main()
{
	///long long
	long long x = 0x0F0E0D0C0B0A0908;

	///int
	//int x = 0x0F0E0D0C;

	///unsigned char
	//unsigned char x = 0xAF;

	print_bits(x);
	print_hex(x);

	print_bits(reverse_endianness(x));
	print_hex(reverse_endianness(x));

	print_bits(reverse_endianness(reverse_endianness(x)));
	print_hex(reverse_endianness(reverse_endianness(x)));

	printf("\nGATA");
	getchar();
	return 0;
}