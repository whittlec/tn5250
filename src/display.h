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

#define TN5250_DISPLAY_KEYQ_SIZE		50

#define TN5250_DISPLAY_IND_INHIBIT	   	0x0001
#define TN5250_DISPLAY_IND_MESSAGE_WAITING	0x0002
#define TN5250_DISPLAY_IND_X_SYSTEM	   	0x0004
#define TN5250_DISPLAY_IND_X_CLOCK	   	0x0008
#define TN5250_DISPLAY_IND_INSERT	   	0x0010

struct _Tn5250Terminal;
struct _Tn5250DBuffer;
struct _Tn5250Field;
struct _Tn5250Session;
struct _Tn5250Buffer;
struct _Tn5250CharMap;

/****s* lib5250/Tn5250Display
 * NAME
 *    Tn5250Display
 * SYNOPSIS
 *    Tn5250Display *dsp = tn5250_display_new ();
 *    tn5250_display_destroy (dsp);
 * DESCRIPTION
 *    Tn5250Display manages the display buffers and the terminal object.
 *    Internally, keeps track of indicators, saved message line.  This
 *    object hands off aid keys to the Tn5250Session object.
 * SOURCE
 */
struct _Tn5250Display {
   struct _Tn5250DBuffer * display_buffers;
   struct _Tn5250Terminal *terminal;
   struct _Tn5250Session *session;
   struct _Tn5250CharMap *map;
   int indicators;
   int indicators_dirty : 1;
   int pending_insert : 1;

   unsigned char *saved_msg_line;

   /* Queued keystroke ring buffer. */
   int key_queue_head, key_queue_tail;
   int key_queue[TN5250_DISPLAY_KEYQ_SIZE];
};

typedef struct _Tn5250Display Tn5250Display;
/*******/

extern Tn5250Display *	tn5250_display_new	      (void);
extern void		tn5250_display_destroy	      (Tn5250Display *This);

extern void		tn5250_display_set_session    (Tn5250Display *This,
						       struct _Tn5250Session *s);

extern Tn5250DBuffer *  tn5250_display_push_dbuffer   (Tn5250Display *This);
extern void		tn5250_display_restore_dbuffer(Tn5250Display *This,
						       Tn5250DBuffer *display);

extern void             tn5250_display_set_terminal   (Tn5250Display *This,
                                                       struct _Tn5250Terminal*);
extern void             tn5250_display_update         (Tn5250Display *This);

extern int		tn5250_display_waitevent      (Tn5250Display *This);
extern int		tn5250_display_getkey	      (Tn5250Display *This);

extern struct _Tn5250Field *tn5250_display_field_at   (Tn5250Display *This,
                                                       int y,
						       int x);
extern struct _Tn5250Field *tn5250_display_current_field(Tn5250Display *This);
extern struct _Tn5250Field *tn5250_display_next_field (Tn5250Display *This);
extern struct _Tn5250Field *tn5250_display_prev_field (Tn5250Display *This);

extern void	  tn5250_display_set_cursor_field     (Tn5250Display *This,
						       Tn5250Field *field);
extern void	  tn5250_display_set_cursor_home      (Tn5250Display *This);
extern void	  tn5250_display_set_cursor_next_field(Tn5250Display *This);
extern void       tn5250_display_set_curosr_prev_field(Tn5250Display *This);

extern void	  tn5250_display_shift_right	      (Tn5250Display *This,
						       Tn5250Field *field,
						       unsigned char fill);
extern void	  tn5250_display_field_adjust	      (Tn5250Display *This,
						       Tn5250Field *field);
extern void	  tn5250_display_interactive_addch    (Tn5250Display *This,
                                                       unsigned char ch);
extern void	  tn5250_display_beep		      (Tn5250Display *This);
extern void	  tn5250_display_do_aidkey	      (Tn5250Display *This,
                                                       int aidcode);
extern void	  tn5250_display_indicator_set	      (Tn5250Display *This,
						       int inds);
extern void	  tn5250_display_indicator_clear      (Tn5250Display *This,
						       int inds);
extern void	  tn5250_display_clear_unit           (Tn5250Display *This);
extern void	  tn5250_display_clear_unit_alternate (Tn5250Display *This);
extern void	  tn5250_display_clear_format_table   (Tn5250Display *This);
extern void	  tn5250_display_set_pending_insert   (Tn5250Display *This,
						       int y,
						       int x);
extern void	  tn5250_display_make_wtd_data        (Tn5250Display *This,
						       struct _Tn5250Buffer *b,
						       struct _Tn5250DBuffer *);
extern void	  tn5250_display_save_msg_line	      (Tn5250Display *This);
extern void	  tn5250_display_set_char_map	      (Tn5250Display *This,
                                                       const char *name);

/* Key functions */
extern void	  tn5250_display_do_keys	      (Tn5250Display *This);
extern void	  tn5250_display_do_key               (Tn5250Display *This,int);
extern void	  tn5250_display_kf_up                (Tn5250Display *This);
extern void	  tn5250_display_kf_down	      (Tn5250Display *This);
extern void       tn5250_display_kf_left	      (Tn5250Display *This);
extern void       tn5250_display_kf_right             (Tn5250Display *This);
extern void	  tn5250_display_kf_field_exit	      (Tn5250Display *This);
extern void	  tn5250_display_kf_field_minus	      (Tn5250Display *This);
extern void	  tn5250_display_kf_field_plus	      (Tn5250Display *This);
extern void	  tn5250_display_kf_dup		      (Tn5250Display *This);
extern void	  tn5250_display_kf_insert	      (Tn5250Display *This);
extern void	  tn5250_display_kf_tab		      (Tn5250Display *This);
extern void       tn5250_display_kf_backtab	      (Tn5250Display *This);
extern void	  tn5250_display_kf_end		      (Tn5250Display *This);
extern void       tn5250_display_kf_home              (Tn5250Display *This);
extern void	  tn5250_display_kf_delete            (Tn5250Display *This);

#define tn5250_display_dbuffer(This) \
   ((This)->display_buffers)
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
#define tn5250_display_roll(This,top,bottom,lines) \
   (tn5250_dbuffer_roll((This)->display_buffers,(top),(bottom),(lines)))
#define tn5250_display_set_ic(This,y,x) \
   (tn5250_dbuffer_set_ic((This)->display_buffers,(y),(x)))
#define tn5250_display_set_header_data(This,data,len) \
   (tn5250_dbuffer_set_header_data((This)->display_buffers,(data),(len)))
#define tn5250_display_clear_pending_insert(This) \
   (void)((This)->pending_insert = 0)
#define tn5250_display_pending_insert(This) \
   ((This)->pending_insert)
#define tn5250_display_field_data(This,field) \
   (tn5250_dbuffer_field_data((This)->display_buffers,(field)))
#define tn5250_display_msg_line(This) \
   (tn5250_dbuffer_msg_line((This)->display_buffers))
#define tn5250_display_char_map(This) \
   ((This)->map)

#ifdef __cplusplus
}
#endif

#endif				/* DISPLAY_H */

/* vi:set cindent sts=3 sw=3: */
