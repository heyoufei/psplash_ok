/* 
 *  pslash - a lightweight framebuffer splashscreen for embedded devices. 
 *
 *  Copyright (c) 2006 Matthew Allum <mallum@o-hand.com>
 *
 *  Parts of this file ( fifo handling ) based on 'usplash' copyright 
 *  Matthew Garret.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include "psplash.h"
#include "psplash-config.h"
#include "psplash-colors.h"
#include "psplash-poky-img.h"
#include "psplash-bar-img.h"
#include "radeon-font.h"
#include "1-img.h"
#include "2-img.h"
#include "3-img.h"
#include "4-img.h"
#include "5-img.h"
#include "6-img.h"
#include "7-img.h"
#include "8-img.h"
#include "9-img.h"
#include "10-img.h"

int count =0;
int num = 0;


#define SPLIT_LINE_POS(fb)                                  \
	(  (fb)->height                                     \
	 - ((  PSPLASH_IMG_SPLIT_DENOMINATOR                \
	     - PSPLASH_IMG_SPLIT_NUMERATOR)                 \
	    * (fb)->height / PSPLASH_IMG_SPLIT_DENOMINATOR) \
	)

void
psplash_exit (int signum)
{
  DBG("mark");

  psplash_console_reset ();
}

void
psplash_draw_msg (PSplashFB *fb, const char *msg)
{
  int w, h;

  psplash_fb_text_size (fb, &w, &h, &radeon_font, msg);

  DBG("displaying '%s' %ix%i\n", msg, w, h);

  /* Clear */

  psplash_fb_draw_rect (fb, 
			0, 
			SPLIT_LINE_POS(fb) - h, 
			fb->width,
			h,
			PSPLASH_BACKGROUND_COLOR);

  psplash_fb_draw_text (fb,
			(fb->width-w)/2, 
			SPLIT_LINE_POS(fb) - h,
			PSPLASH_TEXT_COLOR,
			&radeon_font,
			msg);
}

void
psplash_draw_progress (PSplashFB *fb, int value)
{
  int x, y, width, height, barwidth;

  /* 4 pix border */
  x      = ((fb->width  - BAR_IMG_WIDTH)/2) + 4 ;
  y      = SPLIT_LINE_POS(fb) + 4;
  width  = BAR_IMG_WIDTH - 8; 
  height = BAR_IMG_HEIGHT - 8;
	//printf("in psplash_draw_progress function ,x = %d, y = %d, width = %d, height = %d, value = %d\n", x, y, width, height, value);
  if (value > 0)
    {
      barwidth = (CLAMP(value,0,100) * width) / 100;
      psplash_fb_draw_rect (fb, x + barwidth, y, 
    			width - barwidth, height,
			PSPLASH_BAR_BACKGROUND_COLOR);
      psplash_fb_draw_rect (fb, x, y, barwidth,
			    height, PSPLASH_BAR_COLOR);
    }
  else
    {
      barwidth = (CLAMP(-value,0,100) * width) / 100;
      psplash_fb_draw_rect (fb, x, y, 
    			width - barwidth, height,
			PSPLASH_BAR_BACKGROUND_COLOR);
      psplash_fb_draw_rect (fb, x + width - barwidth,
			    y, barwidth, height,
			    PSPLASH_BAR_COLOR);
    }

  DBG("value: %i, width: %i, barwidth :%i\n", value, 
		width, barwidth);
}

