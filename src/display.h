/* tn5250 -- an implentation of the 5250 telnet protocol.
 * Copyright (C) 1997 Michael Madore
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#define TN5250_DISPLAY_IND_INHIBIT	   	0x0001
#define TN5250_DISPLAY_IND_MESSAGE_WAITING	0x0002
#define TN5250_DISPLAY_IND_X_SYSTEM	   	0x0004
#define TN5250_DISPLAY_IND_X_CLOCK	   	0x0008
#define TN5250_DISPLAY_IND_INSERT	   	0x0010

struct _Tn5250Table;
struct _Tn5250Terminal;
struct _Tn5250DBuffer;
struct _Tn5250Field;

struct _Tn5250Display {
   struct _Tn5250Table *   format_tables;
   struct _Tn5250DBuffer * display_buffers;
   struct _Tn5250Terminal *terminal;
   int indicators;
   int indicators_dirty : 1;
};

typedef struct _Tn5250Display Tn5250Display;

extern Tn5250Display *	tn5250_display_new	      (int width,
						       int height);
extern void		tn5250_display_destroy	      (Tn5250Display *This);

extern Tn5250DBuffer *  tn5250_display_push_dbuffer   (Tn5250Display *This);
extern Tn5250Table *	tn5250_display_push_table     (Tn5250Display *This);
extern void		tn5250_display_restore_dbuffer(Tn5250Display *This,
						       Tn5250DBuffer *display);
extern void             tn5250_display_restore_table  (Tn5250Display *This,
                                                       Tn5250Table *table);

extern void             tn5250_display_set_terminal   (Tn5250Display *This,
                                                       struct _Tn5250Terminal*);
extern void             tn5250_display_update         (Tn5250Display *This);

extern int		tn5250_display_waitevent      (Tn5250Display *This);
extern int		tn5250_display_getkey	      (Tn5250Display *This);

extern struct _Tn5250Field *tn5250_display_current_field(Tn5250Display *This);
extern struct _Tn5250Field *tn5250_display_next_field (Tn5250Display *This);
extern struct _Tn5250Field *tn5250_display_prev_field (Tn5250Display *This);

extern void	  tn5250_display_set_cursor_field     (Tn5250Display *This,
						       Tn5250Field *field);
extern void	  tn5250_display_set_cursor_home      (Tn5250Display *This);
extern void	  tn5250_display_set_cursor_next_field(Tn5250Display *This);
extern void       tn5250_display_set_curosr_prev_field(Tn5250Display *This);

extern unsigned char * tn5250_display_field_data      (Tn5250Display *This,
						       Tn5250Field *field);
extern void	  tn5250_display_shift_right	      (Tn5250Display *This,
						       Tn5250Field *field,
						       unsigned char fill);
extern void	  tn5250_display_field_adjust	      (Tn5250Display *This,
						       Tn5250Field *field);
extern void	  tn5250_display_field_exit	      (Tn5250Display *This);
extern void	  tn5250_display_field_minus	      (Tn5250Display *This);
extern void	  tn5250_display_field_plus	      (Tn5250Display *This);
extern void	  tn5250_display_dup		      (Tn5250Display *This);
extern void	  tn5250_display_interactive_addch    (Tn5250Display *This,
                                                       unsigned char ch);
extern void	  tn5250_display_beep		      (Tn5250Display *This);
extern void	  tn5250_display_q_aidcode	      (Tn5250Display *This,
                                                       int aidcode);
extern void	  tn5250_display_indicator_set	      (Tn5250Display *This,
						       int inds);
extern void	  tn5250_display_indicator_clear      (Tn5250Display *This,
						       int inds);
#define tn5250_display_indicators(This) \
   ((This)->indicators)
#define tn5250_display_inhibited(This) \
   ((tn5250_display_indicators (This) & TN5250_DISPLAY_IND_INHIBIT) != 0)
#define tn5250_display_inhibit(This) \
   (tn5250_display_indicator_set (This, TN5250_DISPLAY_IND_INHIBIT))
#define tn5250_display_uninhibit(This) \
   (tn5250_display_indicator_clear (This, TN5250_DISPLAY_IND_INHIBIT))
#define tn5250_display_cursor_x(This) \
   (tn5250_dbuffer_cursor_x ((This)->display_buffers))
#define tn5250_display_cursor_y(This) \
   (tn5250_dbuffer_cursor_y ((This)->display_buffers))
#define tn5250_display_set_cursor(This,y,x) \
   (tn5250_dbuffer_cursor_set ((This)->display_buffers,(y),(x)))
#define tn5250_display_width(This) \
   (tn5250_dbuffer_width((This)->display_buffers))
#define tn5250_display_height(This) \
   (tn5250_dbuffer_height((This)->display_buffers))
#define tn5250_display_char_at(This,y,x) \
   (tn5250_dbuffer_char_at((This)->display_buffers,(y),(x))) 
#define tn5250_display_addch(This,ch) \
   (tn5250_dbuffer_addch((This)->display_buffers,(ch)))

#ifdef __cplusplus
}
#endif

#endif				/* DISPLAY_H */

/* vi:set cindent sts=3 sw=3: */