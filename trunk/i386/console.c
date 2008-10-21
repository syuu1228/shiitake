#include <lib/console.h>

/* Some screen stuff.  */
/* The number of columns.  */
#define COLUMNS			80
/* The number of lines.  */
#define LINES			24
/* The attribute of an character.  */
#define ATTRIBUTE		7
/* The video memory address.  */
#define VIDEO			0xB8000

/* Variables.  */
/* Save the X position.  */
static int xpos;
/* Save the Y position.  */
static int ypos;
/* Point to the video memory.  */
static volatile unsigned char *video;

/* Clear the screen and initialize VIDEO, XPOS and YPOS.  */
void
cls (void)
{
  int i;

  video = (unsigned char *) VIDEO;
  
  for (i = 0; i < COLUMNS * LINES * 2; i++)
    *(video + i) = 0;

  xpos = 0;
  ypos = 0;
}

/* Scroll the screen. */ 
static void
scroll (void)
{
	int x, y;
	for(y = 1; y < LINES; y++)
		for(x = 0; x < COLUMNS; x++) {
			*(video + (x + (y - 1) * COLUMNS) * 2) = 
				*(video + (x + y * COLUMNS) * 2);
			*(video + (x + (y - 1) * COLUMNS) * 2 + 1) = 
				ATTRIBUTE;
		}
	y = LINES - 1;
	for(x = 0; x < COLUMNS; x++) {
		*(video + (x + y * COLUMNS) * 2) = 0;
		*(video + (x + y * COLUMNS) * 2 + 1) = ATTRIBUTE;
	}
}

/* Put the character C on the screen.  */
void
putchar (int c)
{
  if (c == '\n' || c == '\r')
    {
    newline:
      xpos = 0;
      if(ypos < LINES - 1)
	      ypos++;
      return;
    }

  if (xpos == 0 && ypos == LINES - 1)
	  scroll();
  *(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
  *(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

  xpos++;
  if (xpos >= COLUMNS)
    goto newline;
}

int
getchar (void)
{
	return 0;
}