static int 
parse_command_for_mydesign (PSplashFB *fb, char *string, int length) 
{
  char *command;
	
  DBG("got cmd %s", string);
	
  if (strcmp(string,"QUIT") == 0)
    return 1;

  command = strtok(string," ");

  if (!strcmp(command,"PROGRESS")) 
    {	
		//printf("just for test!!!!!!......\n");
	count ++;
	if (count >= 5000)
	{
	//	printf("the count >= 1000!!!!!\n");
		count = 0;
		num ++;
		switch (num)
		{
		case 1:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, A_IMG_RLE_PIXEL_DATA);
			break;
		case 2:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, B_IMG_RLE_PIXEL_DATA);
			break;
		case 3:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, C_IMG_RLE_PIXEL_DATA);
			break;
		case 4:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, D_IMG_RLE_PIXEL_DATA);
			break;
		case 5:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, E_IMG_RLE_PIXEL_DATA);
			break;
		case 6:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, F_IMG_RLE_PIXEL_DATA);
			break;
		case 7:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, G_IMG_RLE_PIXEL_DATA);
			break;
		case 8:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, H_IMG_RLE_PIXEL_DATA);
			break;
		case 9:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, I_IMG_RLE_PIXEL_DATA);
			break;
		case 10:
			psplash_fb_draw_image(fb, 272,112, 256,256, 4, 1024, J_IMG_RLE_PIXEL_DATA);
			num = 0;
			break;	
		}
//		if(num == 1)
      
	 /*psplash_fb_draw_image (fb, 
			 (fb->width  - A_IMG_WIDTH)/2, 
//#if PSPLASH_IMG_FULLSCREEN
			 (fb->height - A_IMG_HEIGHT)/2,
//#else
			 //(fb->height * PSPLASH_IMG_SPLIT_NUMERATOR
			 // / PSPLASH_IMG_SPLIT_DENOMINATOR - POKY_IMG_HEIGHT)/2,
//#endif
			 A_IMG_WIDTH,
			 A_IMG_HEIGHT,
			 A_IMG_BYTES_PER_PIXEL,
			 A_IMG_ROWSTRIDE,
			 A_IMG_RLE_PIXEL_DATA);*/
		
		}
    } 

  return 0;
}

/*static int 
parse_command (PSplashFB *fb, char *string, int length) 
{
  char *command;

  DBG("got cmd %s", string);
	
  if (strcmp(string,"QUIT") == 0)
    return 1;

  command = strtok(string," ");

  if (!strcmp(command,"PROGRESS")) 
    {
      psplash_draw_progress (fb, atoi(strtok(NULL,"\0")));
    } 
  else if (!strcmp(command,"MSG")) 
    {
      psplash_draw_msg (fb, strtok(NULL,"\0"));
    } 
  else if (!strcmp(command,"QUIT")) 
    {
      return 1;
    }

  return 0;
}
*/
void 
psplash_main (PSplashFB *fb, int pipe_fd, int timeout) 
{
  int            err;
  ssize_t        length = 0;
  fd_set         descriptors;
  struct timeval tv;
  char          *end;
  char           command[2048];

  tv.tv_sec = timeout;
  tv.tv_usec = 0;

  FD_ZERO(&descriptors);
  FD_SET(pipe_fd, &descriptors);

  end = command;
	//printf("in psplash_main function!\n ");
 /* while (1) 
    {
      if (timeout != 0) 
	err = select(pipe_fd+1, &descriptors, NULL, NULL, &tv);
      else
	err = select(pipe_fd+1, &descriptors, NULL, NULL, NULL);
	//printf("err = %d\n", err);      
      if (err <= 0) 
	{
	  return;
	}
      
      length += read (pipe_fd, end, sizeof(command) - (end - command));
		//printf("the length=%d\n", length);
		//printf("command is %s\n", command);
      if (length == 0) 
	{
	  close(pipe_fd);
	  pipe_fd = open(PSPLASH_FIFO,O_RDONLY|O_NONBLOCK);
	  //printf("length = 0\n");
	  goto out;
	}
      
      if (command[length-1] == '\0') 
	{
		//printf("command[length-1]=\\0 \n");
	  if (parse_command(fb, command, strlen(command))) 
	    return;
	  length = 0;
	} 
      else if (command[length-1] == '\n') 
	{
		//printf("command[length-1] =\\n\n");
	  command[length-1] = '\0';
	  if (parse_command(fb, command, strlen(command))) 
	    return;
	  length = 0;
	} 


    out:
      end = &command[length];
    
      tv.tv_sec = timeout;
      tv.tv_usec = 0;
      
      FD_ZERO(&descriptors);
      FD_SET(pipe_fd,&descriptors);
    }*/

	while(1)
	{
		err = select(pipe_fd+1, &descriptors, NULL, NULL, NULL);
		if(err <= 0)
			return;
		length = read (pipe_fd, end, sizeof(command)-(end - command));
		command[length-1] = '\0';
		if(parse_command_for_mydesign(fb, command, strlen(command)))
			return;
	}

  return;
}

