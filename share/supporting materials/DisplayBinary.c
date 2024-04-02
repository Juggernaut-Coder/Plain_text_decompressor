/*
 - Display an integer as binary
 - Extract by successive shifts
 - ECED 3401
 - 14 Sep 2022
*/

#include <stdio.h>

void display_binary(unsigned long data, int total)
{
/*
 - Display an integer value in data in its binary form
 - data: value to display (char, short, int, long)
 - total: total number of bits in value (8, 16, 32, 64)
*/
unsigned long mask;

if (total < 0 || total > 32) // sizeof(long) * 8 bits
	/* Sanity check - default to 8 bits */
	total = 8;

total--;

mask = 1 << total;

while (total >= 0)
{
	putc((data & mask) ? '1' : '0', stdout);
	data = data << 1;
	total--;
}

putc('\n', stdout);

}

main()
{
/*
 - Test display_binary() function
*/
char ch;
unsigned short s;
unsigned long l;

for (ch = 'A'; ch <= 'Z'; ch++)
{
	putc(ch, stdout);
	putc(' ', stdout);
	display_binary(ch, 8);
}

s = 0xFEDC;
printf("%04x ", s);
display_binary(s, 16);

l =0xFDECBA98;
printf("%08x ", l);
display_binary(l, 32);

getchar();

}