int 
main (int argc, char** argv) 
{
  char      *tmpdir;
  int        pipe_fd, i = 0, angle = 0, ret = 0;
  PSplashFB *fb;
  bool       disable_console_switch = FALSE;
  
  signal(SIGHUP, psplash_exit);
  signal(SIGINT, psplash_exit);
  signal(SIGQUIT, psplash_exit);

  while (++i < argc)
    {
      if (!strcmp(argv[i],"-n") || !strcmp(argv[i],"--no-console-switch"))
        {
	  disable_console_switch = TRUE;
	  continue;
	}

      if (!strcmp(argv[i],"-a") || !strcmp(argv[i],"--angle"))
        {
	  if (++i >= argc) goto fail;
	  angle = atoi(argv[i]);
	  continue;
	}
      
    fail:
      fprintf(stderr, 
	      "Usage: %s [-n|--no-console-switch][-a|--angle <0|90|180|270>]\n", 
	      argv[0]);
      exit(-1);
    }

  tmpdir = getenv("TMPDIR");

  if (!tmpdir)
    tmpdir = "/tmp";
	printf("the tmpdir is %s\n", tmpdir);
  chdir(tmpdir);

  if (mkfifo("psplash_fifo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP))
    {
      if (errno!=EEXIST) 
	{
	  perror("mkfifo");
	  exit(-1);
	}
	else
	{
		printf("hahahhhhhfdas\n");
	}

    }
	
  pipe_fd = open (PSPLASH_FIFO,O_RDONLY|O_NONBLOCK);
  printf("the pipe_fd is %d\n", pipe_fd); 

  if (pipe_fd==-1) 
    {
      perror("pipe open");
      exit(-2);
    }

  if (!disable_console_switch)
    psplash_console_switch ();

	//printf("angle = %d\n", angle);
  if ((fb = psplash_fb_new(angle)) == NULL) {
	  ret = -1;
	  goto fb_fail;
  }

  /* Clear the background with #ecece1 */
  psplash_fb_draw_rect (fb, 0, 0, fb->width, fb->height,
                        PSPLASH_BACKGROUND_COLOR);

  /* Draw the Poky logo  */
  /*psplash_fb_draw_image (fb, 
			 (fb->width  - POKY_IMG_WIDTH)/2, 
#if PSPLASH_IMG_FULLSCREEN
			 (fb->height - POKY_IMG_HEIGHT)/2,
#else
			 (fb->height * PSPLASH_IMG_SPLIT_NUMERATOR
			  / PSPLASH_IMG_SPLIT_DENOMINATOR - POKY_IMG_HEIGHT)/2,
#endif
			 POKY_IMG_WIDTH,
			 POKY_IMG_HEIGHT,
			 POKY_IMG_BYTES_PER_PIXEL,
			 POKY_IMG_ROWSTRIDE,
			 POKY_IMG_RLE_PIXEL_DATA);*/

  /* Draw progress bar border */
/*  psplash_fb_draw_image (fb, 
			 (fb->width  - BAR_IMG_WIDTH)/2, 
			 SPLIT_LINE_POS(fb),
			 BAR_IMG_WIDTH,
			 BAR_IMG_HEIGHT,
			 BAR_IMG_BYTES_PER_PIXEL,
			 BAR_IMG_ROWSTRIDE,
			 BAR_IMG_RLE_PIXEL_DATA);
*/
//  psplash_draw_progress (fb, 0);

#ifdef PSPLASH_STARTUP_MSG
  //psplash_draw_msg (fb, PSPLASH_STARTUP_MSG);
  //printf("defined PSPLASH_STARTUP_MSG!\n");
#endif

  psplash_main (fb, pipe_fd, 0);


  psplash_fb_destroy (fb);

 fb_fail:
  unlink(PSPLASH_FIFO);

  if (!disable_console_switch)
    psplash_console_reset ();

  return ret;
}
